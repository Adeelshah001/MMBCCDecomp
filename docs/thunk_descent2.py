#!/usr/bin/env python3
"""Full-span recursive descent (generator semantics): seed from all idiom
instances + 25 validated starts; follow b/bcond/bl; stop at indirect exits
(bx reg / mov pc,reg) and invalid. Produces visited instruction boundaries;
a caller is genuine iff visited. Also collects each new target's callees."""
import sys, struct
from collections import defaultdict, Counter
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

THUNK = (0x1C38, 0x4649, 0x4652, 0x9B08)
idioms = sorted(off for off in range(S, E, 2)
                if (u16(off),u16(off+2),u16(off+4),u16(off+6)) == THUNK)

callers_of = defaultdict(list)
for off in range(0, 0x50000 - 4, 2):
    hi = u16(off)
    if (hi & 0xF800) == 0xF000 and (u16(off+2) & 0xF800) == 0xF800:
        t = thumb_bl_target(off)
        if t is not None and S <= t < E:
            callers_of[t].append(off)
targets = sorted(t for t in callers_of if g.validate_target(t, 'T'))
print(f"seeds: {len(idioms)} idioms + {len(targets)} validated targets", file=sys.stderr)

INDIRECT = {'bx', 'mov_pc', 'bx_reg'}
visited = set()
indirect_exits = Counter()
stack = idioms + targets
while stack:
    pc = stack.pop()
    while True:
        if pc in visited: break
        if not (S <= pc < E) or pc % 2: break
        visited.add(pc)
        d = g.dec_thumb(pc)
        if d is None or d[1] == 'invalid': break
        sz, kind = d[0], d[1]
        if kind == 'bl':
            pc += sz; continue
        elif kind == 'b':
            pc = d[2]; continue
        elif kind == 'bcond':
            if d[2] is not None: stack.append(d[2])
            pc += sz; continue
        elif kind in ('bx',):
            indirect_exits[pc] += 1; break
        elif kind in ('pop_pc', 'ret'):
            break
        else:
            # check mov pc, rN which may come back as 'fall' or other kind
            pc += sz; continue

print(f"visited insn boundaries: {len(visited)}", file=sys.stderr)
print(f"indirect exits: {len(indirect_exits)}", file=sys.stderr)

# caller genuineness
print("=== caller genuineness (visited-boundary check) ===")
for t in targets:
    gen = [c for c in callers_of[t] if c in visited]
    sus = [c for c in callers_of[t] if c not in visited]
    print(f"  {t:05X}: {len(gen)}/{len(callers_of[t])} genuine"
          + ('' if not sus else f' SUSPECT {[f"{c:05X}" for c in sus][:6]}'))

# each target's callees + known-membership
known = set()
for fn in ('func_list_v2.txt', 'func_list_v2_1_addendum.txt', 'func_list_v2_2_addendum.txt'):
    for line in open(fn):
        line = line.strip()
        if line and not line.startswith('#'):
            known.add(int(line.split()[0], 16))
print("=== callees of new targets (K=known, N=new/unknown) ===")
for t in targets:
    callees = Counter()
    # decode body: linear from t until next target/idiom or 200 insns, collecting bl
    off = t
    for _ in range(200):
        if off in visited and off != t:
            pass
        d = g.dec_thumb(off)
        if d is None or d[1] in ('invalid',): break
        if d[1] == 'bl' and d[2] is not None:
            callees[d[2]] += 1
        if d[1] in ('b', 'bx', 'pop_pc', 'ret'): break
        off += d[0]
        if off >= E: break
    tags = []
    for c, n in callees.most_common(6):
        tags.append(f"{c:05X}{'K' if c in known else ('N' if c in set(targets) else '?')}x{n}")
    print(f"  {t:05X}: {' '.join(tags) if tags else '(no bl)'}")
