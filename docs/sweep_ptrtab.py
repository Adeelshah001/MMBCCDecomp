#!/usr/bin/env python3
"""Pointer-table scan: 0x0800xxxx words (whole ROM) targeting unknown code
in 0-0x50000. Validate each unlisted target. Group consecutive pointers as
tables."""
import sys, struct
from collections import defaultdict
import gen_func_list_v2 as g

rom = g.rom
def u32(off): return struct.unpack_from('<I', rom, off)[0]

spans = []
for line in open('byteclass.tsv'):
    line = line.strip()
    if not line or line.startswith('#'): continue
    rng, cls = line.split()
    a, b = rng.split('-')
    spans.append((int(a,16), int(b,16), cls))
def bcls(off):
    for s,e,c in spans:
        if s <= off <= e: return c
    return '?'

listed = set()
for fn in ('func_list_v2.txt', 'func_list_v2_1_addendum.txt', 'func_list_v2_2_addendum.txt'):
    for line in open(fn):
        line = line.strip()
        if line and not line.startswith('#'):
            listed.add(int(line.split()[0], 16))

# scan whole ROM for pointers into 0..0x50000 unknown
ptr_to = defaultdict(list)  # target -> [pointer locations]
for off in range(0, len(rom)-4, 4):
    w = u32(off)
    if 0x08000000 <= w < 0x08050000:
        t = w - 0x08000000
        # Thumb pointer: bit0 set; ARM: bit0 clear and 4-aligned
        tgt = t & ~1
        if bcls(tgt) == 'unknown' and tgt not in listed:
            ptr_to[tgt].append(off)

print(f"unlisted unknown targets with pointers: {len(ptr_to)}", file=sys.stderr)
# filter: need >=2 pointers (a table) OR validate True; skip isolated singles in noise
results = []
for tgt in sorted(ptr_to):
    locs = ptr_to[tgt]
    # check if part of a run (table): consecutive pointers
    v = g.validate_target(tgt, 'T') if (tgt & 1) == 0 else g.validate_target(tgt, 'ARM')
    results.append((tgt, len(locs), v))
    if len(locs) >= 2 or v:
        print(f"  {tgt:05X}: {len(locs)} ptrs validate={v} "
              f"locs={[f'{l:06X}' for l in locs[:4]]}")
print(f"total with >=2 ptrs or validate: "
      f"{sum(1 for _,n,v in results if n>=2 or v)}", file=sys.stderr)
