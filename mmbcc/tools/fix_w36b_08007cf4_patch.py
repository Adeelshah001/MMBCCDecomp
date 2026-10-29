import sys
s = open(sys.argv[1]).read()
def rep(old, new):
    global s
    assert s.count(old) == 1, f"expected 1 occurrence of {old!r}, got {s.count(old)}"
    s = s.replace(old, new)
# 1. entry temp swap: idx*8 in r2, table in r1 (ROM order)
rep("\tlsl\tr1, r0, #3", "\tlsl\tr2, r0, #3")
rep("\tldr\tr2, .L7", "\tldr\tr1, .L7")
rep("\tadd\tr4, r1, r2", "\tadd\tr4, r2, r1")
# 2. f7 &= : result in r1 (m's register), not r2
rep("\tand\tr2, r2, r1", "\tand\tr1, r1, r2")
rep("\tstrb\tr2, [r4, #7]", "\tstrb\tr1, [r4, #7]")
# 3. &1 test: result in r1 (f7 temp), operands r1,r0
rep("\tand\tr0, r0, r2", "\tand\tr1, r1, r0")
# 3b. test cmp must test r1 (the AND result register), not r0
rep("\tand\tr1, r1, r0\n\tcmp\tr0, #0", "\tand\tr1, r1, r0\n\tcmp\tr1, #0")
# 4. delete the extra ORR-0 pair in the |= block (-4 B, exactly the size gap)
rep("\tmov\tr1, #0\n\torr\tr0, r0, r1\n", "")
# 5. |= block load order: constant first, then f7 (ROM order)
rep("\tldrb\tr0, [r4, #7]\n\tmov\tr1, #1\n\torr\tr0, r0, r1",
    "\tmov\tr0, #1\n\tldrb\tr1, [r4, #7]\n\torr\tr0, r0, r1")
open(sys.argv[1], "w").write(s)
print("patch ok")
