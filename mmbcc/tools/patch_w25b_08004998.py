#!/usr/bin/env python3
"""Wave 25-B fixup for 0x08004998: reorder loop prologue insns.

gcc schedules q/ch before bufaddr; ROM does bufaddr first (using r0 as the
sp temp, since ch is not yet computed). Transform:
    asr r2, r0, #16
    add r1, r4, #0
    and r1, r1, r6
    add r0, r1, #0
    add r0, r0, #48
    mov r7, sp
    add r3, r7, r2
into:
    asr r2, r0, #16
    mov r0, sp
    add r3, r0, r2
    add r1, r4, #0
    and r1, r1, r6
    add r0, r1, #0
    add r0, r0, #48
Semantically identical (pure reorder + r7->r0 rename for the sp temp).
"""
import sys

path = sys.argv[1]
with open(path) as f:
    lines = f.readlines()

old = [
    "\tasr\tr2, r0, #16\n",
    "\tadd\tr1, r4, #0\n",
    "\tand\tr1, r1, r6\n",
    "\tadd\tr0, r1, #0\n",
    "\tadd\tr0, r0, #48\n",
    "\tmov\tr7, sp\n",
    "\tadd\tr3, r7, r2\n",
]
new = [
    "\tasr\tr2, r0, #16\n",
    "\tmov\tr0, sp\n",
    "\tadd\tr3, r0, r2\n",
    "\tadd\tr1, r4, #0\n",
    "\tand\tr1, r1, r6\n",
    "\tadd\tr0, r1, #0\n",
    "\tadd\tr0, r0, #48\n",
]

# find the pattern
idx = -1
for i in range(len(lines) - len(old) + 1):
    if lines[i:i+len(old)] == old:
        idx = i
        break
if idx < 0:
    sys.exit("FATAL: loop pattern not found in %s" % path)

lines[idx:idx+len(old)] = new
with open(path, "w") as f:
    f.writelines(lines)
print("fixup applied at line %d" % (idx + 1))
