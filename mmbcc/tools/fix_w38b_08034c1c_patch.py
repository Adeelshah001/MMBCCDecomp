"""W38-B .s patch for 34c1c (v6, old_agbcc, 132 B, 16 diffs).
Fixes v6's register allocation to ROM's (all same-length renames):
1. Prologue base r7 -> r6 (v6 put base in r7, clobbered by tblA load).
2. Loop-head add: r7, r0 -> r0, r6 (base rename + operand order).
3. Loop-body v/dst swap: v r0 -> r1, dst r1 -> r0 (both branches).
4. Tail p r6 -> r1 (2 ldrs, 2 strbs).
Exact agbcc .s text (tabs, pre-UAL spellings).
"""
import sys

p = sys.argv[1]
s = open(p).read()

def rep(old, new, count=1):
    global s
    assert old in s, "NOT FOUND: %r" % old
    s = s.replace(old, new, count)

# 1. prologue base
rep("\tadd\tr7, r0, r1\n\tmov\tr4, #3\n",
    "\tadd\tr6, r0, r1\n\tmov\tr4, #3\n")
# 2. loop-head ep add (rename + operand order)
rep("\tadd\tr0, r7, r0\n",
    "\tadd\tr0, r0, r6\n")
# 3a. call-result trunc dest
rep("\tlsl\tr0, r0, #24\n\tlsr\tr0, r0, #24\n",
    "\tlsl\tr0, r0, #24\n\tlsr\tr1, r0, #24\n")
# 3b. then-branch (sub/cmp/add) + else-branch (sub/cmp/add)
rep("\tsub\tr1, r4, #3\n\tcmp\tr1, #255\n\tbeq\t.L10\t@cond_branch\n\tadd\tr1, r7, r1\n",
    "\tsub\tr0, r4, #3\n\tcmp\tr0, #255\n\tbeq\t.L10\t@cond_branch\n\tadd\tr0, r0, r7\n")
rep("\tsub\tr1, r4, #3\n\tcmp\tr1, #255\n\tbeq\t.L10\t@cond_branch\n\tadd\tr1, r1, r8\n",
    "\tsub\tr0, r4, #3\n\tcmp\tr0, #255\n\tbeq\t.L10\t@cond_branch\n\tadd\tr0, r0, r8\n")
# 3c. store
rep("\tstrb\tr0, [r1]\n",
    "\tstrb\tr1, [r0]\n")
# 4. tail p r6 -> r1
rep("\tldr\tr6, .L20\n", "\tldr\tr1, .L20\n")
rep("\tldr\tr6, .L22\n", "\tldr\tr1, .L22\n")
rep("\tstrb\tr0, [r6, #5]\n", "\tstrb\tr0, [r1, #5]\n")
rep("\tstrb\tr0, [r6, #6]\n", "\tstrb\tr0, [r1, #6]\n")

open(p, "w").write(s)
print("34c1c patch applied")
