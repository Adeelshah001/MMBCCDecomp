#!/usr/bin/env python3
"""Rewrite 22290 table block: pools pool1 (r3) and pool2 (r2) loaded upfront
before the s17 computation, and swap the first two pool words so pool order
is pool1, pool2, pool3 (ROM order)."""
import sys
path = sys.argv[1]
lines = open(path).read().splitlines(keepends=True)
def find(pred, start=0):
    for i in range(start, len(lines)):
        if pred(lines[i].strip()):
            return i
    return -1
# Table block: the `ldrb r0, [r5, #17]` followed by `lsl r1, r0, #1`.
a = find(lambda s: s == "ldrb\tr0, [r5, #17]")
assert a >= 0 and lines[a+1].strip() == "lsl\tr1, r0, #1", lines[a+1]
# Verify the block shape through bl 225b4.
b = find(lambda s: s.startswith("bl\tSub_080225B4"), a)
assert b >= 0
# The block is lines[a:b+1]; replace with ROM form. Pool label is .L11
# (found from the ldr lines); pool1 -> .L11, pool2 -> .L11+4 after swap.
lines[a:b+1] = [
    "\tldr\tr3, .L11\n",
    "\tldr\tr2, .L11+4\n",
    "\tldrb\tr0, [r5, #17]\n",
    "\tlsl\tr1, r0, #1\n",
    "\tadd\tr1, r1, r2\n",
    "\tldrh\tr2, [r1]\n",
    "\tlsr\tr1, r2, #8\n",
    "\tlsl\tr1, r1, #1\n",
    "\tadd\tr1, r1, r3\n",
    "\tldrb\tr4, [r1]\n",
    "\tadd\tr0, r0, #3\n",
    "\torr\tr0, r0, r2\n",
    "\tmov\tr1, #0\n",
    "\tbl\tSub_080225B4\n",
]
# Swap the first two pool words (.L11: pool2 <-> pool1).
p = find(lambda s: s == ".L11:")
assert p >= 0
assert lines[p+1].strip() == ".word\t136474800", lines[p+1]
assert lines[p+2].strip() == ".word\t135739634", lines[p+2]
lines[p+1], lines[p+2] = lines[p+2], lines[p+1]
# Final block: byte load must go to r1 (not r2), and OR with r1.
f = find(lambda s: s == "ldrb\tr2, [r6, #19]")
assert f >= 0
assert lines[f+1].strip() == "orr\tr0, r0, r2"
lines[f] = "\tldrb\tr1, [r6, #19]\n"
lines[f+1] = "\torr\tr0, r0, r1\n"
open(path, "w").writelines(lines)
print("patch OK: 22290 table + pools + final r1")
