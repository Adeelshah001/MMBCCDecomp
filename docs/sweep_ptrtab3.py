#!/usr/bin/env python3
"""Strict filter on the 75 pointer-table candidates: require >=2 table-runs
OR BL-called OR push{lr} prologue. Output the high-confidence set."""
import sys, struct
from collections import defaultdict, Counter
import gen_func_list_v2 as g

rom = g.rom
def u16(off): return struct.unpack_from('<H', rom, off)[0]
def u32(off): return struct.unpack_from('<I', rom, off)[0]

# re-derive the 75 (import logic from sweep_ptrtab2 by re-running core)
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
listed = set()
for fn in ('func_list_v2.txt', 'func_list_v2_1_addendum.txt', 'func_list_v2_2_addendum.txt'):
    for line in open(fn):
        line = line.strip()
        if line and not line.startswith('#'):
            listed.add(int(line.split()[0], 16))
def is_ptr(w): return 0x08000000 <= w < 0x08050000
runs = []
off = 0; N = len(rom)
while off < N - 12:
    if is_ptr(u32(off)) and is_ptr(u32(off+4)) and is_ptr(u32(off+8)):
        t0 = off; tgts = []
        while off < N - 4 and is_ptr(u32(off)):
            tgts.append(u32(off) - 0x08000000); off += 4
        runs.append((t0, tgts))
    else:
        off += 4
def strong_shape(tgt):
    seen = set(); pc = tgt & ~1
    for _ in range(120):
        if pc in seen or not (0 <= pc < 0x50000) or pc & 1: return False
        seen.add(pc)
        d = g.dec_thumb(pc)
        if d is None or d[1] == 'invalid': return False
        h = u16(pc)
        if h == 0x4770: return True
        if (h & 0xFF00) == 0xBD00 and (h & 0x0100): return True
        if h == 0x46F6: return True
        sz, kind, t2 = d[0], d[1], d[2]
        if kind == 'b': pc = t2 & ~1; continue
        if kind == 'bcond': pc += sz; continue
        if kind in ('bx',): return False
        pc += sz
    return False
tgt_runs = Counter(); tgt_locs = defaultdict(list)
for roff, tgts in runs:
    for w in tgts:
        t = w & ~1
        if bcls(t) == 'unknown' and t not in listed and not (roff <= t < roff + 4*len(tgts)):
            tgt_runs[t] += 1; tgt_locs[t].append(roff)
strong = {t: n for t, n in tgt_runs.items() if strong_shape(t)}
print(f"strong: {len(strong)}", file=sys.stderr)

# BL-called check
def bt(bl):
    hi = u16(bl); lo = u16(bl+2)
    if (hi & 0xF800) != 0xF000 or (lo & 0xF800) != 0xF800: return None
    o = ((hi & 0x7FF) << 12) | ((lo & 0x7FF) << 1)
    if o & (1 << 22): o -= (1 << 23)
    t = bl + 4 + o
    return t if 0 <= t < 0x50000 else None
bl_called = Counter()
for off in range(0, 0x50000-4, 2):
    hi = u16(off)
    if (hi & 0xF800) == 0xF000 and (u16(off+2) & 0xF800) == 0xF800:
        t = bt(off)
        if t in strong: bl_called[t] += 1

print("=== high-confidence (>=2 runs OR bl-called OR push_lr prologue) ===")
hc = []
for t, n in sorted(strong.items()):
    h0 = u16(t & ~1)
    push = (h0 & 0xFF00) == 0xB500 and (h0 & 0x0100)
    nbl = bl_called.get(t, 0)
    if n >= 2 or nbl > 0 or push:
        hc.append((t, n, nbl, push))
        print(f"  {t:05X}: runs={n} bl={nbl} push={push}")
print(f"high-confidence: {len(hc)}", file=sys.stderr)
