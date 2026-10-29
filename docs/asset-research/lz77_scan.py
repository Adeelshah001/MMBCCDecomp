#!/usr/bin/env python3
"""LZ77 / Huffman / RLE block scanner for GBA ROM with real-decode validation.
Read-only on the ROM. Writes results to /tmp/lz77_results.json + summary.
"""
import json, sys, time

ROM_PATH = "/home/hatch/workspace/megaman-bcc-recomp/rom/Mega_Man_-_Battle_Chip_Challenge__USA__0_8r4i.gba"
OUT_JSON = "/tmp/lz77_results.json"
MAX_OUT = 4 * 1024 * 1024   # max decompressed size to attempt
MIN_OUT = 8                 # min sane decompressed size (task says >8)

rom = open(ROM_PATH, "rb").read()
N = len(rom)
print(f"ROM size: {N}", flush=True)
t0 = time.time()

def u24(b, o):
    return b[o] | (b[o+1] << 8) | (b[o+2] << 16)

# ---------- GBA LZ77 v10 (0x10) ----------
def dec_lz77_v10(data, off):
    size = u24(data, off + 1)
    if size < MIN_OUT or size > MAX_OUT:
        return None
    src = off + 4
    end = N
    dst = bytearray()
    # use local vars for speed
    try:
        while len(dst) < size:
            if src >= end:
                return None
            flags = data[src]; src += 1
            for i in range(8):
                if len(dst) >= size:
                    break
                if flags & 0x80:
                    if src + 1 >= end:
                        return None
                    b1 = data[src]; b2 = data[src+1]; src += 2
                    length = (b1 >> 4) + 3
                    disp = ((b1 & 0x0F) << 8 | b2) + 1
                    if disp > len(dst) or disp <= 0:
                        return None
                    if len(dst) + length > size:
                        return None
                    # overlap-safe copy
                    for _ in range(length):
                        dst.append(dst[len(dst) - disp])
                else:
                    if src >= end:
                        return None
                    dst.append(data[src]); src += 1
                flags = (flags << 1) & 0xFF
        return (bytes(dst), src - off)  # decompressed, compressed bytes consumed
    except IndexError:
        return None

# ---------- GBA LZ77 v11 (0x11, vram-safe) ----------
def dec_lz77_v11(data, off):
    size = u24(data, off + 1)
    if size < MIN_OUT or size > MAX_OUT:
        return None
    n_ext = [0]
    src = off + 4
    end = N
    dst = bytearray()
    try:
        while len(dst) < size:
            if src >= end:
                return None
            flags = data[src]; src += 1
            for i in range(8):
                if len(dst) >= size:
                    break
                if flags & 0x80:
                    if src + 1 >= end:
                        return None
                    b1 = data[src]; src += 1
                    length = b1 >> 4
                    disp = (b1 & 0x0F) << 8
                    b2 = data[src]; src += 1
                    disp |= b2
                    if length == 0:
                        if src >= end:
                            return None
                        b3 = data[src]; src += 1
                        length = b3 + 0x11   # GBATEK: "number of bytes to copy minus 0x11"
                        n_ext[0] += 1
                    else:
                        length += 1
                    disp += 1
                    if disp > len(dst) or disp <= 0:
                        return None
                    if len(dst) + length > size:
                        return None
                    for _ in range(length):
                        dst.append(dst[len(dst) - disp])
                else:
                    if src >= end:
                        return None
                    dst.append(data[src]); src += 1
                flags = (flags << 1) & 0xFF
        return (bytes(dst), src - off, n_ext[0])
    except IndexError:
        return None

# ---------- Huffman 0x20 (4-bit) / 0x28 (8-bit) ----------
def dec_huff(data, off, bits):
    """Decode GBA Huffman. For 4-bit, leaves are nibbles packed 2/byte.
    Size semantics ambiguous -> try size*2 nibbles then size nibbles."""
    size = u24(data, off + 1)
    if size < MIN_OUT or size > MAX_OUT:
        return None
    src = off + 4
    if src >= N:
        return None
    tree_size = data[src]; src += 1
    if tree_size == 0 or tree_size > 128:
        return None
    if src + tree_size * 2 > N:
        return None
    tree = data[src:src + tree_size * 2]; src += tree_size * 2
    for t in tree:
        if t & 0x80:
            return None
    targets = [size * 2, size] if bits == 4 else [size]
    for target_units in targets:
        units = []
        node = 0
        s = src
        ok = True
        try:
            while len(units) < target_units:
                if s >= N:
                    ok = False; break
                cur = data[s]; s += 1
                for _b in range(8):
                    bit = (cur >> 7) & 1; cur = (cur << 1) & 0xFF
                    entry = tree[node * 2]
                    nxt_off = entry & 0x3F
                    is_data = (entry >> (5 + bit)) & 1
                    child = node + 1 + nxt_off
                    if is_data:
                        val = tree[child * 2 + bit]
                        units.append(val & 0xF if bits == 4 else val)
                        node = 0
                    else:
                        node = child
                        if node * 2 >= len(tree):
                            ok = False; break
                    if len(units) >= target_units:
                        break
                if not ok:
                    break
        except IndexError:
            ok = False
        if ok and len(units) == target_units:
            if bits == 4:
                dst = bytearray()
                for k in range(0, len(units) - 1, 2):
                    dst.append((units[k] << 4) | units[k + 1])
                return (bytes(dst), s - off, target_units)
            return (bytes(units), s - off, target_units)
    return None

