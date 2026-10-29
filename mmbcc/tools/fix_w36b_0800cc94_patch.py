#!/usr/bin/env python3
"""Wave 36-B .s post-process for 0x0800cc94 (C + .s patch, NOT pure C).

agbcc allocates the table index to r1, which blocks the scheduler from
hoisting the table pool load above the byte load, and it picks r2/r1 for
the two halfword RMW values where the ROM uses r3/r2. This patch only
REORDERS existing instructions and renames registers (no instruction is
added or removed), so code size and pool position are unchanged.
Each pattern must match the asserted count.
"""
import sys
p = sys.argv[1]
s = open(p).read()

def rep(old, new, n=1):
    global s
    assert s.count(old) == n, f"pattern {old!r} count {s.count(old)} want {n}"
    s = s.replace(old, new)

# 1. prologue: both pool loads first, index in r3
rep("\tldr\tr2, .L5\n\tldrb\tr1, [r2]\n\tlsl\tr0, r1, #1\n\tldr\tr1, .L5+4\n\tadd\tr0, r0, r1\n",
    "\tldr\tr2, .L5\n\tldr\tr1, .L5+4\n\tldrb\tr3, [r2]\n\tlsl\tr0, r3, #1\n\tadd\tr0, r0, r1\n", 1)
# 2. first-branch OR value in r3, not r2
rep("\tldrh\tr2, [r1]\n\torr\tr0, r0, r2\n",
    "\tldrh\tr3, [r1]\n\torr\tr0, r0, r3\n", 1)
# 3. else-branch AND: base in r2, value in r1
rep("\tldr\tr1, .L7\n\tldr\tr0, .L7+4\n\tldrh\tr2, [r1]\n\tand\tr0, r0, r2\n\tstrh\tr0, [r1]\n",
    "\tldr\tr2, .L7\n\tldr\tr0, .L7+4\n\tldrh\tr1, [r2]\n\tand\tr0, r0, r1\n\tstrh\tr0, [r2]\n", 1)
# 4. else-branch field load after the mask constant, value in r2
rep("\tldrh\tr0, [r1, #10]\n\tmov\tr1, #248\n\tlsl\tr1, r1, #5\n\tand\tr1, r1, r0\n",
    "\tmov\tr1, #248\n\tlsl\tr1, r1, #5\n\tldrh\tr2, [r2, #10]\n\tand\tr1, r1, r2\n", 1)
open(p, "w").write(s)
print("patch ok")
