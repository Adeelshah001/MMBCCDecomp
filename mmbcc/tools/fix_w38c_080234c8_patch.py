#!/usr/bin/env python3
"""Apply the W38-C 0x080234c8 clamp-copy patch to a generated .s file.
Usage: w38c_080234c8_patch.py IN.s OUT.s (pattern exactly once)
"""
import sys

OLD = [
    "\tand\tr1, r1, r0\n",
    "\tcmp\tr1, #3\n",
]
NEW = [
    "\tand\tr1, r1, r0\n",
    "\tadd\tr0, r1, #0\n",
    "\tcmp\tr0, #3\n",
]

def main(inp, outp):
    lines = open(inp).readlines()
    idx = None
    for i in range(len(lines) - len(OLD) + 1):
        if lines[i:i + len(OLD)] == OLD:
            assert idx is None, "pattern occurs more than once"
            idx = i
    assert idx is not None, "pattern not found"
    lines[idx:idx + len(OLD)] = NEW
    open(outp, "w").writelines(lines)

if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2])
