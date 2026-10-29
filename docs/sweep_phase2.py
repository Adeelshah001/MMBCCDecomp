#!/usr/bin/env python3
"""Phase 2 unknown-region sweep worker script (v2.3).

Reads the baserom in place (SHA-1 gated by gen_func_list_v2 import),
never copies bytes. Writes docs/func_list_v2_3_addendum.txt.
"""
import sys, struct
import gen_func_list_v2 as g

rom = g.rom  # bytes, SHA-1 gated on import
print("rom len:", len(rom), file=sys.stderr)

def u16(off):
    return struct.unpack_from('<H', rom, off)[0]

def u32(off):
    return struct.unpack_from('<I', rom, off)[0]

# ---------- byteclass spans ----------
spans = []  # (start, end, class)
for line in open('byteclass.tsv'):
    line = line.strip()
    if not line or line.startswith('#'):
        continue
    rng, cls = line.split()
    a, b = rng.split('-')
    spans.append((int(a, 16), int(b, 16), cls))

def byteclass_at(off):
    for s, e, c in spans:
        if s <= off <= e:
            return c
    return '?'

unknown_spans = [(s, e) for s, e, c in spans if c == 'unknown']
total_unknown = sum(e - s + 1 for s, e in unknown_spans)
print(f"unknown spans: {len(unknown_spans)}, bytes: {total_unknown}", file=sys.stderr)

# ---------- correct Thumb BL target decode (sign from bit 22) ----------
def thumb_bl_target(bl_off):
    """bl_off: file offset of first halfword of the BL pair. Returns target file offset or None."""
    hi = u16(bl_off); lo = u16(bl_off + 2)
    if (hi & 0xF800) != 0xF000 or (lo & 0xF800) != 0xF800:
        return None
    off = ((hi & 0x7FF) << 12) | ((lo & 0x7FF) << 1)
    if off & (1 << 22):
        off -= (1 << 23)
    tgt = bl_off + 4 + off
    # ROM base mapping: file offset == (rom_addr - 0x08000000)
    if 0 <= tgt < 0x50000:
        return tgt
    return None

def is_bl_pair(off):
    if off + 4 > len(rom) or off % 2:
        return False
    hi = u16(off); lo = u16(off + 2)
    return (hi & 0xF800) == 0xF000 and (lo & 0xF800) == 0xF800

# ---------- 1. thunk idiom scan ----------
# idiom halfwords (audit wrote them as byte strings "381c 4946 5246 089b",
# i.e. LE halfwords): 1c38 (adds r0,r7,#0) 4649 (mov r1,r9) 4652 (mov r2,r10)
# 9b08 (lsls r3,r1,#6)
THUNK = (0x1C38, 0x4649, 0x4652, 0x9B08)

thunks = []  # (start, bl_target)
s, e = 0x029000, 0x02CC00
for off in range(s, e, 2):
    if (u16(off), u16(off+2), u16(off+4), u16(off+6)) == THUNK:
        tgt = thumb_bl_target(off + 8) if is_bl_pair(off + 8) else None
        thunks.append((off, tgt))
print(f"thunk idiom instances in 029000-02CC00: {len(thunks)}", file=sys.stderr)
print(f"  first: {thunks[0][0]:05X}, last: {thunks[-1][0]:05X}", file=sys.stderr)

# how many of the thunks are followed by a BL pair?
bl_follow = sum(1 for _, t in thunks if t is not None)
print(f"  followed by valid BL pair: {bl_follow}", file=sys.stderr)

# unique BL targets called by thunks, with byteclass
from collections import Counter
tgtc = Counter(t for _, t in thunks if t is not None)
print(f"  distinct BL targets: {len(tgtc)}", file=sys.stderr)
for t, n in tgtc.most_common(12):
    print(f"    {t:05X} x{n} class={byteclass_at(t)}", file=sys.stderr)
