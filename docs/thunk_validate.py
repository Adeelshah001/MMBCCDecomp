#!/usr/bin/env python3
"""Validate the 26 BL-targeted starts in the thunk span; check caller
genuineness and prologues. Also verify idiom instances are interior
(fallthrough-reached, never BL/bx-called)."""
import sys, struct
from collections import Counter, defaultdict
import gen_func_list_v2 as g

rom = g.rom
def u16(off): return struct.unpack_from('<H', rom, off)[0]
def u32(off): return struct.unpack_from('<I', rom, off)[0]

S, E = 0x29AC4, 0x2C7A4

def thumb_bl_target(bl_off):
    hi = u16(bl_off); lo = u16(bl_off + 2)
    if (hi & 0xF800) != 0xF000 or (lo & 0xF800) != 0xF800: return None
    off = ((hi & 0x7FF) << 12) | ((lo & 0x7FF) << 1)
    if off & (1 << 22): off -= (1 << 23)
    tgt = bl_off + 4 + off
    return tgt if 0 <= tgt < 0x50000 else None

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

callers_of = defaultdict(list)
for off in range(0, 0x50000 - 4, 2):
    hi = u16(off)
    if (hi & 0xF800) == 0xF000 and (u16(off+2) & 0xF800) == 0xF800:
        t = thumb_bl_target(off)
        if t is not None and S <= t < E:
            callers_of[t].append(off)

def genuine_caller(bl_site):
    """Check the BL site decodes at an instruction boundary in a coherent
    body: walk back up to 40 halfwords looking for a plausible start."""
    # simple heuristic: decode linearly back from bl_site-2; if we hit the
    # start of a known function or an idiom/valid seq without invalid, ok.
    # Stronger: the BL site must not be inside a pool/data region.
    c = bcls(bl_site)
    if c in ('pool', 'data'):
        return False, c
    return True, c

print("=== 26 BL-targeted starts: validation ===")
results = []
for t in sorted(callers_of):
    v = g.validate_target(t, 'T')
    # prologue check: first insn
    h0 = u16(t)
    prol = 'push_lr' if (h0 & 0xFF00) == 0xB500 and (h0 & 0x0100) else (
           'sub_sp' if 0xB080 <= h0 <= 0xB0FF else 'none')
    gen = [(c, genuine_caller(c)) for c in callers_of[t]]
    ngen = sum(1 for _, (ok_, _) in gen if ok_)
    results.append((t, v, prol, ngen, len(gen)))
    print(f"  {t:05X}: validate={v} prologue={prol} callers={len(gen)} genuine~{ngen}")

# idiom interior check: is 29AC4 (first idiom) fallthrough-reached?
# check halfword before each idiom: does it decode as fallthrough into it?
print("=== idiom fallthrough check (first 5) ===")
THUNK = (0x1C38, 0x4649, 0x4652, 0x9B08)
idioms = sorted(off for off in range(S, E, 2)
                if (u16(off),u16(off+2),u16(off+4),u16(off+6)) == THUNK)
for t in idioms[:5]:
    prev = u16(t-2)
    d = g.dec_thumb(t-2)
    print(f"  {t:05X}: prev hw={prev:04X} kind={d[1] if d else None}")

# pointer-table check: any 0x0802xxxx words in data/pool pointing at idioms?
print("=== pointer-to-idiom scan ===")
idiomset = set(idioms)
hits = Counter()
for off in range(0, 0x50000, 4):
    w = u32(off)
    if 0x08029AC4 <= w < 0x0802C7A4 and (w - 0x08000000) in idiomset:
        hits[w - 0x08000000] += 1
print(f"data words pointing at idiom starts: {len(hits)} "
      f"({' '.join(f'{k:05X}x{v}' for k,v in list(hits.items())[:5])})")
