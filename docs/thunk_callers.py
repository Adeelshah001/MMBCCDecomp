#!/usr/bin/env python3
"""Region-wide correct BL scan: which BLs (anywhere in ROM code regions)
target into the thunk span? Also: push/sub-sp prologue scan inside span."""
import sys, struct
from collections import Counter, defaultdict
import gen_func_list_v2 as g
from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB

rom = g.rom
def u16(off): return struct.unpack_from('<H', rom, off)[0]

S, E = 0x29AC4, 0x2C7A4

def thumb_bl_target(bl_off):
    hi = u16(bl_off); lo = u16(bl_off + 2)
    if (hi & 0xF800) != 0xF000 or (lo & 0xF800) != 0xF800: return None
    off = ((hi & 0x7FF) << 12) | ((lo & 0x7FF) << 1)
    if off & (1 << 22): off -= (1 << 23)
    tgt = bl_off + 4 + off
    return tgt if 0 <= tgt < 0x50000 else None

# BL scan over the whole 320KB region (code+unknown; BLs only valid in code
# but scan raw and filter by caller plausibility later)
callers_of = defaultdict(list)  # target -> [bl sites]
for off in range(0, 0x50000 - 4, 2):
    hi = u16(off)
    if (hi & 0xF800) == 0xF000 and (u16(off+2) & 0xF800) == 0xF800:
        t = thumb_bl_target(off)
        if t is not None and S <= t < E:
            callers_of[t].append(off)

print(f"distinct BL targets inside span: {len(callers_of)}")
# byteclass of callers: need spans
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

THUNK = (0x1C38, 0x4649, 0x4652, 0x9B08)
idioms = set(off for off in range(S, E, 2)
              if (u16(off),u16(off+2),u16(off+4),u16(off+6)) == THUNK)
print(f"idiom starts: {len(idioms)}")
n_idiom_targets = sum(1 for t in callers_of if t in idioms)
print(f"BL targets that are idiom starts: {n_idiom_targets}")
# non-idiom BL targets in span
nonidiom = {t: v for t, v in callers_of.items() if t not in idioms}
print(f"non-idiom BL targets in span: {len(nonidiom)}")
for t in sorted(nonidiom)[:30]:
    cls = Counter(bcls(c) for c in nonidiom[t])
    print(f"  {t:05X}: {len(nonidiom[t])} callers {dict(cls)}")

# prologue scan inside span: push {..,lr} and sub sp
print("push/sub-sp prologues in span:")
md = Cs(CS_ARCH_ARM, CS_MODE_THUMB)
for off in range(S, E, 2):
    h = u16(off)
    if (h & 0xFF00) == 0xB500 and (h & 0x0100):  # push ..,lr
        print(f"  {off:05X}: push {h:04X}")
    elif h == 0xB080 or (0xB081 <= h <= 0xB08F):
        pass
# sub sp,#imm is 0xB08x; check context: only report if preceded by push lr within 8B
for off in range(S, E, 2):
    h = u16(off)
    if 0xB081 <= h <= 0xB0FF:
        prev = [u16(off-k) for k in (2,4,6,8)]
        if any((p & 0xFF00) == 0xB500 and (p & 0x0100) for p in prev):
            print(f"  {off:05X}: sub sp {h:04X} (after push)")
