#!/usr/bin/env python3
"""Wave 36-B .s post-process for 0x0800eed4 (C + .s patch, NOT pure C).

agbcc folds the OR-target base +20 into the literal pool (q+20 with a
plain [r1] load) where the ROM keeps the base in the pool and uses a
[r1, #20] offset, and it loads the function-pointer table after the
index shift where the ROM loads it first. This patch UNFOLDS the pool
constant (q+20 -> q, same effective address once the offset form is
used) and reorders the table load ahead of the index load. No
instruction is added or removed, so code size and pool position are
unchanged. Each pattern must match the asserted count.
"""
import sys
p = sys.argv[1]
s = open(p).read()

def rep(old, new, n=1):
    global s
    assert s.count(old) == n, f"pattern {old!r} count {s.count(old)} want {n}"
    s = s.replace(old, new)

# 1. unfold q+20 (0x02004e54 = 33574484) to q base (0x02004e40 = 33574464), both clusters
rep("\t.word\t33574484\n", "\t.word\t33574464\n", 2)
# 2. shared OR uses the #20 offset form
rep("\tldrb\tr3, [r1]\n\torr\tr0, r0, r3\n\tstrb\tr0, [r1]\n",
    "\tldrb\tr3, [r1, #20]\n\torr\tr0, r0, r3\n\tstrb\tr0, [r1, #20]\n", 1)
# 3. table load ahead of the index load
rep("\tldrb\tr1, [r2]\n\tlsl\tr0, r1, #2\n\tldr\tr3, .L9+4\n\tadd\tr0, r0, r3\n\tldr\tr1, [r0]\n",
    "\tldr\tr1, .L9+4\n\tldrb\tr3, [r2]\n\tlsl\tr0, r3, #2\n\tadd\tr0, r0, r1\n\tldr\tr1, [r0]\n", 1)
open(p, "w").write(s)
print("patch ok")
