#!/usr/bin/env python3
"""Wave 24-B: applies the .s patch for w24b_08026184.c (main agbcc output).
Fuses the 0x8000 materialization:
    mov r2, #128 / lsl r2, r2, #8 / add r0, r2, #0 / strh r0, [r1, #22]
  ->
    mov r0, #128 / lsl r0, r0, #8 / strh r0, [r1, #22]
Byte-neutral register-rename; fixes the allocation for 0x08026184.
Usage: python3 tools/patch_w24b_26184.py <file.s>
"""
import sys

p = sys.argv[1]
s = open(p).read()
old = ("\tmov\tr2, #128\n"
       "\tlsl\tr2, r2, #8\n"
       "\tadd\tr0, r2, #0\n"
       "\tstrh\tr0, [r1, #22]\n")
new = ("\tmov\tr0, #128\n"
       "\tlsl\tr0, r0, #8\n"
       "\tstrh\tr0, [r1, #22]\n")
assert s.count(old) == 1, f'patch anchor found {s.count(old)}x, expected 1'
open(p, 'w').write(s.replace(old, new))
