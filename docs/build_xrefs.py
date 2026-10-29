#!/usr/bin/env python3
"""
build_xrefs.py — Phase 2: call graph + xref database for MMBCC decomp.

Reads the baserom IN PLACE under gen_func_list_v2's SHA-1 gate. The ROM is
never copied into any repo and never modified.

Inputs:
  docs/func_list_v2.txt (fixed hi-reg MOV decoder: A=51, B=1600),
  docs/func_list_v2_5_addendum.txt (+52 B consolidated novel)
  (1703 counted starts; v2.1-v2.4 addenda are historical — their
  still-novel entries are consolidated in v2.5)

Outputs (under docs/):
  xrefs.tsv            — one row per edge:
                         src_func\toffset\tsrc_addr\tkind\tdst_func\tdst_offset\tnote
                         kind in {bl, bx, pool, dataptr, bcond, tailcall}
  xrefs_unresolved.tsv — indirect bx exits that could not be resolved
  xrefs_dataptrs.tsv   — whole-ROM scan for 32-bit code pointers in data
  func_stats.tsv       — per-function instruction stats (library clustering)
  xrefs_README.md      — format documentation + query examples

Method: for each of the 1649 starts, bounded recursive descent with the
generator's ARMv4T-exact decoders (Thumb BL sign-extends bit 22), tracking
the ldr-literal/pop register tags so `bx rN` / `ldr pc,[pc]` targets resolve.
Function bodies stop at other starts (tail calls); they are NOT stopped at
the v2 owner map, so v2.2 addendum bodies decode fully even where they
overlap neighbours (overlaps are reported as diagnostics).
"""
import struct
import sys
from collections import defaultdict

sys.path.insert(0, '/home/hatch/workspace/mmbcc-decomp/docs')
import gen_func_list_v2 as G  # noqa: E402  (SHA-1-gated; reuses decoders)

DOCS = '/home/hatch/workspace/mmbcc-decomp/docs'
H6 = lambda o: '%06X' % o
H8 = lambda o: '%08X' % o
ROMV = lambda o: '0x%08X' % (G.BASE + o)   # file offset -> ROM address

# --------------------------------------------------------------------------
# 1. Parse the three function lists -> the 1649 counted starts.
# --------------------------------------------------------------------------
def parse_list(path):
    starts = {}
    with open(path) as f:
        for line in f:
            line = line.strip()
            if not line or line.startswith('#'):
                continue
            p = line.split()
            off = int(p[0], 16)
            tier = p[1]
            if tier == 'D':
                continue
            if 'ALT-ENTRY, not counted' in line:
                continue
            mode = 'ARM' if p[2] == 'R' else 'T'
            starts[off] = {'mode': mode, 'tier': tier, 'sym': p[3]}
    return starts

starts = {}
for fn in ('func_list_v2.txt', 'func_list_v2_5_addendum.txt'):
    part = parse_list(DOCS + '/' + fn)
    dupes = set(starts) & set(part)
    assert not dupes, 'duplicate starts across lists: %s' % dupes
    starts.update(part)
print('starts: %d (A=%d B=%d)' % (
    len(starts),
    sum(1 for v in starts.values() if v['tier'] == 'A'),
    sum(1 for v in starts.values() if v['tier'] == 'B')), file=sys.stderr)
assert len(starts) == 1703, 'expected 1703, got %d' % len(starts)

owner = G.owner  # generator's v2 body map, for diagnostics only

