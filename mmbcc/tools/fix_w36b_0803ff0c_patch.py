import sys
s = open(sys.argv[1]).read()
def rep(old, new):
    global s
    assert s.count(old) == 1, f"expected 1 occurrence of {old!r}, got {s.count(old)}"
    s = s.replace(old, new)
# Prologue: a2 copy first, then b/b2/c truncations (reorder, same length).
rep("\tlsl\tr1, r1, #24\n\tlsl\tr2, r2, #24\n\tmov\tr8, r4\n\tlsr\tr5, r1, #24\n\tadd\tr7, r5, #0\n\tlsr\tr2, r2, #24\n\tmov\tr9, r2",
    "\tmov\tr8, r4\n\tlsl\tr1, r1, #24\n\tlsr\tr5, r1, #24\n\tadd\tr7, r5, #0\n\tlsl\tr2, r2, #24\n\tlsr\tr2, r2, #24\n\tmov\tr9, r2")
# Return: move, not truncation (net -2 B, exactly the size gap).
rep("\tlsl\tr0, r6, #24\n\tlsr\tr0, r0, #24",
    "\tadd\tr0, r6, #0")
open(sys.argv[1], "w").write(s)
print("patch ok")
