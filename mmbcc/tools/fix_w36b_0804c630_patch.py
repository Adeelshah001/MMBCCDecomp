import sys
s = open(sys.argv[1]).read()
# First do the r5<->r6 swap.
s = s.replace("r5", "rX")
s = s.replace("r6", "r5")
s = s.replace("rX", "r6")
# Then fix the count setup: truncate in r0, check r0, move to r6 after table load.
def rep(old, new):
    global s
    assert s.count(old) == 1, f"expected 1 occurrence of {old!r}, got {s.count(old)}"
    s = s.replace(old, new)
rep("\tlsr\tr6, r0, #16\n\tcmp\tr6, #0\n\tbeq\t.L2\t@cond_branch\n\tldr\tr5, .L9+28",
    "\tlsr\tr0, r0, #16\n\tcmp\tr0, #0\n\tbeq\t.L2\t@cond_branch\n\tldr\tr5, .L9+28\n\tadd\tr6, r0, #0")
open(sys.argv[1], "w").write(s)
print("patch ok")
