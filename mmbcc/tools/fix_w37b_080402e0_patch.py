import sys
p = sys.argv[1]
s = open(p).read()
old1 = "\tldr\tr2, .L9+4\n\t.code\t16\n\tldr\tr0, .L9+8\n\tadd\tr2, r2, r0\n"
new1 = "\tldr\tr0, .L9+4\n\t.code\t16\n\tldr\tr3, .L9+8\n\tadd\tr2, r0, r3\n"
assert old1 in s, "initial base sequence not found"
s = s.replace(old1, new1, 1)
old2 = "\tldrb\tr2, [r0]\n\tadd\tr1, r2, r5\n"
new2 = "\tldrb\tr3, [r0]\n\tadd\tr1, r3, r5\n"
assert old2 in s, "final store sequence not found"
s = s.replace(old2, new2, 1)
open(p, "w").write(s)
