#!/usr/bin/env python3
"""Fix GAS tail-padding for sub-4-byte-multiple function sections.

The compiler emits ".align 2, 0" at the end of each function section, and GAS
pads the section to 4 bytes with "mov r8, r8" (c0 46). For functions whose
true extent is not a multiple of 4 (e.g. 30 B, 50 B), that padding is not in
the ROM. This script rewrites ONLY the trailing .align of the named sections
to ".align 1, 0", leaving pool alignments (which must stay 4-byte) untouched.

Usage: fix_tail_align.py <file.s> <section> [<section> ...]
"""
import re
import sys

path = sys.argv[1]
targets = set(sys.argv[2:])

with open(path) as f:
    lines = f.readlines()

# Find section boundaries: (section_name, start_line, end_line)
bounds = []
cur = None
for i, ln in enumerate(lines):
    m = re.match(r'\s*\.section\s+(\.\S+?)(?:,|\s|$)', ln)
    if m:
        if cur:
            bounds.append((cur[0], cur[1], i))
        cur = (m.group(1), i)
if cur:
    bounds.append((cur[0], cur[1], len(lines)))

align_re = re.compile(r'^(\s*\.align\s+)2(\s*,\s*0\s*)$')
changed = 0
for name, start, end in bounds:
    if name not in targets:
        continue
    # last ".align 2, 0" in the section = the tail pad (pool aligns come
    # earlier and are followed by .word data)
    for i in range(end - 1, start - 1, -1):
        m = align_re.match(lines[i].rstrip('\n'))
        if m:
            lines[i] = f"{m.group(1)}1{m.group(2)}\n"
            changed += 1
            break

with open(path, 'w') as f:
    f.writelines(lines)
print(f"fix_tail_align: {changed} section(s) adjusted")
