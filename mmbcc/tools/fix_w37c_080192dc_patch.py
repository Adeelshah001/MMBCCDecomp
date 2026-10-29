import sys
p = sys.argv[1]
s = open(p).read()
old = '\tldrb\tr0, [r4, #13]\n\tadd\tr5, r0, #0\n\tcmp\tr0, #0\n\tbeq\t.L4\t@cond_branch\n\tcmp\tr0, #1\n'
new = '\tldrb\tr5, [r4, #13]\n\tcmp\tr5, #0\n\tbeq\t.L4\t@cond_branch\n\tcmp\tr5, #1\n'
assert s.count(old) == 1, 'patch old-block count != 1'
open(p, 'w').write(s.replace(old, new, 1))
