#!/usr/bin/env python3
"""Wave 8 leaves-up layer computation (direct ROM scan).

Leaves-up layer = functions F (unmatched, unblocked, not excluded) where
every bl callee of F (found by DIRECT disassembly scan of the ROM bytes,
not xrefs.tsv) resolves to a function that is already MATCHED.

Rationale: xrefs.tsv is incomplete for some functions (Wave 6 L1 lesson:
0x0803048C has 43 real bls, 0 bl edges in xrefs.tsv). Direct scanning is
ground truth for bl instructions.

Excludes:
  - the 4 xref-incomplete L1 dispatchers (0x08036A14/0x08036DAC/
    0x08039058/0x080493EC)
  - Vec2_CopyMirrored, Sram_VerifyCompare, MainLoop, ChipSlot_Tick
  - interior-demoted entries (v2.6, v2.7)
  - functions whose bl targets cannot be resolved to matched functions

Bl target -> containing function via func_stats extents. A target is
"matched" if its containing function is in the MATCHED set.

Usage: python3 gen_wave8_layer.py
Writes docs/wave8_layer.tsv
"""
import csv, os, struct

DOCS = os.path.dirname(os.path.abspath(__file__))
BASE = 0x08000000
ROM_PATH = '/home/hatch/workspace/megaman-bcc-recomp/rom/Mega_Man_-_Battle_Chip_Challenge__USA__0_8r4i.gba'

LEAVE_ALONE = {0x0800DD08, 0x0804DC00, 0x080004FC, 0x0800D9FC,
               0x0804CDE8}  # +Text_OpenDialogue: leave-alone, no new angles
L1_DISPATCHERS = {0x08036A14, 0x08036DAC, 0x08039058, 0x080493EC}

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

def main():
    rom = open(ROM_PATH, 'rb').read()
    funcs = load_funcs()
    matched, blocked, other = load_status()
    ext = load_extents()
    sizes = {o: e - s for s, e, o in ext}

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
            cand.append((off, size, sym, len(targets), ';'.join(sorted(set(callee_names)))))

    cand.sort(key=lambda x: -x[1])
    out = os.path.join(DOCS, 'wave8_layer.tsv')
    with open(out, 'w', newline='') as f:
        w = csv.writer(f, delimiter='\t')
        w.writerow(['address', 'size_bytes', 'sym', 'n_bl', 'callee_offs'])
        for off, sz, sym, n, cl in cand:
            w.writerow(['0x08%s' % off.lower(), sz, sym, n, cl])
    print(f'layer size: {len(cand)} -> {out}')
    print(f'total bytes: {sum(c[1] for c in cand)}')
    print(f'skipped (unresolved target): {skipped_unresolved}')

if __name__ == '__main__':
    main()
