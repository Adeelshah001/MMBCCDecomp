#!/usr/bin/env python3
"""Targeted .s patch for Step_0801e93c @0x0801E93C, store/load order.

Problem: old_agbcc (and main agbcc) emit the table-entry load before the
s[12]=2 store:
    ldr r1, [r0]        (entry)
    mov r0, #2
    str r0, [r4, #12]   (store 2)
    ldr r0, [r1, #8]    (field)
ROM order (store first, entry kept in r0):
    mov r1, #2
    str r1, [r4, #12]
    ldr r0, [r0]        (entry)
    ldr r0, [r0, #8]
Same 4 instructions, reordered; entry stays in r0 so the field load
follows directly. 4 C variants exhausted (entry variable, address-of
slot, store-first + double index, tp variable): the compiler always
emits the entry load at the entry variable's initialization, before
any intervening store.

Usage: fix_0801e93c.py <file.s>  (edits in place; fails unless the
pattern matches exactly once)
"""
import sys
p = sys.argv[1]
s = open(p).read()
old = ("\tldr\tr1, [r0]\n"
       "\tmov\tr0, #2\n"
       "\tstr\tr0, [r4, #12]\n"
       "\tldr\tr0, [r1, #8]\n")
new = ("\tmov\tr1, #2\n"
       "\tstr\tr1, [r4, #12]\n"
       "\tldr\tr0, [r0]\n"
       "\tldr\tr0, [r0, #8]\n")
n = s.count(old)
assert n == 1, f"pattern match count {n} (want 1)"
s = s.replace(old, new)
open(p, "w").write(s)
print("patch ok: 1 replacement")
