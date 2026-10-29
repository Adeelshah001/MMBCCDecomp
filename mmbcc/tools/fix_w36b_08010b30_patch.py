import sys
s = open(sys.argv[1]).read()
def rep(old, new):
    global s
    assert s.count(old) == 1, f"expected 1 occurrence of {old!r}, got {s.count(old)}"
    s = s.replace(old, new)
# 1. flag test: constant first, then flag load (ROM order)
rep("\tldrb\tr1, [r5, #15]\n\tmov\tr0, #1",
    "\tmov\tr0, #1\n\tldrb\tr1, [r5, #15]")
# 2. else-path: table load first, index into r2
rep("\tbl\tSub_08004F18\n\tldrb\tr0, [r5, #4]\n\tlsl\tr0, r0, #2\n\tldr\tr1, .L6+4\n\tadd\tr0, r0, r1",
    "\tbl\tSub_08004F18\n\tldr\tr1, .L6+4\n\tldrb\tr2, [r5, #4]\n\tlsl\tr0, r2, #2\n\tadd\tr0, r0, r1")
# 3. flag-path: index into r2 (not r0)
rep("\tldr\tr1, .L8\n\tldrb\tr0, [r5, #4]\n\tlsl\tr0, r0, #2",
    "\tldr\tr1, .L8\n\tldrb\tr2, [r5, #4]\n\tlsl\tr0, r2, #2")
open(sys.argv[1], "w").write(s)
print("patch ok")