# --------------------------------------------------------------------------
# CORRECTED dec_thumb: gen_func_list_v2.dec_thumb HAD the hi-register MOV
# Rs/Rd high bits SWAPPED (it used bit7->Rs, bit6->Rd; the ARMv4T encoding
# is bit6->Rs-high, bit7->Rd-high). Verified against arm-none-eabi-as:
#   mov pc, r0 = 0x4687, mov r7, r8 = 0x4647, mov pc, r8 = 0x46C7,
#   mov r8, r0 = 0x4680, mov pc, lr = 0x46F7, mov lr, pc = 0x46FE.
# Consequences of the bug: real `mov pc, rX` switch-dispatch jumps decoded
# as 'fall' (bodies chained through jump tables into case handlers), and
# real `mov r7, r8`-style moves decoded as `bx r0` (false indirect exits
# truncating functions). Everything below uses the corrected decoder.
# (Upstream fix APPLIED in gen_func_list_v2.py 2026-10-20 — this local copy
# is now redundant but kept as a cross-check; both agree.)
# --------------------------------------------------------------------------
def dec_thumb(o):
    h = G.u16(o)
    if 0xF000 <= h <= 0xF7FF:                      # BL first halfword
        if o + 4 > G.CODE_END:
            return (2, 'invalid', None, None)
        h2 = G.u16(o + 2)
        if not 0xF800 <= h2 <= 0xFFFF:
            return (2, 'invalid', None, None)
        s = (h >> 10) & 1
        off = ((h & 0x7FF) << 12) | ((h2 & 0x7FF) << 1)
        if s:
            off -= 1 << 23                        # ARMv4T: sign-extend bit22
        return (4, 'bl', o + 4 + off, None)
    if h >= 0xF800:
        return (2, 'invalid', None, None)          # lone BL suffix
    if h >= 0xE800:
        return (2, 'invalid', None, None)          # undefined on ARMv4T
    if h >= 0xE000:                               # b
        off = (h & 0x7FF) << 1
        if off & 0x800:
            off -= 0x1000
        t = o + 4 + off
        return (2, 'term' if t == o else 'b', t, None)
    if h >= 0xDF00:
        return (2, 'fall', None, None)            # swi
    if h >= 0xD000:                               # conditional branch
        off = (h & 0xFF) << 1
        if off & 0x100:
            off -= 0x200
        return (2, 'bcond', o + 4 + off, None)
    if h >= 0xC000:
        return (2, 'fall', None, None)            # ldm/stm
    if h >= 0xBE00:
        return (2, 'invalid', None, None)          # bkpt / undefined
    if h >= 0xBC00:                               # pop
        return (2, 'term' if (h & 0x0100) else 'fall', None, None)
    if h >= 0xB600:
        return (2, 'invalid', None, None)         # undefined on ARMv4T
    if h >= 0xB400:
        return (2, 'fall', None, None)            # push
    if h >= 0xB100:
        return (2, 'invalid', None, None)         # undefined on ARMv4T
    if h >= 0xB000:
        return (2, 'fall', None, None)            # add/sub sp,#imm
    if h >= 0xA000:
        return (2, 'fall', None, None)            # adr
    if h >= 0x9000:
        return (2, 'fall', None, None)            # ldr/str sp-relative
    if h >= 0x8000:
        return (2, 'fall', None, None)            # ldrh/strh
    if h >= 0x6000:
        return (2, 'fall', None, None)            # ldr/str imm offset
    if h >= 0x5000:
        return (2, 'fall', None, None)            # ldr/str reg offset
    if h >= 0x4800:                               # ldr rD,[pc,#imm]
        return (2, 'ldrpool', ((o + 4) & ~3) + ((h & 0xFF) << 2),
                (h >> 8) & 7)
    if h >= 0x4780:
        return (2, 'invalid', None, None)          # blx: ARMv5T only
    if h >= 0x4700:                               # bx
        rm = (h >> 3) & 0xF
        if rm == 14:
            return (2, 'term', None, None)         # bx lr
        if rm == 15:
            return (2, 'term', None, 'bx_pc_anom')  # bx pc: pathological
        return (2, 'bx', None, rm)
    if h >= 0x4400:                               # hi-reg ops
        if ((h >> 8) & 3) == 2:                   # mov
            # CORRECTED: bit6 -> Rs high, bit7 -> Rd high
            Rs = ((h >> 3) & 7) | (((h >> 6) & 1) << 3)
            Rd = (h & 7) | (((h >> 7) & 1) << 3)
            if Rd == 15:
                if Rs == 14:
                    return (2, 'term', None, None)   # mov pc,lr: return
                return (2, 'bx', None, Rs)            # mov pc,rX: indirect
        return (2, 'fall', None, None)
    # 0x0000-0x43FF: shifts, add/sub, mov/cmp/add/sub imm, ALU.
    return (2, 'fall', None, None)

