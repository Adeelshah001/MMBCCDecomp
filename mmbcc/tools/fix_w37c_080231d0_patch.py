import sys
p = sys.argv[1]
s = open(p).read()
old = '\tmov\tr1, #128\n\tlsl\tr1, r1, #1\n\tadd\tr0, r4, #0\n\tadd\tr0, r0, #76\n'
new = '\tadd\tr0, r4, #0\n\tadd\tr0, r0, #76\n\tmov\tr1, #128\n\tlsl\tr1, r1, #1\n'
assert s.count(old) == 1, 'patch old-block count != 1'
open(p, 'w').write(s.replace(old, new, 1))
