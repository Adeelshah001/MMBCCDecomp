import sys
s = open(sys.argv[1]).read()
def rep(old, new):
    global s
    assert s.count(old) == 1, f"expected 1 occurrence of {old!r}, got {s.count(old)}"
    s = s.replace(old, new)
# 1. first table: table first, struct second, index into r2; pool words swap
rep("\tldr\tr4, .L10\n\tldrb\tr1, [r4]\n\tlsl\tr0, r1, #2\n\tldr\tr1, .L10+4\n\tadd\tr0, r0, r1",
    "\tldr\tr1, .L10\n\tldr\tr4, .L10+4\n\tldrb\tr2, [r4]\n\tlsl\tr0, r2, #2\n\tadd\tr0, r0, r1")
rep("\t.word\t33601552\n\t.word\t136502788",
    "\t.word\t136502788\n\t.word\t33601552")
# 2. flag test: constant first, then flag load
rep("\tldrb\tr1, [r4, #6]\n\tmov\tr0, #8",
    "\tmov\tr0, #8\n\tldrb\tr1, [r4, #6]")
# 3. end block: byte into r2 (not r1)
rep("\tldr\tr0, .L12\n\tldrb\tr1, [r0, #4]\n\tlsr\tr5, r1, #4",
    "\tldr\tr0, .L12\n\tldrb\tr2, [r0, #4]\n\tlsr\tr5, r2, #4")
open(sys.argv[1], "w").write(s)
print("patch ok")
