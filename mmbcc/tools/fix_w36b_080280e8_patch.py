#!/usr/bin/env python3
"""Wave 36-B .s post-process for 0x080280e8 (C + .s patch, NOT pure C).

agbcc folds the table2+7 and table2+8 addresses into two separate pool
words and loads the signed byte with ldrb + lsl/asr, where the ROM keeps
a single table2 pool word, loads the byte with movs + ldrsb (register
offset; agbcc never emits ldrsb from C), and computes +8 with two adds
reusing the table register. This patch swaps the test sequence (4 -> 3
instructions) and the call sequence (2 -> 3 instructions, net code size
unchanged), retargets the pool word from table2+7 to table2, and deletes
the now-dead table2+8 pool word (-4 B, exactly the size gap).
Each pattern must match the asserted count.
"""
import sys
p = sys.argv[1]
s = open(p).read()

def rep(old, new, n=1):
    global s
    assert s.count(old) == n, f"pattern {old!r} count {s.count(old)} want {n}"
    s = s.replace(old, new)

rep("\tldr\tr0, .L5+4\n\tldrb\tr0, [r0, #0]\n\tlsl\tr0, r0, #24\n\tasr\tr0, r0, #24\n",
    "\tldr\tr1, .L5+4\n\tmov\tr0, #7\n\tldrsb\tr0, [r1, r0]\n", 1)
rep("\tldr\tr0, .L5+8\n\tbl\tSub_0800E144\n",
    "\tadd\tr0, r1, #0\n\tadd\tr0, #8\n\tbl\tSub_0800E144\n", 1)
rep("\t.word\t33601511\n", "\t.word\t33601504\n", 1)
rep("\t.word\t33601512\n", "", 1)
open(p, "w").write(s)
print("patch ok")