COND_NAMES = ['eq', 'ne', 'cs', 'cc', 'mi', 'pl', 'vs', 'vc',
              'hi', 'ls', 'ge', 'lt', 'gt', 'le', '', 'nv']


def cond_name_thumb(h):
    return COND_NAMES[(h >> 8) & 0xF]


def cond_name_arm(w):
    return COND_NAMES[w >> 28]


# --------------------------------------------------------------------------
# 2. Per-function recursive descent with register-tag tracking.
# --------------------------------------------------------------------------
def tag_fall_through(pm, pc, raw, curmap):
    """Apply pop-tag / clobber rules for 'fall'-kind insns (mirrors gen v2)."""
    if pm == 'T' and 0xBC00 <= raw <= 0xBDFF and not (raw & 0x0100):
        for r in range(8):
            if (raw >> r) & 1:
                curmap[r] = (G.TAG_POP, None, None)
    elif pm == 'ARM' and ((raw >> 25) & 7) == 4 and ((raw >> 20) & 1) \
            and not (raw & (1 << 15)):
        for r in range(16):
            if (raw >> r) & 1:
                curmap[r] = (G.TAG_POP, None, None)
    else:
        clob = (G.thumb_clobber(raw) if pm == 'T'
                else G.arm_clobber(raw, 'fall'))
        for r in clob:
            curmap.pop(r, None)


