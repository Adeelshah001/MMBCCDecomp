#!/usr/bin/env python3
"""Delimit the thunk cluster: structure, spacing, branch tails, validate each start."""
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
print(f"n={len(thunks)} first={thunks[0]:05X} last={thunks[-1]:05X}", file=sys.stderr)

# Structure of a thunk: offsets 0..14
import collections
tails = collections.Counter()
blt = collections.Counter()
gaps = collections.Counter()
for i, t in enumerate(thunks):
    hw = [u16(t+j) for j in range(0, 16, 2)]
    # hw[4],hw[5] = BL pair; hw[6] = branch?; hw[7] = ?
    tgt = thumb_bl_target(t+8)
    blt[tgt] += 1
    tails[(hw[6], hw[7])] += 1
    if i+1 < len(thunks):
        gaps[thunks[i+1]-t] += 1
print("BL targets:", {f'{k:05X}':v for k,v in blt.items()}, file=sys.stderr)
print("tail (hw6,hw7) patterns:", {f'{k[0]:04X},{k[1]:04X}':v for k,v in tails.most_common()}, file=sys.stderr)
print("gap distribution:", dict(sorted(gaps.items())), file=sys.stderr)

# branch at t+12: decode
for t in thunks[:3]:
    b = u16(t+12)
    assert (b & 0xF800) == 0xE000, hex(b)
    soff = (b & 0x7FF) << 1
    if soff & 0x1000: soff -= 0x2000
    print(f"thunk {t:05X}: tail branch -> {(t+12+4+soff):05X}", file=sys.stderr)

# is 0x2D7A0 a known function (v2 list)?
known = set()
for line in open('func_list_v2.txt'):
    line=line.strip()
    if line and not line.startswith('#'): known.add(int(line.split()[0],16))
for line in open('func_list_v2_1_addendum.txt'):
    line=line.strip()
    if line and not line.startswith('#'): known.add(int(line.split()[0],16))
for line in open('func_list_v2_2_addendum.txt'):
    line=line.strip()
    if line and not line.startswith('#'): known.add(int(line.split()[0],16))
print("2D7A0 in known lists:", 0x2D7A0 in known, file=sys.stderr)

# validate_target on each thunk start
ok = sum(1 for t in thunks if g.validate_target(t, 'T'))
print(f"validate_target T: {ok}/{len(thunks)} pass", file=sys.stderr)
fails = [t for t in thunks if not g.validate_target(t, 'T')]
print("fails:", [f'{t:05X}' for t in fails][:10], file=sys.stderr)

# bytes before first thunk and after last: dump context
print("bytes before 29AC4 (from 29A80):", file=sys.stderr)
for off in range(0x29A80, 0x29AC4, 2):
    print(f"  {off:05X}: {u16(off):04X}", file=sys.stderr)
print("bytes after 2C70C tail (2C70C+14 .. 2C760):", file=sys.stderr)
for off in range(0x2C70C+14, 0x2C760, 2):
    print(f"  {off:05X}: {u16(off):04X}", file=sys.stderr)
