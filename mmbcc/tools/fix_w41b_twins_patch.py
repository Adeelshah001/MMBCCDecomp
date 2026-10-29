#!/usr/bin/env python3
"""Wave 41-B landing wrapper: .s patch for the 0x08003b70 / 0x08003e80 twins.

The C source (w41b_08003b70_r.c, old_agbcc -O2 -mthumb-interwork) builds
328 B with exactly 4 bytes off, all in the prologue: the toolchain's
scheduler interleaves the independent `adds r6, r0, #0` (sp = s) into the
middle of vv's zero-extend chain (lsls/lsrs/mov r8), while the ROM has the
adds first. The two instructions are independent (different registers, no
dependency), so swapping them is semantically neutral.

This script performs ONLY that swap, guarded by an exact-count assert on
the full 4-line prologue block (unique in the file). Usage (Makefile-ready,
same argv convention as tools/fix_*_patch.py):
    python3 w41b_08003b70_patch.py <in.s> <out.s>
"""
import sys

s = open(sys.argv[1]).read()

old = ("\tlsl\tr1, r1, #24\n"
       "\tadd\tr6, r0, #0\n"
       "\tlsr\tr1, r1, #24\n"
       "\tmov\tr8, r1\n")
new = ("\tadd\tr6, r0, #0\n"
       "\tlsl\tr1, r1, #24\n"
       "\tlsr\tr1, r1, #24\n"
       "\tmov\tr8, r1\n")
assert s.count(old) == 1, f"prologue block count={s.count(old)} (expected 1)"
s = s.replace(old, new)
open(sys.argv[2], "w").write(s)
print("w41b prologue swap applied (adds r6 first, then lsls/lsrs/mov r8)")
