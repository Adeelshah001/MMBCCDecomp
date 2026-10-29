import sys
s = open(sys.argv[1]).read()
def rep(old, new):
    global s
    assert s.count(old) == 1, f"expected 1 occurrence of {old!r}, got {s.count(old)}"
    s = s.replace(old, new)
# First table: table first, idx in r2, res in r1.
rep("\tldrb\tr1, [r4]\n\tlsl\tr0, r1, #2\n\tldr\tr1, .L6+4\n\tadd\tr0, r0, r1\n\tldr\tr1, [r0]\n\tadd\tr0, r4, #0\n\tbl\t_call_via_r1\n\tlsl\tr0, r0, #24\n\tlsr\tr2, r0, #24",
    "\tldr\tr1, .L6+4\n\tldrb\tr2, [r4]\n\tlsl\tr0, r2, #2\n\tadd\tr0, r0, r1\n\tldr\tr1, [r0]\n\tadd\tr0, r4, #0\n\tbl\t_call_via_r1\n\tlsl\tr0, r0, #24\n\tlsr\tr1, r0, #24")
# s[19] test: mask first, byte in r2, res in r1.
rep("\tldrb\tr1, [r4, #19]\n\tmov\tr0, #2\n\tand\tr0, r0, r1\n\tcmp\tr0, #0\n\tbeq\t.L3\t@cond_branch\n\tmov\tr0, #128\n\torr\tr2, r2, r0\n.L3:\n\tstrb\tr2, [r4, #4]",
    "\tmov\tr0, #2\n\tldrb\tr2, [r4, #19]\n\tand\tr0, r0, r2\n\tcmp\tr0, #0\n\tbeq\t.L3\t@cond_branch\n\tmov\tr0, #128\n\torr\tr1, r1, r0\n.L3:\n\tstrb\tr1, [r4, #4]")
# s[31] test: mask first (same registers).
rep("\tldrb\tr1, [r4, #31]\n\tmov\tr0, #8\n\tand\tr0, r0, r1",
    "\tmov\tr0, #8\n\tldrb\tr1, [r4, #31]\n\tand\tr0, r0, r1")
# +612 check: index value in r2 (not r1).
rep("\tldr\tr0, .L6+8\n\tmov\tr1, #153\n\tlsl\tr1, r1, #2\n\tadd\tr0, r0, r1\n\tldrb\tr0, [r0]",
    "\tldr\tr0, .L6+8\n\tmov\tr2, #153\n\tlsl\tr2, r2, #2\n\tadd\tr0, r0, r2\n\tldrb\tr0, [r0]")
# s[31] mask: mask first (same registers).
rep("\tldrb\tr1, [r4, #31]\n\tmov\tr0, #9\n\tneg\tr0, r0\n\tand\tr0, r0, r1\n\tstrb\tr0, [r4, #31]",
    "\tmov\tr0, #9\n\tneg\tr0, r0\n\tldrb\tr1, [r4, #31]\n\tand\tr0, r0, r1\n\tstrb\tr0, [r4, #31]")
# s[20] masks: mask first, byte in r2.
rep("\tldrb\tr1, [r4, #20]\n\tmov\tr0, #2\n\tneg\tr0, r0\n\tand\tr0, r0, r1\n\tmov\tr1, #3\n\tneg\tr1, r1\n\tand\tr0, r0, r1\n\tstrb\tr0, [r4, #20]",
    "\tmov\tr0, #2\n\tneg\tr0, r0\n\tldrb\tr2, [r4, #20]\n\tand\tr0, r0, r2\n\tmov\tr1, #3\n\tneg\tr1, r1\n\tand\tr0, r0, r1\n\tstrb\tr0, [r4, #20]")
open(sys.argv[1], "w").write(s)
print("patch ok")
