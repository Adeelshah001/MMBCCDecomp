#!/usr/bin/env python3
"""Targeted .s patch for Sub_08017B6C @0x08017b6c (W40-C, old_agbcc base).

Why: 7 C variants (v1-v7, both compilers) converge to the same remaining
walls, all register-allocation / scheduling differences in gcc 2.9-arm,
invariant across source order, operator form, and compiler version.
(v7 also corrects a semantic misread the patched diff exposed: ROM's
beq after each compare skips the bitfield block too, so the bitfield
lives INSIDE the if body in both cases, not after it.)
  P1 entry: allocator puts the s[16] byte in r1 and the shift result in
     r0; ROM has byte in r0, shift in r1, pool in r0.
  P2/P4 compares + Setup calls: allocator loads the RHS of the != first
     and materializes 768 straight into r0; ROM loads LHS first (r1),
     RHS into r2, and materializes 768 via r3 + copy to r0.
  P3/P5 bitfield s[69] field-insert: allocator computes the -13 mask
     early into r2 and shifts in place (r1); ROM computes the mask late
     into r1 with the shift result in r0. (The clamp itself and the
     movs#13+negs mask already match in C via the int-t / barrier-v
     forms; only the register assignment and position differ.)
  P6 case3 table block: scheduler loads the pool after the index shift;
     ROM loads the pool first.
All replacements preserve or (Setup: +1 instruction each) extend the
instruction stream; branch targets and pools are labels, so the
assembler recomputes offsets and GAS's `.align 2, 0` re-inserts the two
ROM alignment pads. Verified end-to-end: patched .s assembles to a
0-diff 372-byte image over the true extent (see w40c_build_patched.py).

Usage: w40c_08017b6c_patch.py IN.s OUT.s  (fails unless every block
matches its asserted count)
"""
import sys


def rep(text, old, new, count, name):
    n = text.count(old)
    assert n == count, f"{name}: matches {n} times, expected {count}"
    return text.replace(old, new)


def main(inp, outp):
    text = open(inp).read()

    # P1: entry register allocation.
    text = rep(text,
        "\tldrb\tr1, [r4, #16]\n"
        "\tlsl\tr0, r1, #4\n"
        "\tldr\tr1, .L20\n"
        "\tadd\tr5, r0, r1\n",
        "\tldrb\tr0, [r4, #16]\n"
        "\tlsl\tr1, r0, #4\n"
        "\tldr\tr0, .L20\n"
        "\tadd\tr5, r1, r0\n", 1, "P1 entry")

    # P2: case0 compare + Setup (beq target .L6 = bitfield block).
    text = rep(text,
        "\tldrb\tr0, [r5, #6]\n"
        "\tldrb\tr1, [r5]\n"
        "\tcmp\tr1, r0\n"
        "\tbeq\t.L6\t@cond_branch\n"
        "\tmov\tr0, #192\n"
        "\tlsl\tr0, r0, #2\n"
        "\tldrb\tr1, [r5, #1]\n"
        "\torr\tr1, r1, r0\n",
        "\tldrb\tr1, [r5]\n"
        "\tldrb\tr2, [r5, #6]\n"
        "\tcmp\tr1, r2\n"
        "\tbeq\t.L6\t@cond_branch\n"
        "\tmov\tr3, #192\n"
        "\tlsl\tr3, r3, #2\n"
        "\tadd\tr0, r3, #0\n"
        "\tldrb\tr1, [r5, #1]\n"
        "\torr\tr1, r1, r0\n", 1, "P2 case0 setup")

    # P4: case2 compare + Setup (beq target .L12 = bitfield block).
    text = rep(text,
        "\tldrb\tr1, [r5, #6]\n"
        "\tldrb\tr0, [r5, #7]\n"
        "\tcmp\tr1, r0\n"
        "\tbeq\t.L12\t@cond_branch\n"
        "\tmov\tr0, #192\n"
        "\tlsl\tr0, r0, #2\n"
        "\tldrb\tr1, [r5, #1]\n"
        "\torr\tr1, r1, r0\n",
        "\tldrb\tr0, [r5, #6]\n"
        "\tldrb\tr1, [r5, #7]\n"
        "\tcmp\tr0, r1\n"
        "\tbeq\t.L12\t@cond_branch\n"
        "\tmov\tr2, #192\n"
        "\tlsl\tr2, r2, #2\n"
        "\tadd\tr0, r2, #0\n"
        "\tldrb\tr1, [r5, #1]\n"
        "\torr\tr1, r1, r0\n", 1, "P4 case2 setup")

    # P3/P5a: drop the early -13 mask computation (both bitfields).
    text = rep(text,
        "\tand\tr1, r1, r0\n"
        "\tmov\tr2, #13\n"
        "\tneg\tr2, r2\n"
        "\tadd\tr0, r1, #0\n",
        "\tand\tr1, r1, r0\n"
        "\tadd\tr0, r1, #0\n", 2, "P3 early mask")

    # P3/P5b: s[69] field-insert segment, late mask into r1 (both blocks).
    text = rep(text,
        "\tadd\tr3, r4, #0\n"
        "\tadd\tr3, r3, #69\n"
        "\tlsl\tr0, r1, #2\n"
        "\tldrb\tr1, [r3]\n"
        "\tand\tr2, r2, r1\n"
        "\torr\tr0, r0, r2\n"
        "\tstrb\tr0, [r3]\n",
        "\tadd\tr2, r4, #0\n"
        "\tadd\tr2, r2, #69\n"
        "\tlsl\tr0, r1, #2\n"
        "\tmov\tr1, #13\n"
        "\tneg\tr1, r1\n"
        "\tldrb\tr3, [r2]\n"
        "\tand\tr1, r1, r3\n"
        "\torr\tr1, r1, r0\n"
        "\tstrb\tr1, [r2]\n", 2, "P3 s69 segment")

    # P6: case3 table block, pool load first.
    text = rep(text,
        "\tldrb\tr1, [r4, #9]\n"
        "\tlsl\tr0, r1, #2\n"
        "\tldr\tr1, .L26\n"
        "\tadd\tr0, r0, r1\n",
        "\tldr\tr1, .L26\n"
        "\tldrb\tr2, [r4, #9]\n"
        "\tlsl\tr0, r2, #2\n"
        "\tadd\tr0, r0, r1\n", 1, "P6 case3 tbl")

    open(outp, "w").write(text)
    print("w40c_08017b6c_patch: P1,P2,P4,P3x2,P6 applied")


if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2])
