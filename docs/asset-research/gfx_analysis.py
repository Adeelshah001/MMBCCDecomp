#!/usr/bin/env python3
"""Graphics inventory (aggregate only, no pixel content extraction).
1. 4KB-window scan: entropy + 32-byte-tile repetition -> tile-data candidates
2. Palette hunt: runs of >=16 u16 with bit15 clear and plausible 5-bit channels
3. Tilemap hunt: runs of u16 values < 0x4000 with map-like regularity (2KB multiples)
4. RLE/LZ77-decompressed tile data is covered by lz77 scan; here raw ROM only.
"""
import math
from collections import Counter

ROM_PATH = "/home/hatch/workspace/megaman-bcc-recomp/rom/Mega_Man_-_Battle_Chip_Challenge__USA__0_8r4i.gba"
rom = open(ROM_PATH, "rb").read()
N = len(rom)
print(f"ROM {N} bytes", flush=True)

def entropy(buf):
    c = Counter(buf); n = len(buf)
    return -sum((v/n)*math.log2(v/n) for v in c.values())

# ---------- 1. tile-data candidates: mid entropy + high 32B-tile repetition ----------
print("tile-data scan (4KB windows)...", flush=True)
tile_wins = []
for w in range(0, N, 4096):
    blk = rom[w:w+4096]
    if len(blk) < 4096: break
    tiles = [bytes(blk[i:i+32]) for i in range(0, 4096, 32)]
    nz = [t for t in tiles if any(t)]
    if len(nz) < 64: continue
    e = entropy(blk)
    if not (3.0 < e < 7.6): continue
    distinct = len(set(nz))
    rep = 1 - distinct/len(nz)   # repetition ratio
    if rep > 0.15:
        tile_wins.append((w, round(e,2), round(rep,2), len(nz)))
tile_wins.sort(key=lambda x: -x[2])
print(f"  windows with 3<ent<7.6 and tile-repetition>0.15: {len(tile_wins)}", flush=True)
for w, e, rep, n in tile_wins[:30]:
    print(f"  0x{w:07X} ent={e} tile_rep={rep} ntiles={n}", flush=True)
total_tile_bytes = sum(4096 for _ in tile_wins)
print(f"  approx tile-data bytes (raw, incl. overlaps w/ other data): {total_tile_bytes} ({total_tile_bytes/1024:.0f} KB)", flush=True)

# ---------- 2. palette hunt ----------
# BGR555: bit15 usually 0; each 5-bit channel 0..31. Look for runs of >=16 u16
# where bit15==0 and not (all zero) and byte pattern isn't code-like.
print("palette scan...", flush=True)
pals = []
o = 0
while o < N - 32:
    # quick check: 16 consecutive u16 with bit15 clear
    ok = True
    vals = []
    for k in range(16):
        v = rom[o+2*k] | (rom[o+2*k+1] << 8)
        if v & 0x8000:
            ok = False; break
        vals.append(v)
    if ok and any(vals):
        # extend run
        e = o + 32
        while e < N - 2:
            v = rom[e] | (rom[e+1] << 8)
            if v & 0x8000: break
            e += 2
        runlen = (e - o) // 2
        # palette plausibility: not too random; check channel distribution isn't uniform-random
        # simple: require at least 25% of entries have r,g,b all < 28 (not maxed) -> weak; instead require
        # that the run isn't just incrementing/code-like: check distinct count high but entropy mid
        blk = rom[o:e]
        ent = entropy(blk)
        if 4.0 < ent < 7.8 and runlen <= 512:
            pals.append((o, runlen, round(ent, 2)))
        o = e
        continue
    o += 2
print(f"  palette-like runs (>=16 u16, bit15 clear, 4<ent<7.8): {len(pals)}", flush=True)
for o, n, e in pals[:40]:
    print(f"  0x{o:07X} entries={n} ent={e}", flush=True)
pal_bytes = sum(n*2 for _, n, _ in pals)
print(f"  total palette-candidate bytes: {pal_bytes}", flush=True)

# ---------- 3. tilemap hunt: 2KB-aligned runs of u16 with values < 0x4000 ----------
# BG maps are 32x32 or 64x32 u16 = 2048/4096 bytes. Heuristic: 2048-byte window where
# >90% of u16 < 0x4000 and at least 30% are < 0x400 (tile indices), entropy 3..7.
print("tilemap scan (2KB windows)...", flush=True)
maps = []
for w in range(0, N - 2048, 2048):
    blk = rom[w:w+2048]
    vals = [blk[i] | (blk[i+1] << 8) for i in range(0, 2048, 2)]
    if sum(1 for v in vals if v < 0x4000) < 900: continue
    if sum(1 for v in vals if v < 0x400) < 200: continue
    e = entropy(blk)
    if 2.5 < e < 7.0:
        # map regularity: count distinct vs total
        d = len(set(vals))
        maps.append((w, round(e,2), d))
print(f"  tilemap-like 2KB windows: {len(maps)}", flush=True)
for w, e, d in maps[:30]:
    print(f"  0x{w:07X} ent={e} distinct_u16={d}", flush=True)
print("DONE", flush=True)
