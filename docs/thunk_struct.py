#!/usr/bin/env python3
"""Structural analysis of the 29AC4-2C70C cluster: terminators, branch targets,
idiom variants, and what 2D7A0 is."""
import sys, struct
from collections import Counter
import gen_func_list_v2 as g

rom = g.rom
def u16(off): return struct.unpack_from('<H', rom, off)[0]

S, E = 0x29AC4, 0x2C7A4

# terminators in span
terms = Counter()
term_at = []
for off in range(S, E, 2):
    h = u16(off)
    if h == 0x4770:
        terms['bx_lr'] += 1; term_at.append((off, 'bx_lr'))
    elif (h & 0xFF00) == 0xBD00 and (h & 0x0100):
        terms['pop_pc'] += 1; term_at.append((off, 'pop_pc'))
    elif h == 0x46F5:
        pass
print("terminators in span:", dict(terms))
print("first 10:", [(f'{o:05X}', k) for o, k in term_at[:10]])

# idiom variants: 1C38 4649 XXXX 9B08 + BL
print("idiom-variant scan (1C38 4649 ???? 9B08 + BL pair):")
var = Counter()
varloc = []
for off in range(S, E, 2):
    if u16(off) == 0x1C38 and u16(off+2) == 0x4649 and u16(off+6) == 0x9B08:
        x3 = u16(off+4)
        hi, lo = u16(off+8), u16(off+10)
        isbl = (hi & 0xF800) == 0xF000 and (lo & 0xF800) == 0xF800
        var[(x3, isbl)] += 1
        varloc.append((off, x3, isbl))
for k, v in var.most_common():
    print(f"  third={k[0]:04X} bl={k[1]}: {v}")
print("variant (non-4652) locations:", [(f'{o:05X}', f'{x:04X}', b) for o, x, b in varloc if x != 0x4652][:20])

# what is 2D7A0?
print("2D7A0 disassembly (first 12 insns):")
off = 0x2D7A0
for _ in range(12):
    d = g.dec_thumb(off)
    if d is None: print(f"  {off:05X}: ???"); break
    print(f"  {off:05X}: {u16(off):04X} {d[1]}")
    off += d[0]

# known-list membership of 2D7A0
known = {}
for fn in ('func_list_v2.txt', 'func_list_v2_1_addendum.txt', 'func_list_v2_2_addendum.txt'):
    for line in open(fn):
        line = line.strip()
        if line and not line.startswith('#'):
            p = line.split()
            known[int(p[0], 16)] = (p[1], fn)
print("2D7A0 known:", known.get(0x2D7A0))

# branch targets from within span: where do internal b's go?
print("sample internal branch targets (first 8 thunks):")
THUNK = (0x1C38, 0x4649, 0x4652, 0x9B08)
thunks = [off for off in range(S, E, 2)
          if (u16(off), u16(off+2), u16(off+4), u16(off+6)) == THUNK]
for t in thunks[:8]:
    # linear scan of tail until next thunk, collect b targets
    off = t + 12
    nxt = thunks[thunks.index(t)+1] if thunks.index(t)+1 < len(thunks) else E
    tgts = []
    while off < nxt:
        h = u16(off)
        if (h & 0xF800) == 0xE000:
            so = (h & 0x7FF) << 1
            if so & 0x1000: so -= 0x2000
            tgts.append(off+4+so)
            off += 2
        elif (h & 0xF800) == 0xF000 and off+2 < nxt and (u16(off+2) & 0xF800) == 0xF800:
            off += 4
        else:
            off += 2
    print(f"  {t:05X}: b-targets -> {[f'{x:05X}' for x in tgts]}")
