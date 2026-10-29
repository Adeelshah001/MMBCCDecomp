#!/usr/bin/env python3
"""Change the SECTION-START alignment of named sections from 4 to 2 bytes.

Some matched functions have a mid-section literal pool (so fix_tail_align.py
cannot be used — it would rewrite the pool's align). Their sections still get
a 2-byte \"mov r8, r8\" (c0 46) tail from the 4-byte section alignment, while
the ROM has 00 00 (or nothing) there. Changing the section-start
\".align 2, 0\" to \".align 1, 0\" drops the section alignment to 2 bytes,
eliminating the tail pad; the mid-section pool aligns are untouched.

Usage: fix_section_start_align.py <file.s> <section> [<section> ...]
Rewrites only the FIRST \".align 2, 0\" following each named \".section\".
"""
import re
import sys

path = sys.argv[1]
targets = set(sys.argv[2:])

with open(path) as f:
    lines = f.readlines()

align_re = re.compile(r'^(\s*\.align\s+)2(\s*,\s*0\s*)$')
cur = None
changed = 0
done = set()
for i, ln in enumerate(lines):
    m = re.match(r'\s*\.section\s+(\.\S+?)(?:,|\s|$)', ln)
    if m:
        cur = m.group(1)
        continue
    if cur in targets and cur not in done:
        m2 = align_re.match(ln.rstrip('\n'))
        if m2:
            lines[i] = f"{m2.group(1)}1{m2.group(2)}\n"
            changed += 1
            done.add(cur)
    # stop looking once we leave the section's head (past .globl/.type)
    if cur in done:
        cur = None

with open(path, 'w') as f:
    f.writelines(lines)
print(f"fix_section_start_align: {changed} section(s) adjusted")
