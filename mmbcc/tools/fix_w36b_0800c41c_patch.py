import sys
s = open(sys.argv[1]).read()
def rep(old, new):
    global s
    assert s.count(old) == 1, f"expected 1 occurrence of {old!r}, got {s.count(old)}"
    s = s.replace(old, new)
# Tail reorder: load pool5 (r1) first, then pool6 (r0); sb addr from r0;
# ptr from r1. Net size unchanged (one load moved earlier, one removed later).
rep("\tldr\tr1, .L4+16\n\tadd\tr0, r5, r1\n\tmov\tr2, #0\n\tldrsb\tr2, [r0, r2]\n\tlsl\tr2, r2, #2\n\tldr\tr0, .L4+20\n\tadd\tr2, r2, r0",
    "\tldr\tr1, .L4+16\n\tldr\tr0, .L4+20\n\tadd\tr0, r5, r0\n\tmov\tr2, #0\n\tldrsb\tr2, [r0, r2]\n\tlsl\tr2, r2, #2\n\tadd\tr2, r2, r1")
# Pool word swap: .L4+16 becomes pool5 (0x08173180), .L4+20 becomes pool6 (0x0817313c)
rep("\t.word\t135737660\n\t.word\t135737728",
    "\t.word\t135737728\n\t.word\t135737660")
open(sys.argv[1], "w").write(s)
print("patch ok")
