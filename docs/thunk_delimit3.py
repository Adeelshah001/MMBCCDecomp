#!/usr/bin/env python3
"""Inspect failing thunk tails + large gaps for interleaved non-idiom code."""
import sys, struct
import gen_func_list_v2 as g

rom = g.rom
def u16(off): return struct.unpack_from('<H', rom, off)[0]
def u32(off): return struct.unpack_from('<I', rom, off)[0]

THUNK = (0x1C38, 0x4649, 0x4652, 0x9B08)
thunks = []
for off in range(0x029000, 0x02CC00, 2):
    if (u16(off), u16(off+2), u16(off+4), u16(off+6)) == THUNK:
        thunks.append(off)

def dis(off, n):
    out = []
    for _ in range(n):
        d = g.dec_thumb(off)
        if d is None:
            out.append((off, None)); break
        sz = d[0]
        out.append((off, d))
        off += sz
    return out

# failing thunk 29AC4 tail in full (until next thunk or 40 insns)
print("=== thunk 29AC4 tail ===")
for off, d in dis(0x29AC4, 30):
    print(f"  {off:05X}: {u16(off):04X} {d[1] if d else '???'}")
    if off >= 0x29AEA: break

# big gap 29D90 -> 2A67A: scan for push/sub-sp prologues and BL targets
print("=== gap 29D90->2A67A (2282B): prologue/BL scan ===")
def thumb_bl_target(bl_off):
    hi = u16(bl_off); lo = u16(bl_off + 2)
    if (hi & 0xF800) != 0xF000 or (lo & 0xF800) != 0xF800: return None
    off = ((hi & 0x7FF) << 12) | ((lo & 0x7FF) << 1)
    if off & (1 << 22): off -= (1 << 23)
    tgt = bl_off + 4 + off
    return tgt if 0 <= tgt < 0x50000 else None

s, e = 0x29D90 + 14, 0x2A67A
# first: what does the tail of 29D90 look like?
print("--- tail of thunk 29D90 ---")
for off, d in dis(0x29D90, 40):
    print(f"  {off:05X}: {u16(off):04X} {d[1] if d else '???'}")
