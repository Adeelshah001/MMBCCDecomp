#!/usr/bin/env python3
"""Apply the W38-C 0x0801c6b0 patches to a generated .s file.
Usage: w38c_0801c6b0_patch.py IN.s OUT.s (each pattern exactly once)
"""
import sys

SITES = [
    (["\tldr\tr5, [sp, #8]\n"], ["\tldr\tr3, [sp, #8]\n"]),
    (["\tlsl\tr5, r5, #16\n"], ["\tlsl\tr5, r3, #16\n"]),
]

def main(inp, outp):
    lines = open(inp).readlines()
    for old, new in SITES:
        idx = None
        for i in range(len(lines) - len(old) + 1):
            if lines[i:i + len(old)] == old:
                assert idx is None, "pattern occurs more than once"
                idx = i
        assert idx is not None, f"pattern not found: {old[0].strip()}"
        lines[idx:idx + len(old)] = new
    open(outp, "w").writelines(lines)

if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2])
