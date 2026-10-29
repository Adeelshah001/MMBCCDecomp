#!/usr/bin/env python3
"""Targeted .s patches for Check_08028970 @0x08028970 (2 spots).

1) Second flags test: agbcc emits `and r1, r1, r0` (result in the
   flags register) + `cmp r1`; ROM has `and r0, r0, r1` + `cmp r0`
   (result in the constant register, flags preserved). The first
   flags test already matches, so this is a compiler allocation
   quirk for the dead-after-use flags register.
2) (s8) call-result test: agbcc canonicalizes the s8 conversion to
   unsigned (`lsr`, `cmp r0`, `beq done`, `b ret0`) because v is
   only used for ==0 and strb; ROM keeps the signed form (`asr`,
   `cmp r1`, `bne ret0`, `b done`). Same instruction count.

Usage: fix_08028970.py <file.s>  (edits in place; fails unless each
pattern matches exactly once)
"""
import sys
p = sys.argv[1]
s = open(p).read()
patches = [
    ("\tmov\tr0, #32\n\tand\tr1, r1, r0\n\tcmp\tr1, #0\n",
     "\tmov\tr0, #32\n\tand\tr0, r0, r1\n\tcmp\tr0, #0\n"),
    ("\tlsl\tr0, r0, #24\n\tlsr\tr1, r0, #24\n\tcmp\tr0, #0\n\tbeq\t.L7\t@cond_branch\n\tb\t.L13\n",
     "\tlsl\tr0, r0, #24\n\tasr\tr1, r0, #24\n\tcmp\tr1, #0\n\tbne\t.L13\t@cond_branch\n\tb\t.L7\n"),
]
for old, new in patches:
    n = s.count(old)
    assert n == 1, f"pattern match count {n} (want 1): {old!r}"
    s = s.replace(old, new)
open(p, "w").write(s)
print("patch ok: 2 replacements")
