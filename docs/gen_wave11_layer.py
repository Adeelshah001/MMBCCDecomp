#!/usr/bin/env python3
"""Wave 11 leaves-up layer computation (direct ROM scan).

Leaves-up layer = functions F (unmatched, unblocked, not otherwise
registered, not excluded) where every bl callee of F (found by DIRECT
disassembly scan of the ROM bytes, not xrefs.tsv) resolves to a function
that is already MATCHED.

Adds a column w10_new_cal: how many of F's distinct bl-callee offsets are
in the newly-landed Wave 10 MATCHED set (re-derived from the wave10
results tsvs). Candidates with w10_new_cal>0 were newly enabled by Wave 10.

Excludes mirror gen_wave7_layer.py (L1 dispatchers, LEAVE_ALONE, interior
demotions, etc).

Also computes caller counts from docs/xrefs.tsv (kind=call/bl) for ordering.

Writes docs/wave11_layer.tsv (all candidates) and prints the top-40-by-callers.
"""
import csv, os, struct

DOCS = os.path.dirname(os.path.abspath(__file__))
BASE = 0x08000000
ROM_PATH = '/home/hatch/workspace/megaman-bcc-recomp/rom/Mega_Man_-_Battle_Chip_Challenge__USA__0_8r4i.gba'

LEAVE_ALONE = {0x0800DD08, 0x0804DC00, 0x080004FC, 0x0800D9FC}
L1_DISPATCHERS = {0x08036A14, 0x08036DAC, 0x08039058, 0x080493EC}

W10_R = 'wave10_H_results.tsv, wave10_L_results.tsv, wave10_R_results.tsv, wave10_S_results.tsv, wave10_T_results.tsv'


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


def load_w9_new():
    s = set()
    for fn in W10_R.split(', '):
        with open(os.path.join(DOCS, fn)) as f:
            first = f.readline()
            if 'address' in first.split('\t')[0].lower() or 'name' in first.split('\t')[0].lower():
                # has header row
                r = csv.DictReader([first] + f.readlines(), delimiter='\t')
                for row in r:
                    if row.get('status', '').strip() == 'MATCHED':
                        s.add(row['address'].strip().lower())
            else:
                # headerless: name, address, bytes, status, ...
                for line in [first] + f.readlines():
                    parts = line.rstrip('\n').split('\t')
                    if len(parts) >= 4 and parts[3].strip() == 'MATCHED':
                        s.add(parts[1].strip().lower())
    return s


def load_extents():
    ext = []  # (start_off, end_off, off)
    with open(os.path.join(DOCS, 'func_stats.tsv')) as f:
        r = csv.DictReader(f, delimiter='\t')
        for row in r:
            off = int(row['off'].strip(), 16)
            sz = int(row['size_bytes'])
            ext.append((off, off + sz, row['off'].strip().upper()))
    ext.sort()
    return ext


def containing(ext, target_off):
    for s, e, off in ext:
        if s <= target_off < e:
            return off
    return None


def bl_targets(rom, addr, size):
    """ARMv4T Thumb BL scan. Returns list of absolute target addresses."""
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
    # distinct caller functions per callee offset (kind bl/call)
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
    w10new = load_w9_new()
    ext = load_extents()
    sizes = {o: e - s for s, e, o in ext}
    callers = load_caller_counts()
    print(f'wave10 new matches: {len(w10new)} (in status MATCHED: {sum(1 for a in w10new if a in matched)})')

    cand, skipped_unresolved = [], 0
    for off, sym in funcs.items():
        addr = BASE + int(off, 16)
        a = ('0x%08x' % addr).lower()
        if a in matched or a in blocked or a in other:
            continue
        if addr in LEAVE_ALONE or addr in L1_DISPATCHERS:
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
            ca = '0x%s' % coff.lower()
            if ca not in matched:
                ok = False
                break
            callee_names.append(coff)
        if ok:
            callee_set = sorted(set('0x' + c.lower() for c in callee_names))
            w8n = sum(1 for c in callee_set if c in w10new)
            cand.append((off, size, sym, len(targets), ';'.join(callee_set), w8n))

    cand.sort(key=lambda x: (-callers.get(x[0].upper(), 0), x[1]))
    out = os.path.join(DOCS, 'wave11_layer.tsv')
    with open(out, 'w', newline='') as f:
        w = csv.writer(f, delimiter='\t')
        w.writerow(['address', 'size_bytes', 'sym', 'n_bl', 'callee_offs', 'w10_new_cal', 'n_callers'])
        for off, sz, sym, n, cl, w8n in cand:
            w.writerow(['0x08%s' % off.lower(), sz, sym, n, cl, w8n, callers.get(off.upper(), 0)])
    new_enabled = [c for c in cand if c[5] > 0]
    print(f'layer size: {len(cand)} -> {out}')
    print(f'newly enabled by wave10 (w10_new_cal>0): {len(new_enabled)}')
    print(f'skipped (unresolved target): {skipped_unresolved}')
    print('--- top 40 by caller count ---')
    for off, sz, sym, n, cl, w8n in cand[:40]:
        print('0x08%s\t%d\t%s\tn_bl=%d\tw9=%d\tcallers=%d' % (off.lower(), sz, sym, n, w8n, callers.get(off.upper(), 0)))


if __name__ == '__main__':
    main()
