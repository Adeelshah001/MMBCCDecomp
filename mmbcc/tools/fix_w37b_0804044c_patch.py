import sys
p = sys.argv[1]
s = open(p).read()
old = "\tldrb\tr0, [r0]\n\tldrb\tr1, [r1]\n\tadd\tr0, r0, r1\n"
new = "\tldrb\tr1, [r1]\n\tldrb\tr0, [r0]\n\tadd\tr0, r1, r0\n"
assert old in s, "sum load sequence not found"
s = s.replace(old, new, 1)
open(p, "w").write(s)
