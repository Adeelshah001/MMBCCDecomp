#!/usr/bin/env python3
"""Wave 36-B .s post-process for 0x0800ed44 (C + .s patch, NOT pure C).

agbcc puts the store address in r0/r1 (base uniformly in r2) where the
ROM puts the base in r0/r1 and the store address uniformly in r2, and it
emits the table halfword load as ldrh + lsl/asr (agbcc never emits ldrsh
from C) where the ROM uses movs + ldrsh with a register offset. This
patch only REORDERS existing instructions and renames registers, except
for the ldrh + lsl/asr -> movs + ldrsh swap, which is exactly compensated
by the ROM's nonzero-path base copy (adds r0, r1) that the unpatched
code lacks; instruction counts are unchanged on both paths, so code size
and pool position are unchanged. Each pattern must match the asserted count.
"""
import sys
p = sys.argv[1]
s = open(p).read()

def rep(old, new, n=1):
    global s
    assert s.count(old) == n, f"pattern {old!r} count {s.count(old)} want {n}"
    s = s.replace(old, new)

# 1. zero-branch store: base in r0, address in r2, jump past the copy
rep("\tldr\tr2, .L7+4\n\tadd\tr0, r2, #0\n\tadd\tr0, r0, #43\n\tstrb\tr3, [r0]\n\tb\t.L4\n",
    "\tldr\tr0, .L7+4\n\tadd\tr2, r0, #0\n\tadd\tr2, r2, #43\n\tstrb\tr3, [r2]\n\tb\t.L4b\n", 1)
# 2. nonzero-branch store: base in r1, address in r2
rep("\tldr\tr2, .L9+4\n\tadd\tr1, r2, #0\n\tadd\tr1, r1, #43\n\tmov\tr0, #1\n\tstrb\tr0, [r1]\n",
    "\tldr\tr1, .L9+4\n\tadd\tr2, r1, #0\n\tadd\tr2, r2, #43\n\tmov\tr0, #1\n\tstrb\tr0, [r2]\n", 1)
# 3. common code: nonzero-path base copy + ROM load order + ldrsh
rep(".L4:\n\tldrb\tr0, [r2, #6]\n\tlsl\tr0, r0, #2\n\tldr\tr1, .L9+8\n\tadd\tr0, r0, r1\n\tldrh\tr3, [r0, #2]\n\tadd\tr0, r5, #0\n\tlsl\tr3, r3, #16\n\tasr\tr3, r3, #16\n\tadd\tr1, r4, #0\n",
    "\tadd\tr0, r1, #0\n\t.L4b:\n\tldr\tr1, .L9+8\n\tldrb\tr0, [r0, #6]\n\tlsl\tr0, r0, #2\n\tadd\tr0, r0, r1\n\tmov\tr1, #2\n\tldrsh\tr3, [r0, r1]\n\tadd\tr0, r5, #0\n\tadd\tr1, r4, #0\n", 1)
open(p, "w").write(s)
print("patch ok")