def decode_func(s):
    """Returns (insns, edges, unres, stats).
    insns: {(pc,mode): (size,kind,tgt,extra,raw)}
    edges: list of tuples, first element is the kind tag
    unres: list of unresolved-indirect-branch records
    stats: per-function pattern counters"""
    m = starts[s]['mode']
    seen = set()
    insns = {}
    edges = []
    unres = []
    st = {'n': 0, 'bytes': 0, 'swi': 0, 'push': 0, 'pop': 0,
          'byte_mem': 0, 'word_mem': 0, 'shift': 0, 'mul': 0,
          'back_branch': False}
    work = [(s, m, {})]
    steps = 0
    while work:
        a, pm, rm0 = work.pop()
        pc = a
        curmap = dict(rm0)
        prev_mov_lr_pc = False
        while True:
            steps += 1
            if steps > 200000:
                unres.append((s, a, pm, -1, 'step-cap'))
                break
            key = (pc, pm)
            if key in seen:
                break
            seen.add(key)
            # hard boundary: another function start
            if pc != s and pc in starts:
                break
            if not (G.MIN_CODE <= pc < G.CODE_END):
                break
            if pm == 'T' and (pc & 1):
                break
            if pm == 'ARM' and (pc & 3):
                break
            size, kind, tgt, extra = (dec_thumb(pc) if pm == 'T'
                                     else G.dec_arm(pc))
            if kind == 'invalid':
                unres.append((s, pc, pm, -1, 'invalid-encoding'))
                break
            raw = G.u32(pc) if pm == 'ARM' else G.u16(pc)
            insns[key] = (size, kind, tgt, extra, raw)
            st['n'] += 1
            st['bytes'] = max(st['bytes'], pc + size - s)
            # raw pattern tallies
            if pm == 'T':
                h = raw
                if 0xDF00 <= h <= 0xDFFF:
                    st['swi'] += 1
                if 0xB400 <= h <= 0xB5FF:
                    st['push'] += 1
                if 0xBC00 <= h <= 0xBDFF:
                    st['pop'] += 1
                if h < 0x2000:
                    st['shift'] += 1
                if 0x4340 <= h <= 0x4347:
                    st['mul'] += 1
                if 0x5000 <= h < 0x6000:
                    if (h >> 10) & 1:
                        st['byte_mem'] += 1
                    else:
                        st['word_mem'] += 1
                elif 0x6000 <= h < 0x7000:
                    st['word_mem'] += 1
                elif 0x7000 <= h < 0x8000:
                    st['byte_mem'] += 1
            else:
                w = raw
                if (w & 0x0F000000) == 0x0F000000:
                    st['swi'] += 1
                if (w & 0x0FC000F0) == 0x00000090:
                    st['mul'] += 1

            is_mov_lr_pc = ((pm, raw) in G.MOV_LR_PC)

            if kind == 'fall':
                tag_fall_through(pm, pc, raw, curmap)
                prev_mov_lr_pc = is_mov_lr_pc
                pc += size
                continue
            if kind == 'ldrpool':
                pa, rd = tgt, extra
                if G.MIN_CODE <= pa <= G.CODE_END - 4:
                    v = G.u32(pa)
                    edges.append(('pool', pc, pa, rd, v))
                    curmap[rd] = (G.TAG_POOL, pa, v)
                prev_mov_lr_pc = is_mov_lr_pc
                pc += size
                continue
            if kind == 'ldrppc':
                pa = tgt
                if G.MIN_CODE <= pa <= G.CODE_END - 4:
                    v = G.u32(pa)
                    t2, m2 = G.rom2file(v)
                    edges.append(('dataptr', pc, pa, v, t2, m2))
                break  # ldr pc never falls through
            if kind == 'bl':
                t2 = (tgt & ~1) if pm == 'T' else tgt
                edges.append(('bl', pc, t2, pm))
                prev_mov_lr_pc = is_mov_lr_pc
                pc += size
                continue
            if kind == 'b':
                t2 = tgt & ~1
                if t2 < pc:
                    st['back_branch'] = True
                if t2 in starts:
                    edges.append(('tailcall', pc, t2, pm,
                                  'self' if t2 == s else ''))
                    break
                oc = owner.get((t2, pm))
                if oc is not None and oc != s:
                    edges.append(('tailcall', pc, t2, pm, 'mid-body'))
                    break
                work.append((t2, pm, dict(curmap)))
                break
            if kind == 'bcond':
                t2 = tgt & ~1
                if t2 < pc:
                    st['back_branch'] = True
                cn = (cond_name_thumb(raw) if pm == 'T'
                      else cond_name_arm(raw))
                edges.append(('bcond', pc, t2, pm, cn))
                work.append((t2, pm, dict(curmap)))
                prev_mov_lr_pc = is_mov_lr_pc
                pc += size
                continue
            if kind == 'bx':
                rm = extra
                tag = curmap.get(rm)
                if tag is not None and tag[0] == G.TAG_POOL:
                    _, pa, v = tag
                    t2, m2 = G.rom2file(v)
                    if t2 is not None:
                        if prev_mov_lr_pc:
                            edges.append(('bx', pc, t2, m2, pa,
                                          'call (mov lr,pc); mode-switch'))
                            insns[key] = (size, 'bxcall', tgt, extra, raw)
                            prev_mov_lr_pc = is_mov_lr_pc
                            pc += size
                            continue
                        edges.append(('bx', pc, t2, m2, pa, 'tail-jump'))
                    else:
                        unres.append((s, pc, pm, rm,
                                      'bx-pool-not-code val=%s' % H8(v)))
                elif tag is not None and tag[0] == G.TAG_POP:
                    pass  # pop {..,rN}; bx rN: ordinary return
                else:
                    unres.append((s, pc, pm, rm, 'bx-indirect'))
                break
            if kind == 'term':
                break
            unres.append((s, pc, pm, -1, 'unknown-kind-%s' % kind))
            break
    return insns, edges, unres, st


def resolve_dst(t2, pm):
    """Resolve a code target to (sym, note)."""
    if t2 in starts:
        return starts[t2]['sym'], ''
    oc = owner.get((t2, pm))
    if oc is not None:
        return starts[oc]['sym'], 'target mid-body'
    return '', 'target unowned'


# --------------------------------------------------------------------------
# 3. Decode everything; collect edges.
# --------------------------------------------------------------------------
all_insns = {}   # (pc,mode) -> (start, size, kind, tgt, extra, raw)
rows = []        # xrefs.tsv rows (without header)
unres_rows = []
pool_words = {}  # pool file offset -> value
func_bodies = {}  # start -> set of (pc,mode)
func_stats = {}
diag_owner_mismatch = 0
diag_owner_checked = 0

