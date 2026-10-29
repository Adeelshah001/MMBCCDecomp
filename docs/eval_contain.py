#!/usr/bin/env python3
"""Evaluate non-span contains_v1 D entries (excluding 04DE70/04DEE8 already B
via v2.2, and 04DDA0 already rejected in v2.2): BL callers + validate."""
import sys, struct
from collections import defaultdict
import gen_func_list_v2 as g

rom = g.rom
def u16(off): return struct.unpack_from('<H', rom, off)[0]
def u32(off): return struct.unpack_from('<I', rom, off)[0]
def bt(bl):
    hi = u16(bl); lo = u16(bl+2)
    if (hi & 0xF800) != 0xF000 or (lo & 0xF800) != 0xF800: return None
    o = ((hi & 0x7FF) << 12) | ((lo & 0x7FF) << 1)
    if o & (1 << 22): o -= (1 << 23)
    t = bl + 4 + o
    return t if 0 <= t < 0x50000 else None

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

co = defaultdict(list)
for off in range(0, 0x50000-4, 2):
    hi = u16(off)
    if (hi & 0xF800) == 0xF000 and (u16(off+2) & 0xF800) == 0xF800:
        t = bt(off)
        if t is not None: co[t].append(off)

cands = [0x033962, 0x03B3E8, 0x04B514, 0x04B528, 0x04B52C, 0x04B530,
         0x04B534, 0x04B538, 0x04DDA0]
for o in cands:
    v = g.validate_target(o, 'T')
    callers = co.get(o, [])
    cls = [bcls(c) for c in callers]
    print(f"{o:05X}: validate={v} callers={len(callers)} caller_classes={set(cls)}")
    # show first few instructions
    for off in range(o, o+12, 2):
        d = g.dec_thumb(off)
        print(f"    {off:05X}: {u16(off):04X} {d[1] if d else None}")
        if off >= o+8: break
