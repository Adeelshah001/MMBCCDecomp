#!/usr/bin/env python3
"""Post-process old_agbcc .s for w36d_0802fc70 (0x0802fc70).
Patch 1 (off): ROM computes (s+off)+b*4 with b*4 in r1, off in r2;
  agbcc computes (s+b*4)+off with an extra adds. Rewrite the off block.
Patch 2 (call result): ROM moves the u8 call result to r2
  (lsl r0,24 / lsr r2,24); agbcc keeps it in r0.
Patch 3 (f29): ROM loads f29 to r0 then copies to r1; agbcc loads to r1.
Patch 4/5 (checks 2/3): ROM re-extends f29 into r0 (lsl/lsr) before cmp;
  agbcc compares r1 directly. Insert the extension and retarget cmps.
"""
import sys
path = sys.argv[1]
txt = open(path).read()
lines = txt.splitlines(keepends=True)

def find(pred, start=0):
    for i in range(start, len(lines)):
        if pred(lines[i].strip()):
            return i
    return -1

# Patch 0: b zero-extension keeps b in r2 (not r0)
i = find(lambda s: s == "lsr\tr0, r2, #24")
assert i >= 0, "b extension not found"
lines[i] = "\tlsr\tr2, r2, #24\n"
# Patch 1: off block from "cmp r1, #0" to "add r0, r0, r1" (before ldr r0,[r0])
i = find(lambda s: s == "cmp\tr1, #0")
assert i >= 0, "off cmp not found"
j = find(lambda s: s == "add\tr0, r0, r1", i)
assert j > i, "off add not found"
lines[i:j+1] = [
    "\tcmp\tr1, #0\n",
    "\tbne\t.L3\t@cond_branch\n",
    "\tlsl\tr1, r2, #2\n",
    "\tmov\tr2, #168\n",
    "\tlsl\tr2, r2, #1\n",
    "\tb\t.L99\n",
    ".L3:\n",
    "\tlsl\tr1, r2, #2\n",
    "\tmov\tr2, #182\n",
    "\tlsl\tr2, r2, #1\n",
    ".L99:\n",
    "\tadd\tr0, r4, r2\n",
    "\tadd\tr0, r0, r1\n",
]
# Patch 2: call-result extension into r2 (the lsr right after bl 3fd68 + lsl)
i = find(lambda s: s.startswith("bl\tSub_0803FD68"))
assert i >= 0, "bl 3fd68 not found"
assert lines[i+1].strip() == "lsl\tr0, r0, #24", lines[i+1]
assert lines[i+2].strip() == "lsr\tr0, r0, #24", lines[i+2]
lines[i+2] = "\tlsr\tr2, r0, #24\n"
# Patch 3: f29 load to r0 + copy to r1
i = find(lambda s: s == "ldrb\tr1, [r4, #29]")
assert i >= 0, "ldrb f29 not found"
lines[i:i+1] = ["\tldrb\tr0, [r4, #29]\n", "\tadd\tr1, r0, #0\n"]
# Patch 4: check2 extension + retarget (first cmp r1,#1 after the f29 load)
i = find(lambda s: s == "cmp\tr1, #1")
assert i >= 0, "check2 cmp not found"
lines[i:i+1] = ["\tlsl\tr0, r1, #24\n", "\tlsr\tr0, r0, #24\n", "\tcmp\tr0, #1\n"]
# check1's call-result cmp: cmp r0,#1 -> cmp r2,#1 (the one before beq .L15)
i = find(lambda s: s == "cmp\tr0, #1")
assert i >= 0, "check1 cmp not found"
lines[i] = "\tcmp\tr2, #1\n"
# check2's call-result cmp: cmp r0,#2 -> cmp r2,#2
i = find(lambda s: s == "cmp\tr0, #2")
assert i >= 0, "check2 result cmp not found"
lines[i] = "\tcmp\tr2, #2\n"
# Patch 5: check3 extension + retarget
i = find(lambda s: s == "cmp\tr1, #4")
assert i >= 0, "check3 cmp not found"
lines[i:i+1] = ["\tlsl\tr0, r1, #24\n", "\tlsr\tr0, r0, #24\n", "\tcmp\tr0, #4\n"]
i = find(lambda s: s == "cmp\tr0, #3")
assert i >= 0, "check3 result cmp not found"
lines[i] = "\tcmp\tr2, #3\n"
# check3 store: strb r0 -> strb r2 (the strb right before mov r5,#1)
i = find(lambda s: s == "mov\tr5, #1")
assert i >= 0, "mov r5,1 not found"
assert lines[i-1].strip() == "strb\tr0, [r4, #29]", lines[i-1]
lines[i-1] = "\tstrb\tr2, [r4, #29]\n"
open(path, "w").writelines(lines)
print("patch OK: off + result-r2 + f29 copy + extensions")
