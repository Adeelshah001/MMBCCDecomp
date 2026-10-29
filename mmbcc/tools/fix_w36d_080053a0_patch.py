#!/usr/bin/env python3
"""Match ROM prologue pool order (base, off1, val1, v2).
agbcc emits loads r5(v2) then r0(val1) and pools v2 then val1.
Patch: swap the two load lines, swap their pool offsets, swap the two
pool words, so loads are r0(val1) then r5(v2) and pools are val1 then v2.
"""
import sys, re
path = sys.argv[1]
lines = open(path).read().splitlines(keepends=True)
def find(pred, start=0):
    for i in range(start, len(lines)):
        if pred(lines[i].strip()):
            return i
    return -1
i = find(lambda s: s.startswith("ldr\tr5,"))
j = find(lambda s: s.startswith("ldr\tr0,"), i+1)
assert i >= 0 and j == i+1, (i, j)
# Parse offsets: r5 line references .L5+8 (v2), r0 line references .L5+12 (val1).
m5 = re.search(r"(\.L\d+)\+(\d+)", lines[i])
m0 = re.search(r"(\.L\d+)\+(\d+)", lines[j])
assert m5 and m0 and m5.group(1) == m0.group(1), (lines[i], lines[j])
base, off5, off0 = m5.group(1), m5.group(2), m0.group(2)
# Swap lines AND offsets: r0 line first with v2's old offset swapped to val1's
# position after the pool swap. Simplest: rewrite both lines explicitly.
lines[i] = f"\tldr\tr0, {base}+{off5}\n"
lines[j] = f"\tldr\tr5, {base}+{off0}\n"
# Interleave: move the val1 store (str r0, [r6]) to between the two loads,
# so the prologue is ldr val1, str val1, ldr v2, str v2 (ROM order).
si = find(lambda s: s == "str\tr0, [r6]")
assert si == j+1, si
lines.insert(i+1, lines.pop(si))
# Swap the two pool words (v2=100679680, val1=100667392).
a = find(lambda s: s == ".word\t100679680")
b = find(lambda s: s == ".word\t100667392")
assert a >= 0 and b >= 0
lines[a], lines[b] = lines[b], lines[a]
open(path, "w").writelines(lines)
print("patch OK: prologue load/offset/pool swap")
