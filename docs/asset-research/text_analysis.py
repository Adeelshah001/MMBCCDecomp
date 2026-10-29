#!/usr/bin/env python3
"""Text encoding analysis for MMBCC GBA ROM. Read-only. Aggregate stats only.
1. Whole-ROM byte histogram + ASCII-string check (prior claim: none outside header)
2. Pointer-table hunt (u32 ROM pointers, increasing, small deltas)
3. Entropy-window scan for structured-data regions
4. Font/tile-pattern hunt (regular 16/32-byte glyph tiles)
5. Dialogue-inside-LZ77 check (decode valid 0x10 blocks, score text-likeness)
"""
import json, math, re
from collections import Counter

ROM_PATH = "/home/hatch/workspace/megaman-bcc-recomp/rom/Mega_Man_-_Battle_Chip_Challenge__USA__0_8r4i.gba"
rom = open(ROM_PATH, "rb").read()
N = len(rom)
print(f"ROM {N} bytes", flush=True)

# ---------- 1. histogram ----------
hist = Counter(rom)
print("Top 20 bytes:", [(f"{b:02X}", c) for b, c in hist.most_common(20)], flush=True)
zero_frac = hist[0] / N
ff_frac = hist.get(0xFF, 0) / N
print(f"0x00 fraction={zero_frac:.3f} 0xFF fraction={ff_frac:.3f}", flush=True)

# ---------- ASCII check ----------
pat = re.compile(rb'[\x20-\x7E]{8,}')
hits = [(m.start(), m.group()[:60]) for m in pat.finditer(rom)]
outside = [(o, g) for (o, g) in hits if not (0xA0 <= o < 0xC0)]
print(f"ASCII runs>=8 total={len(hits)} outside_header={len(outside)}", flush=True)
for o, g in outside[:20]:
    print(f"  0x{o:07X}: {g}", flush=True)

# ---------- 2. pointer tables: runs of >=6 u32 in [0x08000000,0x08800000), increasing, delta<0x20000 ----------
def u32(o): return rom[o] | (rom[o+1] << 8) | (rom[o+2] << 16) | (rom[o+3] << 24)
tables = []
o = 0
while o < N - 4:
    v = u32(o)
    if 0x08000000 <= v < 0x08800000:
        run = [v]; p = o + 4
        while p < N - 4:
            v2 = u32(p)
            if not (0x08000000 <= v2 < 0x08800000): break
            if v2 < run[-1] or v2 - run[-1] > 0x20000: break
            run.append(v2); p += 4
        if len(run) >= 6:
            # check targets land in data-ish (not all in code region start?) just record
            tables.append((o, len(run), run[0], run[-1]))
            o = p
            continue
    o += 4
print(f"u32 pointer-table runs>=6: {len(tables)}", flush=True)
for t in tables[:30]:
    print(f"  table@0x{t[0]:07X} n={t[1]} first->0x{t[2]:08X} last->0x{t[3]:08X}", flush=True)

# ---------- 3. entropy windows (4KB): find low-entropy structured regions ----------
def entropy(buf):
    c = Counter(buf)
    n = len(buf)
    return -sum((v/n) * math.log2(v/n) for v in c.values())

print("entropy scan (4KB windows, reporting entropy<5.0 non-zero regions)...", flush=True)
low = []
for w in range(0, N, 4096):
    blk = rom[w:w+4096]
    if len(blk) < 4096: break
    nz = sum(1 for b in blk if b)
    if nz < 64: continue
    e = entropy(blk)
    if e < 5.0:
        low.append((w, round(e, 2), nz))
print(f"  windows with entropy<5.0: {len(low)}", flush=True)
for w, e, nz in low[:40]:
    print(f"  0x{w:07X} ent={e} nonzero={nz}", flush=True)

# ---------- 4. font hunt: 16-byte (1bpp 8x16) or 32-byte (4bpp 8x8) glyph regularity ----------
# Heuristic: a font block = long run of tiles where each tile is non-trivial,
# tiles differ from each other, but byte values show "glyph-like" structure:
# for 1bpp, rows have 1-7 bits set typically (not 0, not 8) for many rows.
def glyph_score_1bpp(tile16):
    # count rows with 1..7 bits set
    good = sum(1 for b in tile16 if 0 < bin(b).count("1") < 8)
    return good / 16
best = []
for w in range(0, N - 4096, 1024):
    blk = rom[w:w+4096]
    tiles = [blk[i:i+16] for i in range(0, 4096, 16)]
    nz_tiles = [t for t in tiles if any(t) and not all(b == t[0] for b in t)]
    if len(nz_tiles) < 200: continue
    sc = sum(glyph_score_1bpp(t) for t in nz_tiles) / len(nz_tiles)
    # also require low tile duplication (font glyphs mostly distinct)
    distinct = len(set(bytes(t) for t in nz_tiles)) / len(nz_tiles)
    if sc > 0.55 and distinct > 0.5:
        best.append((w, round(sc, 3), round(distinct, 3), len(nz_tiles)))
best.sort(key=lambda x: -x[1])
print(f"font-like 1bpp-8x16 regions (score>0.55, distinct>0.5): {len(best)}", flush=True)
for w, sc, d, n in best[:20]:
    print(f"  0x{w:07X} glyphscore={sc} distinct={d} ntiles={n}", flush=True)

# ---------- 5. dialogue inside LZ77: decode valid 0x10 blocks, text-likeness ----------
# reuse decoders from lz77_scan.py defs
g = {}
src = open("/tmp/lz77_scan.py").read()
defs = src[:src.index("# ================= driver")]
exec(defs, g)
dec10 = g["dec_lz77_v10"]
print("decoding valid 0x10 blocks for text-likeness...", flush=True)
def textlike(buf):
    """score 0..1: long runs, low entropy, control-code-ish bytes"""
    if len(buf) < 64: return 0
    e = entropy(buf)
    # text-ish: entropy 2..6, few 0x00/0xFF extremes? custom enc unknown; use generic:
    # fraction of bytes that are NOT in sparse tails
    c = Counter(buf)
    top8 = sum(v for _, v in c.most_common(8)) / len(buf)
    return (e, top8)
cands = []
off = 0
nvalid = 0
while off < N - 4:
    if rom[off] == 0x10:
        from_lz = off  # placeholder
        size = rom[off+1] | (rom[off+2] << 8) | (rom[off+3] << 16)
        if 8 < size < 4*1024*1024:
            r = dec10(rom, off)
            if r is not None:
                decd, clen = r
                if clen >= 6 and len(decd) == size:
                    nvalid += 1
                    e, top8 = textlike(decd)
                    if 1.5 < e < 5.5 and top8 > 0.35:
                        cands.append((off, size, round(e, 2), round(top8, 2)))
    off += 1
cands.sort(key=lambda x: x[3], reverse=True)
print(f"  valid 0x10 blocks re-decoded: {nvalid}; text-like (1.5<ent<5.5, top8>0.35): {len(cands)}", flush=True)
for o, s, e, t in cands[:25]:
    print(f"  0x{o:07X} dec={s} ent={e} top8frac={t}", flush=True)
print("DONE", flush=True)
