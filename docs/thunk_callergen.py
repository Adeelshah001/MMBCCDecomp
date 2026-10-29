#!/usr/bin/env python3
"""Caller genuineness: for each BL site targeting the 25 validated starts,
verify the site sits in a coherent ARMv4T stream (walk back 24 halfwords;
all must decode valid and the walk must not cross an unconditional
branch/terminator). Also diagnose 2A846."""
import sys, struct
from collections import defaultdict
import gen_func_list_v2 as g

rom = g.rom
def u16(off): return struct.unpack_from('<H', rom, off)[0]

S, E = 0x29AC4, 0x2C7A4

def thumb_bl_target(bl_off):
    hi = u16(bl_off); lo = u16(bl_off + 2)
    if (hi & 0xF800) != 0xF000 or (lo & 0xF800) != 0xF800: return None
    off = ((hi & 0x7FF) << 12) | ((lo & 0x7FF) << 1)
    if off & (1 << 22): off -= (1 << 23)
    tgt = bl_off + 4 + off
    return tgt if 0 <= tgt < 0x50000 else None

callers_of = defaultdict(list)
for off in range(0, 0x50000 - 4, 2):
    hi = u16(off)
    if (hi & 0xF800) == 0xF000 and (u16(off+2) & 0xF800) == 0xF800:
        t = thumb_bl_target(off)
        if t is not None and S <= t < E:
            callers_of[t].append(off)

def stream_ok(bl_site):
    """Walk back up to 24 halfwords; require all decode valid (ARMv4T)
    and no unconditional control-flow break."""
    off = bl_site - 2
    for _ in range(24):
        if off < 0 or off % 2:
            return False, 'oob'
        d = g.dec_thumb(off)
        if d is None or d[1] == 'invalid':
            return False, f'invalid@{off:05X}'
        kind = d[1]
        if kind in ('b', 'bx', 'pop_pc', 'ret'):
            return False, f'cfbreak@{off:05X}'
        off -= 2
        if off < S - 0x100:
            break
    return True, 'ok'

print("=== caller genuineness ===")
allok = True
for t in sorted(callers_of):
    if not g.validate_target(t, 'T'):
        continue
    bad = []
    for c in callers_of[t]:
        ok, why = stream_ok(c)
        if not ok:
            bad.append((c, why))
    flag = '' if not bad else f'  <-- {len(bad)} SUSPECT'
    print(f'  {t:05X}: {len(callers_of[t])} callers{flag}')
    for c, why in bad[:4]:
        print(f'      {c:05X}: {why}')
        allok = False

# 2A846 diagnosis
print('=== 2A846 diagnosis ===')
t = 0x2A846
print('callers:', [f'{c:05X}' for c in callers_of[t]])
for c in callers_of[t]:
    ok, why = stream_ok(c)
    print(f'  caller {c:05X}: {why}')
    # context
    for off in range(c-8, c+8, 2):
        d = g.dec_thumb(off)
        print(f'    {off:05X}: {u16(off):04X} {d[1] if d else None}')
