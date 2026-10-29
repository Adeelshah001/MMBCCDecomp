#!/usr/bin/env python3
"""Apply the W38-C 0x08023a7c prologue reorder to a generated .s file.
Usage: w38c_08023a7c_patch.py IN.s OUT.s  (each pattern must occur exactly once)
"""
import sys

OLD = [
    "\tmov\tr0, #127\n",
    "\tmov\tr8, r0\n",
    "\tldrb\tr3, [r6, #4]\n",
    "\tldrb\tr0, [r6]\n",
    "\tadd\tr2, r3, r0\n",
]
NEW = [
    "\tldrb\tr0, [r6]\n",
    "\tldrb\tr3, [r6, #4]\n",
    "\tadd\tr2, r0, r3\n",
    "\tmov\tr0, #127\n",
    "\tmov\tr8, r0\n",
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
