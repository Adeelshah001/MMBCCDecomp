#!/usr/bin/env python3
"""Apply the W38-C 0x0800e144 patches to a generated .s file.
Usage: w38c_0800e144_patch.py IN.s OUT.s (asserted occurrence counts)
"""
import sys

def main(inp, outp):
    lines = open(inp).readlines()
    out = []
    n_sum = n_move = n_ldr = n_and = 0
    for ln in lines:
        if ln == "\tadd\tr4, r2, r0\n":
            out.append("\tadd\tr0, r2, r0\n")
            n_sum += 1
        elif ln == "\tadd\tr0, r4, #0\n":
            n_move += 1  # deleted
        elif ln == "\tldr\tr0, .L7\n":
            out.append("\tldr\tr2, .L7\n")
            n_ldr += 1
        elif ln == "\tand\tr1, r1, r0\n":
            out.append("\tand\tr1, r1, r2\n")
            n_and += 1
        else:
            out.append(ln)
    assert (n_sum, n_move, n_ldr, n_and) == (2, 2, 1, 1), \
        (n_sum, n_move, n_ldr, n_and)
    open(outp, "w").writelines(out)

if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2])
