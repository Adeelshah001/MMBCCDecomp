#!/usr/bin/env python3
"""Wave 46 landing: .s patch for w46c_08001ae4 (0x08001ae4, 276 B).

Coordinator-SANCTIONED instruction-order-swap patch (Wave 46, same
class as the Wave 43 0x0803ff80 and Wave 45 0x0801a89c sanctions).
Worker C's raw C (old_agbcc) builds 276 B with exactly 4 differing
bytes at one site; C-only steering was exhausted (operand swap,
named-constant form, volatile-u16 form, main -O2, old -Os — all still
load-first, still 4 diffs). The swap exchanges two adjacent
instructions with disjoint register footprints (ldrh writes r1 only,
movs writes r0 only); the load reads ordinary RAM at [r2+6]
(0x02002ee0+6, no side effect); the movs flag result is dead (the
following ands overwrites flags before the cmp); both orders leave
r0=3, r1=*(G+6) at the ands. Semantically identical.
"""
import sys
inp, outp = sys.argv[1], sys.argv[2]
text = open(inp).read()
old = "\tldrh\tr1, [r2, #6]\n\tmov\tr0, #3\n"
new = "\tmov\tr0, #3\n\tldrh\tr1, [r2, #6]\n"
assert text.count(old) == 1, f"OLD pair count != 1: {text.count(old)}"
assert new not in text, "NEW pair already present (double-patch?)"
open(outp, "w").write(text.replace(old, new))
print("patched: 1 swap applied")
