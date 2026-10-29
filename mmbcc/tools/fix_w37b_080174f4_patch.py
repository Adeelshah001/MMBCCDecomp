import sys
p = sys.argv[1]
s = open(p).read()
old = "\tadd\tr1, r1, r0\n\tmov\tr0, #1\n\tstr\tr0, [r5, #12]\n\tldr\tr0, [r1]\n"
new = "\tadd\tr0, r0, r1\n\tmov\tr1, #1\n\tstr\tr1, [r5, #12]\n\tldr\tr0, [r0]\n"
assert old in s, "entry/one sequence not found"
s = s.replace(old, new, 1)
old2 = "\torr\tr0, r0, r3\n\tmov\tr1, #1\n\torr\tr0, r0, r1\n"
new2 = "\torr\tr0, r0, r3\n\torr\tr0, r0, r1\n"
assert old2 in s, "s10 reload sequence not found"
s = s.replace(old2, new2, 1)
open(p, "w").write(s)
