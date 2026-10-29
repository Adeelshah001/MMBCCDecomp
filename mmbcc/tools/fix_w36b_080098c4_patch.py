#!/usr/bin/env python3
"""Wave 36-B .s post-process for 0x080098c4 (C + .s patch, NOT pure C).

agbcc emits the two pool-mask loads (r5/r6) immediately after the base
load and computes buf[0]'s shift in the opposite order; the ROM
interleaves the loads inside the buf[0] computation and keeps the final
buf[1] ORR result in r0. This patch only REORDERS existing instructions
and swaps the final ORR/STR destination register (r4 -> r0); it adds no
instructions, so code size and pool position are unchanged.
Each pattern must match the asserted count.
"""
import sys
p = sys.argv[1]
s = open(p).read()

def rep(old, new, n=1):
    global s
    assert s.count(old) == n, f"pattern {old!r} count {s.count(old)} want {n}"
    s = s.replace(old, new)

# 1. remove the two early mask loads
rep("\tldr\tr5, .L3+4\n", "", 1)
rep("\tldr\tr6, .L3+8\n", "", 1)
# 2. ROM order: and -> ldr r5 -> lsr r0,#29 -> lsl r0,#17 -> ldr r6 -> lsr r4,#24
rep("\tand\tr4, r4, r0\n\tlsr\tr4, r4, #24\n\tlsr\tr0, r0, #29\n\tlsl\tr0, r0, #17\n",
    "\tand\tr4, r4, r0\n\tldr\tr5, .L3+4\n\tlsr\tr0, r0, #29\n\tlsl\tr0, r0, #17\n\tldr\tr6, .L3+8\n\tlsr\tr4, r4, #24\n", 1)
# 3. final buf[1] ORR result in r0, not r4
rep("\torr\tr4, r4, r0\n\tstr\tr4, [sp, #4]\n",
    "\torr\tr0, r0, r4\n\tstr\tr0, [sp, #4]\n", 1)
open(p, "w").write(s)
print("patch ok")
