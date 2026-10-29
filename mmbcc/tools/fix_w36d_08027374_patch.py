#!/usr/bin/env python3
"""Post-process old_agbcc .s for w36d_08027374 (0x08027374).
Case 3: ROM loads the call arg into r1 then copies to r0.
  agbcc: ldr r1,POOL / add r0,r4,r1 / ldr r0,[r0] / bl 21d84
  ROM:   ldr r1,POOL / add r0,r4,r1 / ldr r1,[r0] / add r0,r1 / bl 21d84
"""
import sys, re
path = sys.argv[1]
lines = open(path).read().splitlines(keepends=True)
done = False
for i in range(len(lines) - 3):
    m = re.match(r"\tldr\tr1, (\S+)\n", lines[i])
    if (m and lines[i+1].strip() == "add\tr0, r4, r1"
        and lines[i+2].strip() == "ldr\tr0, [r0]"
        and lines[i+3].strip().startswith("bl\t")):
        lines[i:i+4] = [
            "\tldr\tr1, %s\n" % m.group(1),
            "\tadd\tr0, r4, r1\n",
            "\tldr\tr1, [r0]\n",
            "\tadd\tr0, r1, #0\n",
            lines[i+3],
        ]
        done = True
        break
assert done, "case 3 copy patch not found"
open(path, "w").writelines(lines)
print("patch OK: case 3 copy inserted")
