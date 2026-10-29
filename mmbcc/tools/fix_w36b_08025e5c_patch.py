#!/usr/bin/env python3
"""Wave 36-B .s post-process for 0x08025e5c (C + .s patch, NOT pure C).

agbcc folds the loop index into an ldrb offset (s+i, then [r0, #2])
where the ROM computes s+2+i with two adds and a plain load. This patch
replaces the 2-instruction form with the ROM 3-instruction form (+2 B,
exactly filling the code-size gap; the trailing 00 00 pad in the C file
supplies the other 2 B). Each pattern must match the asserted count.
"""
import sys
p = sys.argv[1]
s = open(p).read()

def rep(old, new, n=1):
    global s
    assert s.count(old) == n, f"pattern {old!r} count {s.count(old)} want {n}"
    s = s.replace(old, new)

rep("\tadd\tr0, r4, r5\n\tldrb\tr1, [r0, #2]\n",
    "\tadd\tr0, r5, #2\n\tadd\tr0, r0, r4\n\tldrb\tr1, [r0]\n", 1)
open(p, "w").write(s)
print("patch ok")
