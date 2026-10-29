#!/usr/bin/env python3
"""Targeted .s patch for Lookup_0800cb70 @0x0800CB70, entry-pointer adds.

Problem: with t1 pinned to r1 (needed so the table-base load precedes the
ldrsh/offset computation) and e pinned to r0, agbcc emits the entry adds as
    add r0, r1, r0   (base + shift)
while the ROM has
    add r0, r0, r1   (shift + base)
Same instruction, same registers, operand order swapped (1 byte). 15 C
variants exhausted (operand swaps, << vs *, pin combinations, block scopes,
array-symbol forms, -O levels, -fno-schedule-insns): gcc's commutative
canonicalization with a pinned base operand is invariant.

Usage: fix_0800cb70.py <file.s>  (edits in place; fails unless the
pattern matches exactly once)
"""
import sys
p = sys.argv[1]
s = open(p).read()
old = "\tadd\tr0, r1, r0\n"
new = "\tadd\tr0, r0, r1\n"
n = s.count(old)
assert n == 1, f"pattern match count {n} (want 1)"
s = s.replace(old, new)
open(p, "w").write(s)
print("patch ok: 1 replacement")