for i, s in enumerate(sorted(starts)):
    insns, edges, unres, st = decode_func(s)
    func_stats[s] = st
    body = set(insns)
    func_bodies[s] = body
    for (pc, pm), (size, kind, tgt, extra, raw) in insns.items():
        all_insns[(pc, pm)] = (s, size, kind, tgt, extra, raw)
        oc = owner.get((pc, pm))
        if oc is not None:
            diag_owner_checked += 1
            if oc != s:
                diag_owner_mismatch += 1
    sym = starts[s]['sym']
    off = H6(s)
    for e in edges:
        k = e[0]
        if k == 'bl':
            _, pc, t2, pm = e
            dsym, note = resolve_dst(t2, pm)
            rows.append((sym, off, H6(pc), 'bl', dsym, H6(t2), note))
        elif k == 'bx':
            _, pc, t2, m2, pa, note = e
            dsym, note2 = resolve_dst(t2, m2)
            if note2:
                note = note + '; ' + note2
            rows.append((sym, off, H6(pc), 'bx', dsym, H6(t2),
                         'via pool %s (%s); %s' % (H6(pa), ROMV(pa), note)))
        elif k == 'pool':
            _, pc, pa, rd, v = e
            pool_words.setdefault(pa, v)
            rows.append((sym, off, H6(pc), 'pool', '', H6(pa),
                         'ldr r%d <- [%s]=%s' % (rd, ROMV(pa), H8(v))))
        elif k == 'dataptr':
            _, pc, pa, v, t2, m2 = e
            pool_words.setdefault(pa, v)
            if t2 is not None:
                dsym, note = resolve_dst(t2, m2)
                if note:
                    note = '; ' + note
                note = 'ldr pc <- [%s]=%s -> %s%s' % (
                    ROMV(pa), H8(v), ROMV(t2), note)
                rows.append((sym, off, H6(pc), 'dataptr', dsym, H6(pa),
                             note))
            else:
                rows.append((sym, off, H6(pc), 'dataptr', '', H6(pa),
                             'ldr pc <- [%s]=%s (not code)' % (
                                 ROMV(pa), H8(v))))
        elif k == 'bcond':
            _, pc, t2, pm, cn = e
            dsym, note = resolve_dst(t2, pm)
            if t2 in body or (t2, pm) in body:
                if not dsym:
                    dsym, note = sym, 'internal'
                elif note == '':
                    note = 'internal'
            rows.append((sym, off, H6(pc), 'bcond', dsym, H6(t2),
                         ('b%s' % cn) + ('; ' + note if note else '')))
        elif k == 'tailcall':
            _, pc, t2, pm, note = e
            dsym, note2 = resolve_dst(t2, pm)
            if note2 and note2 not in note:
                note = (note + '; ' + note2).strip('; ')
            rows.append((sym, off, H6(pc), 'tailcall', dsym, H6(t2), note))
    for (us, upc, upm, reg, detail) in unres:
        unres_rows.append((starts[us]['sym'], H6(us), H6(upc), upm,
                           'r%d' % reg if reg >= 0 else '-', detail))

print('owner agreement vs v2 map (built with buggy hi-reg mov decoder): '
      '%d/%d insns match; mismatches expected at mov-pc/mov-r7 sites'
      % (diag_owner_checked - diag_owner_mismatch, diag_owner_checked),
      file=sys.stderr)

rows.sort(key=lambda r: (r[1], r[2], r[3]))

with open(DOCS + '/xrefs.tsv', 'w') as f:
    f.write('src_func\toffset\tsrc_addr\tkind\tdst_func\tdst_offset\tnote\n')
    for r in rows:
        f.write('\t'.join(r) + '\n')

with open(DOCS + '/xrefs_unresolved.tsv', 'w') as f:
    f.write('src_func\toffset\tsrc_addr\tmode\treg\tdetail\n')
    for r in sorted(unres_rows):
        f.write('\t'.join(r) + '\n')

with open(DOCS + '/func_stats.tsv', 'w') as f:
    f.write('off\tsym\ttier\tmode\tn_insn\tsize_bytes\tn_bl\tn_bx\t'
            'n_bcond\tn_pool\tn_dataptr\tn_swi\thas_loop\t'
            'n_byte_mem\tn_word_mem\tn_shift\tn_mul\n')
    # recompute per-kind edge counts per function for stats
    per = defaultdict(lambda: defaultdict(int))
    for r in rows:
        # r = (src_func, off, src_addr, kind, dst_func, dst_offset, note)
        per[r[1]][r[3]] += 1
    for s in sorted(starts):
        st = func_stats[s]
        e = per[H6(s)]
        f.write('\t'.join(map(str, [
            H6(s), starts[s]['sym'], starts[s]['tier'], starts[s]['mode'],
            st['n'], st['bytes'], e['bl'], e['bx'], e['bcond'], e['pool'],
            e['dataptr'], st['swi'], int(st['back_branch']),
            st['byte_mem'], st['word_mem'], st['shift'], st['mul']])) + '\n')