# ---------- RLE 0x30 (try 8-bit and 16-bit units) ----------
def dec_rle(data, off, unit16):
    size = u24(data, off + 1)
    if size < MIN_OUT or size > MAX_OUT:
        return None
    unit = 2 if unit16 else 1
    if size % unit != 0:
        return None
    src = off + 4
    dst = bytearray()
    try:
        while len(dst) < size:
            if src >= N:
                return None
            flag = data[src]; src += 1
            run = (flag & 0x7F) + 1
            if flag & 0x80:
                if src + unit > N:
                    return None
                val = data[src:src+unit]; src += unit
                if len(dst) + run * unit > size:
                    return None
                dst.extend(val * run)
            else:
                if src + run * unit > N:
                    return None
                if len(dst) + run * unit > size:
                    return None
                dst.extend(data[src:src + run * unit]); src += run * unit
        return (bytes(dst), src - off)
    except IndexError:
        return None

# ================= driver =================
results = {}
all_spans = []  # (off, end, type) for overlap filtering later

def record(tname, off, decsize, complen, extra=""):
    results.setdefault(tname, {"candidates": 0, "blocks": []})
    results[tname]["blocks"].append({"off": off, "dec": decsize, "comp": complen, "extra": extra})
    all_spans.append((off, off + complen, tname))

print("Scanning 0x10 (LZ77 v10)...", flush=True)
cand = 0
for off in range(N - 4):
    if rom[off] != 0x10: continue
    size = u24(rom, off + 1)
    if size < MIN_OUT or size > MAX_OUT: continue
    cand += 1
    r = dec_lz77_v10(rom, off)
    if r is not None:
        decd, clen = r
        if clen >= 6 and len(decd) == size:
            record("lz77_v10", off, size, clen)
    if off & 0xFFFFF == 0:
        print(f"  0x10: 0x{off:07X} cand={cand} valid={len(results.get('lz77_v10',{}).get('blocks',[]))}", flush=True)
results["lz77_v10"]["candidates"] = cand
print(f"  0x10 done: cand={cand} valid={len(results['lz77_v10']['blocks'])} ({time.time()-t0:.1f}s)", flush=True)

print("Scanning 0x11 (LZ77 v11)...", flush=True)
cand = 0
for off in range(N - 4):
    if rom[off] != 0x11: continue
    size = u24(rom, off + 1)
    if size < MIN_OUT or size > MAX_OUT: continue
    cand += 1
    r = dec_lz77_v11(rom, off)
    if r is not None:
        decd, clen, n_ext = r
        if clen >= 6 and len(decd) == size:
            r10 = dec_lz77_v10(rom, off)
            also10 = r10 is not None and len(r10[0]) == size
            record("lz77_v11", off, size, clen, f"ext={n_ext} also10={also10}")
results["lz77_v11"]["candidates"] = cand
print(f"  0x11 done: cand={cand} valid={len(results.get('lz77_v11',{}).get('blocks',[]))} ({time.time()-t0:.1f}s)", flush=True)

print("Scanning 0x20/0x28 (Huffman)...", flush=True)
for tbyte, bits in ((0x20, 4), (0x28, 8)):
    cand = 0
    for off in range(N - 4):
        if rom[off] != tbyte: continue
        size = u24(rom, off + 1)
        if size < MIN_OUT or size > MAX_OUT: continue
        cand += 1
        r = dec_huff(rom, off, bits)
        if r is not None:
            decd, clen, tunits = r
            if clen >= 8:
                record(f"huff_{bits}bit", off, len(decd), clen, f"units={tunits}")
    results[f"huff_{bits}bit"]["candidates"] = cand
    print(f"  {tbyte:#04x} done: cand={cand} valid={len(results[f'huff_{bits}bit']['blocks'])} ({time.time()-t0:.1f}s)", flush=True)

