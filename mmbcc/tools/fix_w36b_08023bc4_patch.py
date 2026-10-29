import sys
s = open(sys.argv[1]).read()
def rep(old, new):
    global s
    assert s.count(old) == 1, f"expected 1 occurrence of {old!r}, got {s.count(old)}"
    s = s.replace(old, new)
# Second part: pointer in r0 (in place), shift amount in r1; net -2 B.
rep("\tmov\tr2, r9\n\tadd\tr1, r2, r0\n\tmov\tr0, #8\n\tmov\tr2, r8\n\tsub\tr0, r0, r2\n\tldrb\tr1, [r1]\n\tasr\tr1, r1, r0\n\tadd\tr0, r1, #0\n\torr\tr4, r4, r0",
    "\tadd\tr0, r9\n\tmov\tr1, #8\n\tmov\tr2, r8\n\tsub\tr1, r1, r2\n\tldrb\tr0, [r0]\n\tasr\tr0, r0, r1\n\tadd\tr1, r0, #0\n\torr\tr4, r4, r1")
open(sys.argv[1], "w").write(s)
print("patch ok")
