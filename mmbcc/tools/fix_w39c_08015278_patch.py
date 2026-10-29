#!/usr/bin/env python3
"""Apply the W39-C 0x08015278 dispatch patch to a generated .s file.
Usage: w39c_08015278_patch.py IN.s OUT.s
Replaces the single `bhi` (mode>1 dispatch) with `bgt`. Asserted to
occur exactly once in this file.
"""
import sys


def main(inp, outp):
    lines = open(inp).readlines()
    idx = [i for i, ln in enumerate(lines) if ln.strip().startswith("bhi\t")]
    assert len(idx) == 1, f"expected exactly one bhi, found {len(idx)}"
    lines[idx[0]] = lines[idx[0]].replace("bhi\t", "bgt\t", 1)
    open(outp, "w").writelines(lines)


if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2])
