import sys
s = open(sys.argv[1]).read()
def rep(old, new):
    global s
    assert s.count(old) == 1, f"expected 1 occurrence of {old!r}, got {s.count(old)}"
    s = s.replace(old, new)
# Clamp: copy x to r0 before comparing (net +2 B).
rep("\tand\tr1, r1, r0\n\tcmp\tr1, #3\n\tble\t.L3\t@cond_branch\n\tmov\tr1, #3",
    "\tand\tr1, r1, r0\n\tadd\tr0, r1, #0\n\tcmp\tr0, #3\n\tble\t.L3\t@cond_branch\n\tmov\tr1, #3")
# s[69]: shift first, mask via negs -13 (net +2 B).
rep("\tadd\tr2, r4, #0\n\tadd\tr2, r2, #69\n\tmov\tr0, #242\n\tldrb\tr3, [r2]\n\tand\tr0, r0, r3\n\tlsl\tr1, r1, #2\n\torr\tr0, r0, r1\n\tstrb\tr0, [r2]",
    "\tadd\tr2, r4, #0\n\tadd\tr2, r2, #69\n\tlsl\tr1, r1, #2\n\tmov\tr0, #13\n\tneg\tr0, r0\n\tldrb\tr3, [r2]\n\tand\tr0, r0, r3\n\torr\tr0, r0, r1\n\tstrb\tr0, [r2]")
open(sys.argv[1], "w").write(s)
print("patch ok")
