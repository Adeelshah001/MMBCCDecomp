#!/usr/bin/env python3
"""Post-process old_agbcc .s for w36d_080227dc (0x080227dc).
Patch A (case 1 first store): 288 in r1, copied to r0, f18 in r4.
  agbcc: mov r0,#144 / lsl r0,#1 / ldrb r4 / sub r2,r0,r4 (with ldrb first)
  ROM:   mov r1,#144 / lsl r1,#1 / add r0,r1 / ldrb r4 / sub r2,r0,r4
Patch B (case 1 second store): recompute s+78 (not bump).
  agbcc: add r1,#2 / ldrb r2 / sub r0,r0,r2 / strh r0,[r1]
  ROM:   ldrb r1 / sub r0,r0,r1 / add r1,r3,#78 / strh r0,[r1]
Patch C (case 2): same as 22700 patch 2 (pool-first, shift into r0).
Patch D (case 1 f18/t/d): same as 22700 patch 3 (f18 in r0, d in r2).
"""
import sys, re
path = sys.argv[1]
lines = open(path).read().splitlines(keepends=True)

# Patch A: find ldrb r4,[r3,#18] then mov r0,#144 / lsl r0 / sub r2,r0,r4
doneA = False
for i in range(len(lines) - 3):
    if (lines[i].strip() == "ldrb\tr4, [r3, #18]"
        and lines[i+1].strip() == "mov\tr0, #144"
        and lines[i+2].strip() == "lsl\tr0, r0, #1"
        and lines[i+3].strip() == "sub\tr2, r0, r4"):
        lines[i:i+4] = [
            "\tmov\tr1, #144\n",
            "\tlsl\tr1, r1, #1\n",
            "\tadd\tr0, r1, #0\n",
            "\tldrb\tr4, [r3, #18]\n",
            "\tsub\tr2, r0, r4\n",
        ]
        doneA = True
        break
assert doneA, "patch A not found"

# Patch B: add r1,#2 / ldrb r2 / sub r0,r0,r2 / strh r0,[r1]
doneB = False
for i in range(len(lines) - 3):
    if (lines[i].strip() == "add\tr1, r1, #2"
        and lines[i+1].strip() == "ldrb\tr2, [r3, #18]"
        and lines[i+2].strip() == "sub\tr0, r0, r2"
        and lines[i+3].strip() == "strh\tr0, [r1]"):
        lines[i:i+4] = [
            "\tldrb\tr1, [r3, #18]\n",
            "\tsub\tr0, r0, r1\n",
            "\tadd\tr1, r3, #0\n",
            "\tadd\tr1, #78\n",
            "\tstrh\tr0, [r1]\n",
        ]
        doneB = True
        break
assert doneB, "patch B not found"

# Patch C: case 2 (same as 22700 patch 2)
doneC = False
for i in range(len(lines) - 5):
    if (lines[i].strip() == "ldrb\tr4, [r3, #9]"
        and lines[i+1].strip() == "lsl\tr4, r4, #2"):
        m = re.match(r"\tldr\tr0, (\S+)\n", lines[i+2])
        if (m and lines[i+3].strip() == "add\tr4, r4, r0"
            and lines[i+4].strip() == "str\tr2, [r3, #12]"
            and lines[i+5].strip() == "ldr\tr0, [r4]"):
            lab = m.group(1)
            lines[i:i+6] = [
                "\tldr\tr1, %s\n" % lab,
                "\tldrb\tr4, [r3, #9]\n",
                "\tlsl\tr0, r4, #2\n",
                "\tadd\tr0, r0, r1\n",
                "\tstr\tr2, [r3, #12]\n",
                "\tldr\tr0, [r0]\n",
            ]
            doneC = True
            break
assert doneC, "patch C not found"

# Patch D: f18/t/d (same as 22700 patch 3)
doneD1 = doneD2 = doneD3 = False
for i in range(len(lines) - 1):
    if (lines[i].strip() == "ldrb\tr2, [r3, #18]"
        and lines[i+1].strip() == "lsl\tr1, r2, #24"):
        lines[i] = "\tldrb\tr0, [r3, #18]\n"
        lines[i+1] = "\tlsl\tr1, r0, #24\n"
        doneD1 = True
        break
assert doneD1, "patch D1 not found"
for i in range(len(lines) - 1):
    if lines[i].strip() == "mov\tr0, #1":
        for j in range(i+1, min(i+6, len(lines))):
            if lines[j].strip() == "lsr\tr0, r1, #16":
                lines[i] = "\tmov\tr2, #1\n"
                lines[j] = "\tlsr\tr2, r1, #16\n"
                doneD2 = True
                break
        if doneD2:
            break
assert doneD2, "patch D2 not found"
for i in range(len(lines) - 1):
    if lines[i].strip() == "sub\tr0, r2, r0":
        lines[i] = "\tsub\tr0, r0, r2\n"
        doneD3 = True
        break
assert doneD3, "patch D3 not found"

open(path, "w").writelines(lines)
print("patch OK: A+B+C+D applied")
