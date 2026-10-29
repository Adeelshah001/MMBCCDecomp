import sys
p = sys.argv[1]
s = open(p).read()
reps = [
    ("\tadd\tr2, r2, r1\n", "\tadd\tr1, r1, r2\n"),
    ("\tmov\tr1, #4\n\tstr\tr1, [r0, #12]\n\tldr\tr1, [r2]\n",
     "\tmov\tr2, #4\n\tstr\tr2, [r0, #12]\n\tldr\tr1, [r1]\n"),
]
for old, new in reps:
    assert old in s, "not found: " + repr(old)
    s = s.replace(old, new, 1)
open(p, "w").write(s)
