#!/usr/bin/env python3
"""Text deep-dive: is dialogue inside LZ77 blocks? What encoding?
Aggregate stats only. Re-decodes valid 0x10 blocks and profiles content."""
import math, re
from collections import Counter

ROM_PATH = "/home/hatch/workspace/megaman-bcc-recomp/rom/Mega_Man_-_Battle_Chip_Challenge__USA__0_8r4i.gba"
rom = open(ROM_PATH, "rb").read()
N = len(rom)

g = {}
src = open("/tmp/lz77_scan.py").read()
exec(src[:src.index("# ================= driver")], g)
dec10 = g["dec_lz77_v10"]

def entropy(buf):
    c = Counter(buf); n = len(buf)
    return -sum((v/n)*math.log2(v/n) for v in c.values())

# ---- 1. firm ASCII check: runs with spaces (real text has ~1/6 spaces) ----
runs = [m.group() for m in re.finditer(rb'[\x20-\x7E]{8,}', rom)]
with_sp = [r for r in runs if b' ' in r and len(r) >= 12]
print(f"ASCII runs>=8: {len(runs)}; with spaces and len>=12: {len(with_sp)}", flush=True)
for r in with_sp[:10]:
    print("  ", r[:80], flush=True)

# ---- 2. decode valid 0x10 blocks, profile ----
cands = []
off = 0
nvalid = 0
while off < N - 4:
    if rom[off] == 0x10:
        size = rom[off+1] | (rom[off+2] << 8) | (rom[off+3] << 16)
        if 8 < size < 4*1024*1024:
            r = dec10(rom, off)
            if r is not None:
                decd, clen = r
                if clen >= 6 and len(decd) == size:
                    nvalid += 1
                    if size >= 256:
                        e = entropy(decd)
                        c = Counter(decd)
                        top16 = sum(v for _, v in c.most_common(16)) / size
                        cands.append((off, size, e, top16, bytes(decd)))
    off += 1
print(f"valid 0x10: {nvalid}", flush=True)

# text-like: small alphabet + low-mid entropy
textlike = [(o, s, e, t) for (o, s, e, t, d) in cands if 1.8 < e < 5.2 and t > 0.55]
textlike.sort(key=lambda x: x[1], reverse=True)
print(f"text-like blocks (1.8<ent<5.2, top16>0.55, size>=256): {len(textlike)}", flush=True)
for o, s, e, t in textlike[:20]:
    print(f"  0x{o:07X} dec={s} ent={e:.2f} top16={t:.2f}", flush=True)

# ---- 3. for top text candidates: 16-bit pattern + SJIS pair test (aggregate) ----
def sjis_score(buf):
    # count lead/trail pairs
    n = 0; i = 0
    L = len(buf)
    while i < L - 1:
        b = buf[i]
        if (0x81 <= b <= 0x9F) or (0xE0 <= b <= 0xFC):
            t = buf[i+1]
            if (0x40 <= t <= 0x7E) or (0x80 <= t <= 0xFC):
                n += 1; i += 2; continue
        i += 1
    return n / (L / 2)

print("\nencoding probes on top text-like blocks:", flush=True)
for o, s, e, t in textlike[:10]:
    d = next(d for (oo, ss, ee, tt, d) in cands if oo == o)
    # 16-bit LE: fraction of u16 with high byte 0
    u16s = [d[i] | (d[i+1] << 8) for i in range(0, len(d)-1, 2)]
    hib0 = sum(1 for v in u16s if v < 256) / len(u16s)
    lo_rng = sum(1 for v in u16s if v < 0x3000) / len(u16s)
    sj = sjis_score(d)
    # control-code-ish: fraction of 0x00,0xFF,0xFE
    ctrl = sum(1 for b in d if b in (0, 255, 254)) / len(d)
    print(f"  0x{o:07X}: u16<0x100 frac={hib0:.2f} u16<0x3000 frac={lo_rng:.2f} sjis-pair={sj:.2f} ctrl000/FFF/FFE={ctrl:.3f}", flush=True)

# ---- 4. overall: how many blocks look like text vs tiles vs code? ----
import json
cats = Counter()
for (o, s, e, t, d) in cands:
    if s < 256: cats["tiny"] += 1
    elif 1.8 < e < 5.2 and t > 0.55: cats["text-like"] += 1
    elif e >= 7.0: cats["high-ent(code/pcm?)"] += 1
    elif 5.2 <= e < 7.0: cats["mid-ent(tiles/maps?)"] += 1
    else: cats["very-low-ent"] += 1
print("\nblock content categories (size>=256):", dict(cats), flush=True)
print("DONE", flush=True)