print("Scanning 0x30 (RLE)...", flush=True)
for unit16 in (False, True):
    cand = 0
    for off in range(N - 4):
        if rom[off] != 0x30: continue
        size = u24(rom, off + 1)
        if size < MIN_OUT or size > MAX_OUT: continue
        if size % (2 if unit16 else 1) != 0: continue
        cand += 1
        r = dec_rle(rom, off, unit16)
        if r is not None:
            decd, clen = r
            if clen >= 6 and len(decd) == size:
                record(f"rle_{'16' if unit16 else '8'}", off, size, clen)
    results[f"rle_{'16' if unit16 else '8'}"]["candidates"] = cand
    print(f"  rle{'16' if unit16 else '8'} done: cand={cand} valid={len(results[f'rle_{'16' if unit16 else '8'}']['blocks'])} ({time.time()-t0:.1f}s)", flush=True)

# ---- overlap filtering: drop blocks fully inside another block's compressed span ----
# sort spans by length desc; keep a block if not contained in an already-kept larger span
spans_sorted = sorted(all_spans, key=lambda s: (s[1]-s[0]), reverse=True)
kept = []  # (off, end)
def contained(off, end):
    for (koff, kend) in kept:
        if koff <= off and end <= kend and (koff, kend) != (off, end):
            return True
    return False
filtered = {}
for tname, tdata in results.items():
    fb = []
    for b in tdata["blocks"]:
        if contained(b["off"], b["off"] + b["comp"]):
            continue
        if tname.startswith("rle_") and not (b["comp"] < b["dec"]):
            continue
        fb.append(b)
        kept.append((b["off"], b["off"] + b["comp"]))
    filtered[tname] = fb

# ---- size distribution + top 30 ----
dist_bins = [0, 64, 256, 1024, 4096, 16384, 65536, 262144, 1048576, 1<<31]
def dist(blocks):
    d = {f"<={b//1 if False else 0}": 0 for b in []}
    out = {}
    labels = ["<=64","65-256","257-1K","1K-4K","4K-16K","16K-64K","64K-256K","256K-1M",">1M"]
    counts = [0]*len(labels)
    for b in blocks:
        s = b["dec"]
        if s <= 64: counts[0]+=1
        elif s <= 256: counts[1]+=1
        elif s <= 1024: counts[2]+=1
        elif s <= 4096: counts[3]+=1
        elif s <= 16384: counts[4]+=1
        elif s <= 65536: counts[5]+=1
        elif s <= 262144: counts[6]+=1
        elif s <= 1048576: counts[7]+=1
        else: counts[8]+=1
    return dict(zip(labels, counts))

summary = {}
allb = []
for tname, tdata in results.items():
    fb = sorted(filtered[tname], key=lambda b: -b["dec"])
    summary[tname] = {
        "candidates": tdata["candidates"],
        "valid_raw": len(tdata["blocks"]),
        "valid_filtered": len(fb),
        "total_dec_bytes": sum(b["dec"] for b in fb),
        "total_comp_bytes": sum(b["comp"] for b in fb),
        "dist": dist(fb),
        "top10": [{"off": hex(b["off"]), "dec": b["dec"], "comp": b["comp"], "extra": b.get("extra","")} for b in fb[:10]],
    }
    allb.extend([(b["dec"], tname, b["off"], b["comp"]) for b in fb])

allb.sort(reverse=True)
summary["top30_all"] = [{"off": hex(o), "type": t, "dec": d, "comp": c} for (d, t, o, c) in allb[:30]]
summary["elapsed_s"] = round(time.time()-t0, 1)

with open(OUT_JSON, "w") as f:
    json.dump(summary, f, indent=1)
out = {}
for k, v in summary.items():
    if isinstance(v, dict):
        out[k] = {kk: vv for kk, vv in v.items() if kk != "top10"}
    else:
        out[k] = v
print(json.dumps(out, indent=1))
summary["blocks_full"] = {t: [{"off": hex(b["off"]), "dec": b["dec"], "comp": b["comp"], "extra": b.get("extra","")} for b in sorted(filtered[t], key=lambda b: -b["dec"])] for t in filtered}
print("TOP30:")
for e in summary["top30_all"]:
    print(f"  {e['off']:>10} {e['type']:<10} dec={e['dec']:>8} comp={e['comp']:>7}")
print("wrote", OUT_JSON, flush=True)
