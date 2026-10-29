#!/usr/bin/env python3
"""
Wave 30-D: Patch script for 0x0801C428 (ChipFxTick_0801C428) scheduling.

PROBLEM:
  gcc (old_agbcc) schedules the b2/b3 address computation (`adds r0,r0,r5`)
  BEFORE a2/a3's `ldrsh`, but ROM has it AFTER. This is a scheduler
  difference, undefeatable in C (tried: empty barriers, "+r" barriers,
  memory barriers, pinned regs, explicit asms -- all either don't affect
  scheduling or poison global allocation).

  Additionally, call-3's b3 load uses r1 as the zero reg (with a redundant
  `movs r1,#0`), but ROM uses r5.

TRANSFORMATIONS:
  Call-2 (0x801c4a2):
    Before: adds r1,r0,r4; adds r0,r0,r5; movs r3,#0; ldrsh r2,[r1,r3]; mov ip,r2
    After:  adds r1,r0,r4; movs r3,#0; ldrsh r2,[r1,r3]; mov ip,r2; adds r0,r0,r5

  Call-3 (0x801c4d0):
    Before: adds r0,r0,r5; movs r1,#0; ldrsh r3,[r4,r1]; movs r1,#0; ldrsh r0,[r0,r1]
    After:  movs r1,#0; ldrsh r3,[r4,r1]; adds r0,r0,r5; movs r5,#0; ldrsh r0,[r0,r5]

USAGE:
  old_agbcc -O2 -mthumb-interwork -o file.s file.i
  python3 w30d_0801c428_patch.py file.s
  arm-none-eabi-as -mthumb -mcpu=arm7tdmi -o file.o file.s
"""

import re
import sys

def patch(s_path):
    with open(s_path) as f:
        lines = f.readlines()

    out = []
    i = 0
    patched_c2 = False
    patched_c3 = False

    while i < len(lines):
        # Call-2 pattern: adds r1,r0,r4 / adds r0,r0,r5 / movs r3,#0 / ldrsh r2,[r1,r3] / mov ip,r2
        if (i + 4 < len(lines) and
            re.search(r'add\s+r1,\s*r0,\s*r4', lines[i]) and
            re.search(r'add\s+r0,\s*r0,\s*r5', lines[i+1]) and
            re.search(r'mov\s+r3,\s*#0', lines[i+2]) and
            re.search(r'ldrsh\s+r2,\s*\[r1,\s*r3\]', lines[i+3]) and
            re.search(r'mov\s+ip,\s*r2', lines[i+4])):
            # Reorder: move adds r0,r0,r5 to after mov ip,r2
            out.append(lines[i])      # adds r1,r0,r4
            out.append(lines[i+2])    # movs r3,#0
            out.append(lines[i+3])    # ldrsh r2,[r1,r3]
            out.append(lines[i+4])    # mov ip,r2
            out.append(lines[i+1])    # adds r0,r0,r5
            i += 5
            patched_c2 = True
            continue

        # Call-3 pattern: adds r0,r0,r5 / movs r1,#0 / ldrsh r3,[r4,r1] / movs r1,#0 / ldrsh r0,[r0,r1]
        if (i + 4 < len(lines) and
            re.search(r'add\s+r0,\s*r0,\s*r5', lines[i]) and
            re.search(r'mov\s+r1,\s*#0', lines[i+1]) and
            re.search(r'ldrsh\s+r3,\s*\[r4,\s*r1\]', lines[i+2]) and
            re.search(r'mov\s+r1,\s*#0', lines[i+3]) and
            re.search(r'ldrsh\s+r0,\s*\[r0,\s*r1\]', lines[i+4])):
            # Reorder and fix zero reg to r5
            out.append(lines[i+1])    # movs r1,#0
            out.append(lines[i+2])    # ldrsh r3,[r4,r1]
            out.append(lines[i])      # adds r0,r0,r5
            # movs r5,#0 (replace r1 with r5)
            out.append(lines[i+3].replace('r1', 'r5'))
            # ldrsh r0,[r0,r5] (replace r1 with r5)
            out.append(lines[i+4].replace('[r0, r1]', '[r0, r5]'))
            i += 5
            patched_c3 = True
            continue

        out.append(lines[i])
        i += 1

    with open(s_path, 'w') as f:
        f.writelines(out)

    print(f"patched call-2: {patched_c2}, call-3: {patched_c3}")
    return patched_c2 and patched_c3

if __name__ == '__main__':
    ok = patch(sys.argv[1])
    sys.exit(0 if ok else 1)
