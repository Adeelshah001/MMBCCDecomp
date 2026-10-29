#!/usr/bin/env python3
"""Wave 36-B .s post-process for 0x08021ed4 (case-1 second table field).

ROM folds the +2 field offset into the base register:
  adds r1, #2; adds r0, r0, r1; movs r1, #0; ldrsh r0, [r0, r1]
agbcc instead keeps the entry address and uses offset register 2:
  add r0, r0, r1; mov r1, #2; ldrsh r0, [r0, r1]
The replacement is net +2 bytes, which exactly fills the alignment pad
(code 98 -> 100 B, pool stays at offset 100, total 104 B).
Pattern must match exactly once; the script asserts this.
"""
import sys

p = sys.argv[1]
s = open(p).read()
old = "\tadd\tr0, r0, r1\n\tmov\tr1, #2\n\tldrsh\tr0, [r0, r1]"
new = "\tadd\tr1, #2\n\tadd\tr0, r0, r1\n\tmov\tr1, #0\n\tldrsh\tr0, [r0, r1]"
n = s.count(old)
assert n == 1, f"pattern match count {n} (want 1)"
s = s.replace(old, new)
open(p, "w").write(s)
print("patch ok: 1 replacement")
