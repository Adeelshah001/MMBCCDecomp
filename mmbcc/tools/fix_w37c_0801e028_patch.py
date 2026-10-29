import sys
p = sys.argv[1]
s = open(p).read()
old = '\tldr\tr3, .L4+16\n\tadd\tr0, r0, r3\n'
new = '\tldr\tr1, .L4+16\n\tadd\tr0, r0, r1\n'
assert s.count(old) == 1, 'patch old-block count != 1'
open(p, 'w').write(s.replace(old, new, 1))
