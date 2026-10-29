#!/usr/bin/env python3
"""Post-process old_agbcc .s for w36d_0800cde8 (0x0800cde8).
ROM layout: case3 swap + halfword (ldr r2,pool1; ldr r0,pool2; ldrh r1;
  and; ldr r1,pool3; and; strh; b end), pools (pool1,pool2,pool3),
  set0 (mov r5,0), end. agbcc: case3 set0 first, swap+halfword (folded
  single AND, pools at end), end. Patch: rewrite halfword block, move
  set0 after pools, move pools to middle, add b end after halfword.
"""
import sys
path = sys.argv[1]
lines = open(path).read().splitlines(keepends=True)

def find(pred, start=0):
    for i in range(start, len(lines)):
        if pred(lines[i].strip()):
            return i
    return -1

# 1. Extract and remove the set0 block from .L11 (mov r5,#0; b .L3)
i = find(lambda s: s == "mov\tr5, #0")
assert i >= 0
assert lines[i+1].strip() == "b\t.L3", lines[i+1]
set0 = lines[i:i+2]
del lines[i:i+2]
# 2. Rewrite the halfword block in .L12 (ldr r1,.L18; ldr r0,.L18+4;
#    ldrh r2,[r1]; and; strh) to ROM form, and add b .L3 after it.
j = find(lambda s: s == "ldr\tr1, .L18")
assert j >= 0
assert lines[j+1].strip() == "ldr\tr0, .L18+4"
assert lines[j+2].strip() == "ldrh\tr2, [r1]"
assert lines[j+3].strip() == "and\tr0, r0, r2"
assert lines[j+4].strip() == "strh\tr0, [r1]"
lines[j:j+5] = [
    "\tldr\tr2, .Lpool1\n",
    "\tldr\tr0, .Lpool2\n",
    "\tldrh\tr1, [r2]\n",
    "\tand\tr0, r0, r1\n",
    "\tldr\tr1, .Lpool3\n",
    "\tand\tr0, r0, r1\n",
    "\tstrh\tr0, [r2]\n",
    "\tb\t.L3\n",
]
# 3. Remove the old pool block (.L18: .word, .word) and .L19/.align if present.
k = find(lambda s: s == ".L18:")
assert k >= 0
# .L18 block: .L18:, .word, .word (and possibly .L19/.align before it)
# Find .L19 (align) before .L18 and remove both.
m = find(lambda s: s == ".L19:")
if m >= 0 and m < k:
    del lines[m:k+3]
else:
    del lines[k:k+3]
# 4. Insert the new pools + set0 before .L3 (end). .L3 is the end label.
n = find(lambda s: s == ".L3:")
assert n >= 0
lines[n:n] = [
    "\t.align\t2, 0\n",
    ".Lpool1:\n",
    "\t.word\t33567200\n",
    ".Lpool2:\n",
    "\t.word\t60927\n",
    ".Lpool3:\n",
    "\t.word\t56319\n",
    ".Lset0:\n",
    "\tmov\tr5, #0\n",
]
# Fix case3 branch: the original `bne .L12` (not-equal -> swap) must become
# `beq .Lset0` (equal -> set0 after pools), since set0 moved.
for i, ln in enumerate(lines):
    if ln.strip().startswith("bne\t.L12"):
        lines[i] = "\tbeq\t.Lset0\t@cond_branch\n"
        break
open(path, "w").writelines(lines)
print("patch OK: halfword split + pools/set0 moved")
