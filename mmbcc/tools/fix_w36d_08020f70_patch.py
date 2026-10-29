#!/usr/bin/env python3
"""Rewrite 20f70 prologue to ROM order: b->r6, c->r7, a->r4, then
cmp/beq set1 with duplicated r0=0 in both branches."""
import sys
path = sys.argv[1]
lines = open(path).read().splitlines(keepends=True)
def find(pred, start=0):
    for i in range(start, len(lines)):
        if pred(lines[i].strip()):
            return i
    return -1
# Find the prologue block: from `add r7, r2, #0` to the `mov r3, #0` before bl.
a = find(lambda s: s == "add\tr7, r2, #0")
assert a >= 0
# Verify the expected sequence follows.
seq = ["lsl\tr0, r0, #24", "lsr\tr4, r0, #24", "add\tr6, r1, #0",
       "mov\tr1, #0", "cmp\tr4, #14"]
for k, exp in enumerate(seq):
    assert lines[a+1+k].strip().startswith(exp), (k, lines[a+1+k])
b = find(lambda s: s.startswith("bne\t.L3"), a)
assert b >= 0
c = find(lambda s: s == "mov\tr1, #1", b)
assert c == b+1
d = find(lambda s: s == ".L3:", c)
assert d >= 0
e = find(lambda s: s == "mov\tr3, #0", d)
assert e >= 0
# Replace lines[a:e+1] (through mov r3) with ROM prologue, keeping .L3 as done.
new = [
    "\tadd\tr6, r1, #0\n",
    "\tadd\tr7, r2, #0\n",
    "\tlsl\tr0, r0, #24\n",
    "\tlsr\tr4, r0, #24\n",
    "\tcmp\tr4, #14\n",
    "\tbeq\t.Lset1\n",
    "\tmov\tr0, #0\n",
    "\tmov\tr1, #0\n",
    "\tb\t.L3\n",
    ".Lset1:\n",
    "\tmov\tr0, #0\n",
    "\tmov\tr1, #1\n",
    ".L3:\n",
    "\tmov\tr2, #0\n",
    "\tmov\tr3, #0\n",
]
lines[a:e+1] = new
# Table reorder: pool2 must load before the byte load, into r0 (not r2).
# Current: ldrb r1,[r5,#17]; ldr r2,.Lx; adds r0,r1,r2
# Wanted:  ldr r0,.Lx; ldrb r1,[r5,#17]; adds r0,r1,r0
i2 = find(lambda s: s == "ldrb\tr1, [r5, #17]")
assert i2 >= 0
assert lines[i2+1].strip().startswith("ldr\tr2,")
assert lines[i2+2].strip() == "add\tr0, r1, r2"
poolref = lines[i2+1].strip().split(", ", 1)[1]
lines[i2:i2+3] = [
    f"\tldr\tr0, {poolref}\n",
    "\tldrb\tr1, [r5, #17]\n",
    "\tadd\tr0, r1, r0\n",
]
open(path, "w").writelines(lines)
print("patch OK: 20f70 prologue + table")
