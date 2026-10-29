#!/usr/bin/env python3
"""Wave 47 landing: .s patch for w47d_0804472c (0x0804472c, 252 B).

Coordinator-SANCTIONED instruction-order-swap + register-field patch
(Wave 47, same classes as the Wave 43 0x0803ff80 / Wave 45 0x0801a89c
order-swaps and the Wave 42 register-field sanction). Worker's raw C
(old_agbcc) builds 252 B with exactly 5 differing bytes at one site
(+106..+110, mode-1 table load); C-only steering was exhausted
(old -Os/-O3/-fno-regmove same 5, -O1 260 B, main 224 B).
The swap exchanges the adjacent ldr and lsrs (disjoint footprints:
ldr writes only the base register, lsrs writes only r0, neither
touches memory, ldr address is PC-relative) and renames the base
register r2 -> r1 (dead after the adds: the next use in either
version is a movs #0 overwrite before any read; the intervening ldr
reads r0 only). The pool word is unchanged (both ldrs target the
same pool address). Semantically identical; patched build is 0-diff.
"""
import sys
inp, outp = sys.argv[1], sys.argv[2]
text = open(inp).read()
old = "\tlsr\tr0, r0, #22\n\tldr\tr2, .L21\n\tadd\tr0, r0, r2\n"
new = "\tldr\tr1, .L21\n\tlsr\tr0, r0, #22\n\tadd\tr0, r0, r1\n"
assert text.count(old) == 1, f"OLD block count != 1: {text.count(old)}"
assert new not in text, "NEW block already present (double-patch?)"
open(outp, "w").write(text.replace(old, new))
print("patched: 1 swap+rename applied")
