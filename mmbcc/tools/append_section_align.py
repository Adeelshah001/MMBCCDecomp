#!/usr/bin/env python3
"""Append `.align 2, 0` at the end of named function sections.

Some matched functions need a `00 00` (not GAS's default `46 c0` /
`mov r8, r8`) tail pad to be byte-identical. agbcc emits no trailing
align for these; appending `.align 2, 0` after the function's `.size`
directive makes GAS pad with zeroes.

Usage: append_section_align.py <file.s> <section> [<section> ...]
Inserts one `\t.align\t2, 0` line right after the `.size` line that
terminates each named section.
"""
import re
import sys

path = sys.argv[1]
targets = set(sys.argv[2:])

with open(path) as f:
    lines = f.readlines()

cur = None
changed = 0
out = []
for ln in lines:
    m = re.match(r'\s*\.section\s+(\.\S+?)(?:,|\s|$)', ln)
    if m:
        cur = m.group(1)
    out.append(ln)
    if re.match(r'\s*\.size\s', ln) and cur in targets:
        out.append('\t.align\t2, 0\n')
        changed += 1

with open(path, 'w') as f:
    f.writelines(out)
print(f"append_section_align: {changed} section(s) adjusted")
