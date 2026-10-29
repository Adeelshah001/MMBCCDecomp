#!/usr/bin/env python3
"""Apply the W39-C 0x0801a72c single-opcode patch to a generated .s file.
Usage: w39c_0801a72c_patch.py IN.s OUT.s
Replaces the FIRST `bhi` (the mode>1 dispatch branch, after the second
`cmp r0, #1`) with `bgt`. The file's second `bhi` (a different comparison
that already matches ROM) is left untouched, so the replacement must be
first-occurrence only, asserted by the surrounding cmp sequence.
"""
import sys


def main(inp, outp):
    lines = open(inp).readlines()
    # Find dispatch sequence: cmp r0,#1 / beq? / cmp r0,#1 / bhi .L6
    idx = None
    for i in range(len(lines) - 3):
        if (lines[i].strip() == "cmp\tr0, #1"
                and lines[i + 2].strip() == "cmp\tr0, #1"
                and lines[i + 3].strip().startswith("bhi\t")):
            assert idx is None, "dispatch pattern occurs more than once"
            idx = i + 3
    assert idx is not None, "dispatch bhi pattern not found"
    lines[idx] = lines[idx].replace("bhi\t", "bgt\t", 1)
    open(outp, "w").writelines(lines)


if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2])
