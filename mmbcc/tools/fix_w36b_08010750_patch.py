import sys
s = open(sys.argv[1]).read()
def rep(old, new):
    global s
    assert s.count(old) == 1, f"expected 1 occurrence of {old!r}, got {s.count(old)}"
    s = s.replace(old, new)
# Bit computation: 3 in r3 (for later stack1=3 store).
rep("\tldr\tr2, .L6\n\tmov\tr0, #3\n\tsub\tr0, r0, r1\n\tldr\tr2, [r2]\n\tlsr\tr2, r2, r0\n\tmov\tr0, #1\n\tand\tr2, r2, r0",
    "\tldr\tr2, .L6\n\tmov\tr3, #3\n\tsub\tr0, r3, r1\n\tldr\tr2, [r2]\n\tlsr\tr2, r2, r0\n\tmov\tr0, #1\n\tand\tr2, r2, r0")
# Stack stores interleaved + middle pool split (table/s move to end pool .L8).
rep("\tmov\tr3, #5\n\tcmp\tr1, #0\n\tbeq\t.L4\t@cond_branch\n\tmov\tr3, #3\n.L4:\n\tlsl\tr0, r2, #2\n\tldr\tr1, .L6+4\n\tadd\tr0, r0, r1\n\tldr\tr1, [r0]\n\tldr\tr0, .L6+8\n\tstr\tr0, [sp]\n\tstr\tr3, [sp, #4]\n\tstr\tr1, [sp, #8]",
    "\tldr\tr0, .L6+4\n\tstr\tr0, [sp]\n\tcmp\tr1, #0\n\tbeq\t.L5\t@cond_branch\n\tstr\tr3, [sp, #4]\n\tb\t.L4\t@cond_branch\n.L6:\n\t.word\t33568368\n\t.word\t525\n.L5:\n\tmov\tr0, #5\n\tstr\tr0, [sp, #4]\n.L4:\n\tldr\tr1, .L8\n\tlsl\tr0, r2, #2\n\tadd\tr0, r0, r1\n\tldr\tr0, [r0]\n\tstr\tr0, [sp, #8]")
# s load after the call now references the end pool.
rep("\tbl\tSub_080062B4\n\tldr\tr4, .L6+12",
    "\tbl\tSub_080062B4\n\tldr\tr4, .L8+4")
# End pool: table + s only.
rep("\t.align\t2, 0\n.L6:\n\t.word\t33568368\n\t.word\t135740972\n\t.word\t525\n\t.word\t33575272\n",
    "\t.align\t2, 0\n.L8:\n\t.word\t135740972\n\t.word\t33575272\n")
open(sys.argv[1], "w").write(s)
print("patch ok")
