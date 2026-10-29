#!/usr/bin/env python3
"""Targeted .s patch for ChipSlot_Tick @0x0800D9FC, H-first load/key group.

Problem: old_agbcc (and main agbcc) always sink the variable load below the
key computation, emitting (10 bytes at relative 0xb0-0xb9):

    lsl   r1, r1, #8
    ldrb  r0, [r5, #29]
    orr   r1, r1, r0
    mov   r7, #0
    ldrsh r0, [r4, r7]

ROM order (same 5 instructions, groups swapped):

    mov   r7, #0
    ldrsh r0, [r4, r7]
    lsl   r1, r1, #8
    ldrb  r7, [r5, #29]
    orr   r1, r1, r7

32 C variants + micro-tests exhausted for this group (staging/wave35_A);
gcc's sink-to-compare-site is invariant across source order, operator
form, and compiler version. The reorder preserves instruction count and
length exactly, so the remaining 314 bytes are untouched.

Usage: fix_0800d9fc.py <file.s>  (edits in place; fails unless the
5-line block matches exactly once)
"""
import re
import sys

OLD = (
    "\tlsl\tr1, r1, #8\n"
    "\tldrb\tr0, [r5, #29]\n"
    "\torr\tr1, r1, r0\n"
    "\tmov\tr7, #0\n"
    "\tldrsh\tr0, [r4, r7]\n"
)
NEW = (
    "\tmov\tr7, #0\n"
    "\tldrsh\tr0, [r4, r7]\n"
    "\tlsl\tr1, r1, #8\n"
    "\tldrb\tr7, [r5, #29]\n"
    "\torr\tr1, r1, r7\n"
)


def main() -> None:
    path = sys.argv[1]
    with open(path) as f:
        text = f.read()
    count = text.count(OLD)
    assert count == 1, f"H-first block matches {count} times, expected 1"
    text = text.replace(OLD, NEW)
    with open(path, "w") as f:
        f.write(text)
    print("fix_0800d9fc: 1 replacement (H-first load/key reorder)")


if __name__ == "__main__":
    main()
