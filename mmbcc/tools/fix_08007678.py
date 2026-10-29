#!/usr/bin/env python3
"""Post-process agbcc .s for d34_08007678_MATCHED.c (0x08007678).

Patch: rotate 3 instructions in x!=0 branch.
  agbcc emits:  ldrb r0,[r0] / lsl r0,r0,#2 / ldr r1,.L7+8
  ROM wants:    ldr r1,.L7+8 / ldrb r0,[r0] / lsl r0,r0,#2
(the base=0x08170e7c ldr must precede the ldrb; scheduler places it late).
Applied to the .s BEFORE assembling (labels recalc).
"""
import sys

path = sys.argv[1]
lines = open(path).read().splitlines(keepends=True)

a = ["\tldrb\tr0, [r0]\n", "\tlsl\tr0, r0, #2\n"]
# find ldrb/lsl followed by ldr r1
idx = None
for i in range(len(lines) - 2):
    if lines[i:i+2] == a and lines[i+2].startswith("\tldr\tr1, "):
        idx = i
        break
assert idx is not None, "ldrb/lsl/ldr-r1 sequence not found"
ldr_line = lines[idx+2]
lines[idx:idx+3] = [ldr_line] + a

open(path, "w").writelines(lines)
print("patch OK: rotated ldrb/lsl/ldr-r1")
