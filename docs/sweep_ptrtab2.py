#!/usr/bin/env python3
"""Strict pointer-table sweep: unlisted unknown targets pointed to by table
runs (>=3 consecutive 0x0800xxxx) or >=3 distinct locations. Target must have
a STRONG function shape: forward decode reaches bx lr / pop{pc} / mov pc,lr
within 120 insns (not merely validate-ok). Excludes self-overlapping tables."""
import sys, struct
from collections import defaultdict
import gen_func_list_v2 as g

rom = g.rom
def u16(off): return struct.unpack_from('<H', rom, off)[0]
def u32(off): return struct.unpack_from('<I', rom, off)[0]

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

def is_ptr(w):
    return 0x08000000 <= w < 0x08050000

# find table runs: >=3 consecutive 4-byte pointers
runs = []  # (start_off, [targets])
off = 0
N = len(rom)
while off < N - 12:
    if is_ptr(u32(off)) and is_ptr(u32(off+4)) and is_ptr(u32(off+8)):
        t0 = off
        tgts = []
        while off < N - 4 and is_ptr(u32(off)):
            tgts.append(u32(off) - 0x08000000)
            off += 4
        runs.append((t0, tgts))
    else:
        off += 4
print(f"table runs (>=3): {len(runs)}", file=sys.stderr)

def strong_shape(tgt):
    """Forward decode up to 120 insns; True if reaches bx lr/pop pc/mov pc,lr
    without invalid and without leaving 0..0x50000."""
    seen = set()
    pc = tgt & ~1
    for _ in range(120):
        if pc in seen or not (0 <= pc < 0x50000) or pc & 1:
            return False
        seen.add(pc)
        d = g.dec_thumb(pc)
        if d is None or d[1] == 'invalid':
            return False
        h = u16(pc)
        if h == 0x4770:  # bx lr
            return True
        if (h & 0xFF00) == 0xBD00 and (h & 0x0100):  # pop {..,pc}
            return True
        if h == 0x46F6:  # mov pc, lr
            return True
        sz, kind, t2 = d[0], d[1], d[2]
        if kind == 'b':
            pc = t2 & ~1; continue
        if kind == 'bcond':
            # follow fallthrough only (conservative)
            pc += sz; continue
        if kind in ('bx',):
            return False  # indirect exit: not strong enough alone
        pc += sz
    return False

# collect targets from runs
from collections import Counter
tgt_runs = Counter()  # tgt -> number of runs pointing to it
tgt_locs = defaultdict(list)
for roff, tgts in runs:
    for w in tgts:
        t = w & ~1
        if bcls(t) == 'unknown' and t not in listed and not (roff <= t < roff + 4*len(tgts)):
            tgt_runs[t] += 1
            tgt_locs[t].append(roff)

print(f"unlisted unknown targets from tables: {len(tgt_runs)}", file=sys.stderr)
strong = []
for t, n in sorted(tgt_runs.items()):
    if strong_shape(t):
        strong.append((t, n))
        print(f"  {t:05X}: {n} table-runs strong_shape=True")
print(f"STRONG candidates: {len(strong)}", file=sys.stderr)
