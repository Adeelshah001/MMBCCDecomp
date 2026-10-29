#!/usr/bin/env python3
"""Wave 25 leaves-up layer computation (direct ROM scan).

Same algorithm as gen_wave21_layer.py, adapted for wave 25:
- leaves = unmatched, unblocked, not otherwise registered, not excluded
  functions whose bl-callees ALL resolve to MATCHED functions.
- Exclude wave-19/20 off-limits twins/pool cluster (explicit per worker
  brief; members are registered MATCHED anyway).
- "newly enabled" column counts callees landed in wave 21.
- Exclude the 4 xref-incomplete L1 dispatchers until their callees land.
- Sorted by distinct-caller count (desc), then size (asc).
"""
import csv, os, struct

DOCS = os.path.dirname(os.path.abspath(__file__))
BASE = 0x08000000
ROM_PATH = '/home/hatch/workspace/megaman-bcc-recomp/rom/Mega_Man_-_Battle_Chip_Challenge__USA__0_8r4i.gba'

LEAVE_ALONE = {0x0800DD08, 0x0804DC00, 0x080004FC, 0x0800D9FC}
L1_DISPATCHERS = {0x08036A14, 0x08036DAC, 0x08039058, 0x080493EC}

# Wave-19/20/21 off-limits twins/pool cluster (landed by 19-C/19-D/20; registered
# MATCHED anyway, but excluded explicitly per worker briefs):
W22_OFFLIMITS = {
    0x0800FFF4, 0x0801009C, 0x08017620, 0x08017D00,
    0x080250BC, 0x08022868, 0x08020340, 0x0803E9BC,
}


def load_funcs():
    funcs = {}
    with open(os.path.join(DOCS, 'func_list_v2.txt')) as f:
        for line in f:
            line = line.strip()
            if not line or line.startswith('#'):
                continue
            parts = line.split()
            if parts[1] in ('A', 'B'):
                funcs[parts[0].upper()] = parts[3] if len(parts) > 3 else 'sub_08' + parts[0].upper()
    with open(os.path.join(DOCS, 'func_list_v2_5_addendum.txt')) as f:
        for line in f:
            line = line.strip()
            if not line or line.startswith('#'):
                continue
            parts = line.split()
            off = parts[0]
            if off.startswith('0x') or off.startswith('0X'):
                off = off[2:]
            off = off.upper().zfill(6)[-6:]
            sym = parts[2] if len(parts) > 2 else 'sub_08' + off
            funcs[off] = sym
    for fn in ('func_list_v2_6_addendum.txt', 'func_list_v2_7_addendum.txt'):
        p = os.path.join(DOCS, fn)
        if os.path.exists(p):
            for line in open(p):
                line = line.strip()
                if line.startswith('0x080'):
                    funcs.pop(line[3:9].upper(), None)
    for dead in ('03D9EC', '03C20E', '02C6E6'):
        funcs.pop(dead, None)
    return funcs


def load_status():
    matched, blocked, other = set(), set(), set()
    with open(os.path.join(DOCS, 'match_status.tsv')) as f:
        r = csv.DictReader(f, delimiter='\t')
        for row in r:
            a = row['address'].strip().lower()
            st = row['status'].strip()
            if st == 'MATCHED':
                matched.add(a)
            elif st == 'BLOCKED':
                blocked.add(a)
            else:
                other.add(a)
    return matched, blocked, other


def load_wave_new(wave):
    s = set()
    with open(os.path.join(DOCS, 'match_status.tsv')) as f:
        r = csv.DictReader(f, delimiter='\t')
        for row in r:
            if row.get('wave', '').strip() == str(wave) and row.get('status', '').strip() == 'MATCHED':
                s.add(row['address'].strip().lower())
    return s


def load_extents():
    ext = []
    with open(os.path.join(DOCS, 'func_stats.tsv')) as f:
        r = csv.DictReader(f, delimiter='\t')
        for row in r:
            off = int(row['off'].strip(), 16)
            sz = int(row['size_bytes'])
            ext.append((off, off + sz, row['off'].strip().upper().zfill(6)[-6:]))
    ext.sort()
    return ext


def containing(ext, target_off):
    for s, e, off in ext:
        if s <= target_off < e:
            return off
    return None


