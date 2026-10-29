#!/usr/bin/env python3
"""Targeted .s patch for Sub_0802129C @0x0802129c (W40-C, old_agbcc base).

Single reorder, case2's final Draw call: the barrier that keeps the
0x0817386c pool unfolded (see v3) also hoists its load above the
(s16)cnt argument extension, emitting
    ldr r1, .L30; lsl r0, r5, #16; asr r0, r0, #16; ldrh r1, [r1, #44]
ROM order (same 4 instructions, pool load last):
    lsl r0, r5, #16; asr r0, r0, #16; ldr r1, .L30; ldrh r1, [r1, #44]
The pool is a label, so the assembler recomputes the pc-relative offset
after the move; instruction count and length are unchanged. The other
3 C variants (v1 folded pool, v2 increments, v3 barrier bases) already
match everywhere else; the unbarriered v1 form had this exact order but
folded the pool to 0x08173898 + [r1, #0].

Usage: w40c_0802129c_patch.py IN.s OUT.s  (fails unless the block
matches exactly once)
"""
import sys


def main(inp, outp):
    text = open(inp).read()
    old = ("\tldr\tr1, .L30\n"
           "\t.code\t16\n"
           "\tlsl\tr0, r5, #16\n"
           "\tasr\tr0, r0, #16\n")
    new = ("\tlsl\tr0, r5, #16\n"
           "\tasr\tr0, r0, #16\n"
           "\tldr\tr1, .L30\n"
           "\t.code\t16\n")
    n = text.count(old)
    assert n == 1, f"final-call block matches {n} times, expected 1"
    open(outp, "w").write(text.replace(old, new))
    print("w40c_0802129c_patch: 1 reorder (final-call pool load last)")


if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2])