print('xrefs.tsv: %d rows; unresolved: %d; pools: %d'
      % (len(rows), len(unres_rows), len(pool_words)), file=sys.stderr)

# --------------------------------------------------------------------------
# 4. Whole-ROM data code-pointer scan.
#    Every aligned 32-bit word v with 0x08000000 <= v <= 0x0804FFFF whose
#    target lands in the code region [MIN_CODE, CODE_END).
# --------------------------------------------------------------------------
rom = G.rom
nwords = len(rom) // 4
code_bytes = set()
for (pc, pm), (s, size, _k, _t, _e, _r) in all_insns.items():
    for i in range(pc, pc + size):
        code_bytes.add(i)

dp_rows = []
mv = memoryview(rom)
for wi in range(nwords):
    o = wi * 4
    v = struct.unpack_from('<I', mv, o)[0]
    if not (0x08000000 <= v <= 0x0804FFFF):
        continue
    t = (v & ~1) - G.BASE
    if not (G.MIN_CODE <= t < G.CODE_END):
        continue
    m2 = 'T' if (v & 1) else 'ARM'
    if t in starts:
        tf, note = starts[t]['sym'], 'start'
    else:
        oc = owner.get((t, m2))
        tf = starts[oc]['sym'] if oc is not None else ''
        note = 'mid-body' if oc is not None else 'unowned'
    if o in code_bytes:
        cls = 'code'
    elif o in pool_words:
        cls = 'pool'
    else:
        cls = 'data'
    dp_rows.append((o, v, t, m2, tf, note, cls, o in pool_words))

with open(DOCS + '/xrefs_dataptrs.tsv', 'w') as f:
    f.write('word_off\tvalue\ttarget_off\tmode\ttarget_func\ttarget_note\t'
            'class_at_word\tis_literal_pool\n')
    for (o, v, t, m2, tf, note, cls, ispool) in dp_rows:
        f.write('\t'.join([H8(o), H8(v), H6(t), m2, tf, note, cls,
                            str(ispool)]) + '\n')

print('dataptrs: %d code-pointer words in ROM' % len(dp_rows),
      file=sys.stderr)

# --------------------------------------------------------------------------
# 5. Summary stats for the report (stdout).
# --------------------------------------------------------------------------
from collections import Counter
kind_counts = Counter(r[3] for r in rows)
print('EDGE_KINDS ' + ' '.join('%s=%d' % kv
                               for kv in sorted(kind_counts.items())))
# incoming call counts (bl + call-bx + tailcall), distinct callers + total
callers = defaultdict(set)
calls = Counter()
for r in rows:
    if r[3] == 'bl' or r[3] == 'tailcall' or (
            r[3] == 'bx' and 'call (mov lr,pc)' in r[6]):
        if r[4]:
            callers[r[4]].add(r[0])
            calls[r[4]] += 1
top = sorted(calls, key=lambda k: (-len(callers[k]), -calls[k]))[:20]
print('TOP_CALLEES')
for k in top:
    print('  %s callers=%d edges=%d' % (k, len(callers[k]), calls[k]))
# functions with no bl/bx-call/tailcall callers at all
uncalled = [starts[s]['sym'] for s in sorted(starts)
            if starts[s]['sym'] not in calls]
print('UNCALLED %d: %s' % (len(uncalled), ' '.join(uncalled[:40])))
# table-only-called: dataptr target, not a call target
table_targets = set()
for (o, v, t, m2, tf, note, cls, ispool) in dp_rows:
    if tf and cls != 'pool' and tf not in calls:
        table_targets.add(tf)
print('TABLE_ONLY %d: %s' % (len(table_targets),
                             ' '.join(sorted(table_targets))))
