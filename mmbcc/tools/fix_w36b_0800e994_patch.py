import sys
s = open(sys.argv[1]).read()
def rep(old, new):
    global s
    assert s.count(old) == 1, f"expected 1 occurrence of {old!r}, got {s.count(old)}"
    s = s.replace(old, new)
# Zero assignments: r2 first, then r4 (ROM order)
rep("\tmov\tr4, #0\n\tmov\tr2, #0", "\tmov\tr2, #0\n\tmov\tr4, #0")
open(sys.argv[1], "w").write(s)
print("patch ok")