def bl_targets(rom, addr, size):
    out = []
    data = rom[addr - BASE:addr - BASE + size]
    i = 0
    n = len(data)
    while i + 4 <= n:
        h1 = struct.unpack_from('<H', data, i)[0]
        if 0xF000 <= h1 <= 0xF7FF:
            h2 = struct.unpack_from('<H', data, i + 2)[0]
            if 0xF800 <= h2 <= 0xFFFF:
                off = ((h1 & 0x7FF) << 12) | ((h2 & 0x7FF) << 1)
                if off & 0x400000:
                    off -= 0x800000
                out.append((addr + i + 4 + off) & 0xFFFFFFFF)
                i += 4
                continue
        i += 2
    return out


def load_caller_counts():
    callers = {}
    with open(os.path.join(DOCS, 'xrefs.tsv')) as f:
        r = csv.DictReader(f, delimiter='\t')
        for row in r:
            if row['kind'] not in ('bl', 'call', 'b'):
                continue
            src = row['src_offset'].strip().upper() if 'src_offset' in row else row['offset'].strip().upper()
            dst = row['dst_offset'].strip().upper()
            callers.setdefault(dst, set()).add(src)
    return {k: len(v) for k, v in callers.items()}


def main():
    rom = open(ROM_PATH, 'rb').read()
    funcs = load_funcs()
    matched, blocked, other = load_status()
    w22new = load_wave_new(23)
    ext = load_extents()
    sizes = {o: e - s for s, e, o in ext}
    callers = load_caller_counts()
    print(f'wave23 new matches: {len(w22new)} (all MATCHED in registry: {sum(1 for a in w22new if a in matched)})')
    print(f'funcs: {len(funcs)}, matched: {len(matched)}, blocked: {len(blocked)}, other: {len(other)}')

    cand, skipped_unresolved, skipped_unmatched_cal, skipped_offlimits = [], 0, 0, 0
    for off, sym in funcs.items():
        addr = BASE + int(off, 16)
        a = ('0x%08x' % addr).lower()
        if a in matched or a in blocked or a in other:
            continue
        if addr in LEAVE_ALONE or addr in L1_DISPATCHERS or addr in W22_OFFLIMITS:
            if addr in W22_OFFLIMITS:
                skipped_offlimits += 1
            continue
        size = sizes.get(off, 0)
        if size <= 0:
            continue
        targets = bl_targets(rom, addr, size)
        ok = True
        callee_names = []
        for t in targets:
            coff = containing(ext, t - BASE)
            if coff is None:
                ok = False
                skipped_unresolved += 1
                break
            ca = '0x08%s' % coff.lower()
            if ca not in matched:
                ok = False
                skipped_unmatched_cal += 1
                break
            callee_names.append(ca)
        if ok:
            callee_set = sorted(set(callee_names))
            w22n = sum(1 for c in callee_set if c in w22new)
            cand.append((off, size, sym, len(targets), ';'.join(callee_set), w22n))

    cand.sort(key=lambda x: (-callers.get(x[0].upper(), 0), x[1]))
    out = os.path.join(DOCS, "wave25_layer.tsv")
    with open(out, 'w', newline='') as f:
        w = csv.writer(f, delimiter='\t')
        w.writerow(['address', 'size_bytes', 'sym', 'n_bl', 'callee_offs', 'w25_new_cal', 'n_callers'])
        for off, sz, sym, n, cl, w22n in cand:
            w.writerow(['0x08%s' % off.lower(), sz, sym, n, cl, w22n, callers.get(off.upper(), 0)])
    new_enabled = [c for c in cand if c[5] > 0]
    print(f'layer size: {len(cand)} -> {out}')
    print(f'newly enabled by wave21 (w25_new_cal>0): {len(new_enabled)}')
    print(f'skipped (unresolved target): {skipped_unresolved}, skipped (unmatched callee): {skipped_unmatched_cal}, off-limits: {skipped_offlimits}')
    print('--- top 45 by caller count ---')
    for off, sz, sym, n, cl, w22n in cand[:45]:
        print('0x08%s\t%d\t%s\tn_bl=%d\tw20=%d\tcallers=%d' % (off.lower(), sz, sym, n, w22n, callers.get(off.upper(), 0)))


if __name__ == '__main__':
    main()
