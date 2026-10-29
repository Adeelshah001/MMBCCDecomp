import sys
s = open(sys.argv[1]).read()
def rep(old, new):
    global s
    assert s.count(old) == 1, f"expected 1 occurrence of {old!r}, got {s.count(old)}"
    s = s.replace(old, new)
# Prologue: base pin before target truncation (reorder, same length).
rep("\tlsl\tr1, r1, #24\n\tmov\tr8, r0\n\tlsr\tr7, r1, #24",
    "\tmov\tr8, r0\n\tlsl\tr1, r1, #24\n\tlsr\tr7, r1, #24")
# Loop: element pointer index + base (operand order, same length).
rep("\tmov\tr1, r8\n\tadd\tr4, r1, r0",
    "\tmov\tr1, r8\n\tadd\tr4, r0, r1")
open(sys.argv[1], "w").write(s)
print("patch ok")
