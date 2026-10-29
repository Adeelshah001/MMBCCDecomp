#!/usr/bin/env python3
"""Delimit thunk cluster v2: validate each start, inspect gaps/tails."""
import sys, struct
import gen_func_list_v2 as g

rom = g.rom
def u16(off): return struct.unpack_from('<H', rom, off)[0]
def u32(off): return struct.unpack_from('<I', rom, off)[0]

def thumb_bl_target(bl_off):
    hi = u16(bl_off); lo = u16(bl_off + 2)
    if (hi & 0xF800) != 0xF000 or (lo & 0xF800) != 0xF800: return None
    off = ((hi & 0x7FF) << 12) | ((lo & 0x7FF) << 1)
    if off & (1 << 22): off -= (1 << 23)
    tgt = bl_off + 4 + off
    return tgt if 0 <= tgt < 0x50000 else None

THUNK = (0x1C38, 0x4649, 0x4652, 0x9B08)
thunks = []
for off in range(0x029000, 0x02CC00, 2):
    if (u16(off), u16(off+2), u16(off+4), u16(off+6)) == THUNK:
        thunks.append(off)

# 1. validate_target each thunk start
ok = [t for t in thunks if g.validate_target(t, 'T')]
print(f"validate_target T: {len(ok)}/{len(thunks)} pass")
bad = [t for t in thunks if not g.validate_target(t, 'T')]
print("fails:", [f'{t:05X}' for t in bad])

# 2. large gaps: list them
print("large gaps (>=200):")
for i, t in enumerate(thunks):
    if i + 1 < len(thunks):
        gap = thunks[i+1] - t
        if gap >= 200:
            print(f"  {t:05X} -> {thunks[i+1]:05X} gap={gap}")

# 3. region before first thunk and after last thunk: is it really unknown?
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
print("class @29AC4-2:", bcls(0x29AC2), " @2C70C+14:", bcls(0x2C71A))

# 4. dump full disassembly of 2 representative thunks via gen decoder
for t in (thunks[0], thunks[50], thunks[-1]):
    print(f"--- thunk {t:05X} (next starts +{thunks[thunks.index(t)+1]-t if thunks.index(t)+1<len(thunks) else 'END'})")
    off = t
    for _ in range(24):
        d = g.dec_thumb(off)
        if d is None:
            print(f"  {off:05X}: <invalid>"); break
        print(f"  {off:05X}: {d}")
        off += 2 * (2 if getattr(d, 'wide', False) else 1)
        if off >= (thunks[thunks.index(t)+1] if thunks.index(t)+1 < len(thunks) else t+80):
            break
