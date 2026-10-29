import sys
s = open(sys.argv[1]).read()
def rep(old, new):
    global s
    assert s.count(old) == 1, f"expected 1 occurrence of {old!r}, got {s.count(old)}"
    s = s.replace(old, new)
# Slot address: offset + struct (ROM order), not struct + offset
rep("\tadd\tr4, r5, r0", "\tadd\tr4, r0, r5")
open(sys.argv[1], "w").write(s)
print("patch ok")
