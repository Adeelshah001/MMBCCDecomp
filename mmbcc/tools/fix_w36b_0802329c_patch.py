#!/usr/bin/env python3
"""Wave 36-B .s post-process for 0x0802329c.

agbcc keeps the flag variable in callee-saved r4 for the second branch
(push {r4, lr}, add r4, r3, #0, strb r4 in branch 1, pop {r4});
the ROM keeps it in r3 throughout (push {lr} only, strb r3 in both
branches, single pop {r0}). The patch removes the allocator's r4 copy:
  1. push {r4, lr} -> push {lr}
  2. delete the 'add r4, r3, #0' line
  3. strb r4 -> strb r3 (exactly 2 occurrences, branch 1 stores)
  4. delete the 'pop {r4}' line
Net -4 bytes (108 -> 104 B), matching the ROM extent exactly.
Each pattern must match the asserted count; the script fails otherwise.
"""
import sys

p = sys.argv[1]
s = open(p).read()

old = "\tpush\t{r4, lr}"
assert s.count(old) == 1, "push pattern"
s = s.replace(old, "\tpush\t{lr}")

old = "\tadd\tr4, r3, #0\n"
assert s.count(old) == 1, "r4 copy pattern"
s = s.replace(old, "")

old = "\tstrb\tr4, [r1, #15]"
assert s.count(old) == 1, "strb r4 #15 pattern"
s = s.replace(old, "\tstrb\tr3, [r1, #15]")
old = "\tstrb\tr4, [r1, #14]"
assert s.count(old) == 1, "strb r4 #14 pattern"
s = s.replace(old, "\tstrb\tr3, [r1, #14]")

old = "\tpop\t{r4}\n"
assert s.count(old) == 1, "pop r4 pattern"
s = s.replace(old, "")

open(p, "w").write(s)
print("patch ok: 5 replacements")
