import sys
p = sys.argv[1]
s = open(p).read()
old_mov = "\tmov\tr0, #0\n\tmov\tr1, #0\n"
new_mov = "\tmov\tr1, #0\n\tmov\tr0, #0\n"
assert old_mov in s, "mov pair not found"
s = s.replace(old_mov, new_mov, 1)
old_pool = "\tldr\tr3, .L3\n\tadd\tr0, r3, #0\n"
new_pool = "\tldr\tr0, .L3\n"
assert old_pool in s, "pool pair not found"
s = s.replace(old_pool, new_pool, 1)
open(p, "w").write(s)
