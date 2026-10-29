#!/usr/bin/env python3
"""Apply the W38-C 0x0801bde4 patches to a generated .s file.
Usage: w38c_0801bde4_patch.py IN.s OUT.s (each pattern exactly once)
"""
import sys

SITES = [
    (["\tpush\t{r4, r5, r6, lr}\n"],
     ["\tpush\t{r4, r5, r6, r7, lr}\n"]),
    (["\tldr\tr7, .L19\n",
      "\tlsl\tr3, r3, #16\n",
      "\tasr\tr3, r3, #16\n",
      "\tadd\tr6, r6, r7\n",
      "\tlsl\tr6, r6, #16\n",
      "\tasr\tr6, r6, #16\n",
      "\tstr\tr6, [sp]\n"],
     ["\tlsl\tr3, r3, #16\n",
      "\tasr\tr3, r3, #16\n",
      "\tldr\tr7, .L19\n",
      "\tadd\tr0, r6, r7\n",
      "\tlsl\tr0, r0, #16\n",
      "\tasr\tr0, r0, #16\n",
      "\tstr\tr0, [sp]\n"]),
    (["\tpop\t{r4, r5, r6}\n"],
     ["\tpop\t{r4, r5, r6, r7}\n"]),
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
