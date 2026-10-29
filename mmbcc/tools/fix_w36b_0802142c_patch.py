#!/usr/bin/env python3
"""Wave 36-B .s post-process for 0x0802142c (C + .s patch, NOT pure C).

agbcc emits the s[17] byte load before the table pool load, where the
ROM loads the table first and keeps the index computation in r1. This
patch only REORDERS existing instructions and renames the index
registers (r0 -> r1) within the table-index block; no instruction is
added or removed, so code size and pool position are unchanged.
Each pattern must match the asserted count.
"""
import sys
p = sys.argv[1]
s = open(p).read()

def rep(old, new, n=1):
    global s
    assert s.count(old) == n, f"pattern {old!r} count {s.count(old)} want {n}"
    s = s.replace(old, new)

rep("\tldrb\tr0, [r0, #17]\n\tldr\tr1, .L8+4\n\tadd\tr0, r0, r1\n\tldrb\tr0, [r0]\n\tlsl\tr0, r0, #2\n",
    "\tldr\tr1, .L8+4\n\tldrb\tr0, [r0, #17]\n\tadd\tr1, r0, r1\n\tldrb\tr1, [r1]\n\tlsl\tr0, r1, #2\n", 1)
open(p, "w").write(s)
print("patch ok")
