#!/usr/bin/env python3
"""Region-wide BL scan: find novel targets (not in v2/v2.1/v2.2, any tier)
in unknown regions; validate each. These are the '39 novel' from the v2.2
audit minus the 5 data false-positives, plus any missed."""
import sys, struct
from collections import defaultdict
import gen_func_list_v2 as g

rom = g.rom
def u16(off): return struct.unpack_from('<H', rom, off)[0]
def bt(bl):
    hi = u16(bl); lo = u16(bl+2)
    if (hi & 0xF800) != 0xF000 or (lo & 0xF800) != 0xF800: return None
    o = ((hi & 0x7FF) << 12) | ((lo & 0x7FF) << 1)
    if o & (1 << 22): o -= (1 << 23)
    t = bl + 4 + o
    return t if 0 <= t < 0x50000 else None

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

# all listed offsets (any tier)
listed = set()
for fn in ('func_list_v2.txt', 'func_list_v2_1_addendum.txt', 'func_list_v2_2_addendum.txt'):
    for line in open(fn):
        line = line.strip()
        if line and not line.startswith('#'):
            listed.add(int(line.split()[0], 16))

co = defaultdict(list)
for off in range(0, 0x50000-4, 2):
    hi = u16(off)
    if (hi & 0xF800) == 0xF000 and (u16(off+2) & 0xF800) == 0xF800:
        t = bt(off)
        if t is not None: co[t].append(off)

novel = {t: v for t, v in co.items() if t not in listed}
print(f"distinct BL targets: {len(co)}, novel (unlisted): {len(novel)}", file=sys.stderr)
# only unknown-class novel targets
unk_novel = {t: v for t, v in novel.items() if bcls(t) == 'unknown'}
print(f"novel in unknown regions: {len(unk_novel)}", file=sys.stderr)
results = []
for t in sorted(unk_novel):
    v = g.validate_target(t, 'T')
    # caller genuineness: caller byteclass distribution
    cl = defaultdict(int)
    for c in unk_novel[t]: cl[bcls(c)] += 1
    results.append((t, v, len(unk_novel[t]), dict(cl)))
    print(f"  {t:05X}: validate={v} callers={len(unk_novel[t])} caller_cls={dict(cl)}")
