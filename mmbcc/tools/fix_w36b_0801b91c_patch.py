import sys
s = open(sys.argv[1]).read()
def rep(old, new):
    global s
    assert s.count(old) == 1, f"expected 1 occurrence of {old!r}, got {s.count(old)}"
    s = s.replace(old, new)
# Table 1: base first, index into r2
rep("\tldrb\tr1, [r5, #16]\n\tlsl\tr0, r1, #2\n\tldr\tr1, .L4\n\tadd\tr0, r0, r1",
    "\tldr\tr1, .L4\n\tldrb\tr2, [r5, #16]\n\tlsl\tr0, r2, #2\n\tadd\tr0, r0, r1")
# Table 2: base first, index into r2
rep("\tldrb\tr1, [r5, #9]\n\tlsl\tr0, r1, #2\n\tldr\tr1, .L4+4\n\tadd\tr0, r0, r1",
    "\tldr\tr1, .L4+4\n\tldrb\tr2, [r5, #9]\n\tlsl\tr0, r2, #2\n\tadd\tr0, r0, r1")
open(sys.argv[1], "w").write(s)
print("patch ok")
