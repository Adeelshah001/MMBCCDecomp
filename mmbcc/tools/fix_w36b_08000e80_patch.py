import sys
s = open(sys.argv[1]).read()
def rep(old, new):
    global s
    assert s.count(old) == 1, f"expected 1 occurrence of {old!r}, got {s.count(old)}"
    s = s.replace(old, new)
# First part: ROM order — base in r3, offset1 in r2, idx*24 before offset2 load.
rep("\tldr\tr2, .L3\n\tldr\tr3, .L3+4\n\tadd\tr1, r2, r3\n\tldr\tr3, [r1]\n\tldr\tr1, .L3+8\n\tadd\tr2, r2, r1\n\tlsl\tr1, r3, #1\n\tadd\tr1, r1, r3\n\tlsl\tr1, r1, #3\n\tadd\tr1, r1, r2",
    "\tldr\tr3, .L3\n\tldr\tr2, .L3+4\n\tadd\tr1, r3, r2\n\tldr\tr2, [r1]\n\tlsl\tr1, r2, #1\n\tadd\tr1, r1, r2\n\tlsl\tr1, r1, #3\n\tldr\tr2, .L3+8\n\tadd\tr3, r3, r2\n\tadd\tr1, r1, r3")
open(sys.argv[1], "w").write(s)
print("patch ok")
