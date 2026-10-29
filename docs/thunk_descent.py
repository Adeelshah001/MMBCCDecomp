#!/usr/bin/env python3
"""Recursive descent from 29AC4 over the span: are the idiom instances
interior points of one big function? Catalog exits."""
import sys, struct
from collections import Counter
import gen_func_list_v2 as g

rom = g.rom
def u16(off): return struct.unpack_from('<H', rom, off)[0]

S, E = 0x29AC4, 0x2C7A4

THUNK = (0x1C38, 0x4649, 0x4652, 0x9B08)
idioms = set()
for off in range(S, E, 2):
    if (u16(off), u16(off+2), u16(off+4), u16(off+6)) == THUNK:
        idioms.add(off)
print(f"strict idiom instances: {len(idioms)}")

visited = set()
exits = Counter()
exit_detail = []
stack = [S]
bl_targets = Counter()
while stack:
    pc = stack.pop()
    while True:
        if pc in visited or not (S <= pc < E) or pc % 2:
            if not (S <= pc < E) and pc % 2 == 0 and 0 <= pc < 0x50000:
                exits['branch_outside'] += 1
                exit_detail.append(pc)
            break
        visited.add(pc)
        d = g.dec_thumb(pc)
        if d is None:
            exits['invalid'] += 1; exit_detail.append(pc); break
        sz, kind, tgt = d[0], d[1], d[2]
        if kind == 'bl':
            bl_targets[tgt] += 1
            pc += sz; continue
        elif kind == 'b':
            pc = tgt; continue
        elif kind == 'bcond':
            stack.append(tgt); pc += sz; continue
        elif kind in ('bx', 'pop_pc', 'ret'):
            exits[kind] += 1; exit_detail.append(pc); break
        elif kind == 'invalid':
            exits['invalid'] += 1; exit_detail.append(pc); break
        else:
            pc += sz; continue

print(f"visited halfwords: {len(visited)} ({2*len(visited)} bytes)")
print("exits:", dict(exits))
print("exit pcs:", [f'{x:05X}' for x in exit_detail[:20]])
reached_idioms = idioms & visited
print(f"idiom instances reached by descent: {len(reached_idioms)}/{len(idioms)}")
unreached = sorted(idioms - visited)
print("unreached idioms:", [f'{x:05X}' for x in unreached][:10])
print("top BL targets:", [(f'{k:05X}', v) for k, v in bl_targets.most_common(8)])
# byte coverage of span
cov = 2 * len(visited)
print(f"span bytes: {E-S}, covered: {cov} ({100*cov/(E-S):.1f}%)")
