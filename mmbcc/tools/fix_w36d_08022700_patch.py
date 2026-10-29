#!/usr/bin/env python3
"""Post-process old_agbcc .s for w36d_08022700 (0x08022700).

Patch 1 (case 1 first store): 256 constant must be in r1, copied to r0.
  agbcc emits:  mov r0, #128 / lsl r0, r0, #1 / ldrb r2, [r3, #18] / orr r2, r2, r0
  ROM wants:    mov r1, #128 / lsl r1, r1, #1 / add r0, r1, #0 / ldrb r2, [r3, #18] / orr r2, r2, r0
Patch 2 (case 2): pool-first order, shift into r0, f12 store after address.
  agbcc emits:  str r2, [r3, #12] / ldrb r4, [r3, #9] / lsl r4, r4, #2 / ldr r0, POOL / add r4, r4, r0 / ldr r0, [r4]
  ROM wants:    ldr r1, POOL / ldrb r4, [r3, #9] / lsl r0, r4, #2 / add r0, r0, r1 / str r2, [r3, #12] / ldr r0, [r0]
Applied to the .s BEFORE assembling (labels recalc).
"""
import sys, re

path = sys.argv[1]
lines = open(path).read().splitlines(keepends=True)

# Patch 1: find "mov r0, #128" followed by "lsl r0, r0, #1" in case 1
# (case 0 uses mov r1, #144 so it is distinct; case 1's 128 is the only mov r0, #128)
done1 = False
for i in range(len(lines) - 1):
    if lines[i].strip() == "mov\tr0, #128" and lines[i+1].strip() == "lsl\tr0, r0, #1":
        lines[i:i+2] = [
            "\tmov\tr1, #128\n",
            "\tlsl\tr1, r1, #1\n",
            "\tadd\tr0, r1, #0\n",
        ]
        done1 = True
        break
assert done1, "patch 1 (case 1 256 copy) not found"

# Patch 2: case 2 block
done2 = False
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
            done2 = True
            break
assert done2, "patch 2 (case 2 reorder) not found"
open(path, "w").writelines(lines)
print("patch OK: case1 copy inserted, case2 reordered")

# Patch 3 (case 1 f18/t/d block): f18 must be in r0, d in r2.
#   agbcc emits:  ldrb r2, [r3, #18] / lsl r1, r2, #24 / ... / mov r0, #1 / ... / lsr r0, r1, #16 / sub r0, r2, r0
#   ROM wants:    ldrb r0, [r3, #18] / lsl r1, r0, #24 / ... / mov r2, #1 / ... / lsr r2, r1, #16 / sub r0, r0, r2
# The ldrb/lsl pair is identified by the following cmp + bne to the decrement block;
# the mov/lsr/sub trio is identified by the strb to [r3, #18] that follows.
done3a = done3b = done3c = False
for i in range(len(lines) - 1):
    if (lines[i].strip() == "ldrb\tr2, [r3, #18]"
        and lines[i+1].strip() == "lsl\tr1, r2, #24"):
        lines[i] = "\tldrb\tr0, [r3, #18]\n"
        lines[i+1] = "\tlsl\tr1, r0, #24\n"
        done3a = True
        break
assert done3a, "patch 3a (f18 load) not found"
for i in range(len(lines) - 1):
    if lines[i].strip() == "mov\tr0, #1":
        # only the d=1 mov (followed within a few lines by cmp + beq + lsr)
        for j in range(i+1, min(i+6, len(lines))):
            if lines[j].strip() == "lsr\tr0, r1, #16":
                lines[i] = "\tmov\tr2, #1\n"
                lines[j] = "\tlsr\tr2, r1, #16\n"
                done3b = True
                break
        if done3b:
            break
assert done3b, "patch 3b (d register) not found"
for i in range(len(lines) - 1):
    if lines[i].strip() == "sub\tr0, r2, r0":
        lines[i] = "\tsub\tr0, r0, r2\n"
        done3c = True
        break
assert done3c, "patch 3c (subs operands) not found"
open(path, "w").writelines(lines)
print("patch 3 OK: f18/t/d registers fixed (written)")
