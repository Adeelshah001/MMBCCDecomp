import sys
p = sys.argv[1]
s = open(p).read()
old = "\tlsl\tr1, r2, #3\n\tldr\tr0, .L7\n\tadd\tr1, r1, r0\n"
new = "\tlsl\tr0, r2, #3\n\tldr\tr1, .L7\n\tadd\tr1, r0, r1\n"
assert old in s, "entry sequence not found"
s = s.replace(old, new, 1)
open(p, "w").write(s)
