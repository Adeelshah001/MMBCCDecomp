#!/usr/bin/env python3
"""Extended prologue scan over unknown regions: push{..,lr}, and idiom-family
starts. Validate each candidate not already listed."""
import sys, struct
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
unknown = [(s,e) for s,e,c in spans if c == 'unknown']

listed = set()
for fn in ('func_list_v2.txt', 'func_list_v2_1_addendum.txt', 'func_list_v2_2_addendum.txt'):
    for line in open(fn):
        line = line.strip()
        if line and not line.startswith('#'):
            listed.add(int(line.split()[0], 16))

cands = {}  # off -> kind
for s, e in unknown:
    for off in range(s, e, 2):
        h = u16(off)
        if (h & 0xFF00) == 0xB500 and (h & 0x0100):  # push ..,lr
            if off not in listed:
                cands[off] = 'push_lr'
        # idiom family: 1C38 4649 XXXX 9B08 (but not the strict thunk already known-interior)
        # skip: these are interior points, not entries (proven). Only note if BL-called (already covered).

print(f"push_lr candidates in unknown (unlisted): {len(cands)}", file=sys.stderr)
good = []
for off, k in sorted(cands.items()):
    v = g.validate_target(off, 'T')
    if v:
        good.append(off)
print(f"validate=True: {len(good)}", file=sys.stderr)
for off in good[:40]:
    print(f"  {off:05X} push_lr")
if len(good) > 40:
    print(f"  ... +{len(good)-40} more", file=sys.stderr)
