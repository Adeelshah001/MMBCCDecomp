#!/usr/bin/env python3
"""Post-process old_agbcc .s for w36d_0801b04c (0x0801b04c).

Patch: table-base load must precede the index load.
  agbcc emits:  ldrb r1,[r4,#17] / ldr r3,.Lx / add r0,r1,r3 / ldrb r0,[r0]
  ROM wants:    ldr r0,.Lx / ldrb r1,[r4,#17] / add r0,r1,r0 / ldrb r0,[r0]
Applied to the .s BEFORE assembling (labels recalc).
"""
import sys, re

path = sys.argv[1]
lines = open(path).read().splitlines(keepends=True)

idx = None
lab = None
for i in range(len(lines) - 3):
    if lines[i].strip() == "ldrb\tr1, [r4, #17]":
        m = re.match(r"\tldr\tr3, (\S+)\n", lines[i+1])
        if m and lines[i+2].strip() == "add\tr0, r1, r3" and lines[i+3].strip() == "ldrb\tr0, [r0]":
            idx, lab = i, m.group(1)
            break
assert idx is not None, "table-load sequence not found"
lines[idx:idx+4] = [
    "\tldr\tr0, %s\n" % lab,
    "\tldrb\tr1, [r4, #17]\n",
    "\tadd\tr0, r1, r0\n",
    "\tldrb\tr0, [r0]\n",
]
open(path, "w").writelines(lines)
print("patch OK: table-base load moved before index load")
