#!/usr/bin/env python3
"""Post-process agbcc .s for 0x0803ac4c: fix three register choices + push/pop r7.

Reads the .s file, builds a pool-label -> value map, then rewrites:
1. push {r4,r5,r6,lr} -> push {r4,r5,r6,r7,lr} ; pop {r4,r5,r6} -> pop {r4,r5,r6,r7}
   (r7 is used via register pins which mark it fixed, so gcc doesn't save it;
   the function has no stack frame, so saving r7 is semantically a no-op)
2. B32 o1: ldr r0,[pool 0x469b] + add r1,r4,r0 -> ldr r5 / add r1,r4,r5
3. B16 q:  ldr r2,[pool 0x469a] + add r3,r4,r2 -> ldr r0 / add r3,r4,r0
4. Tail:   ldr r2,[pool 0x4698] + add r0,r4,r2 -> ldr r5 / add r0,r4,r5
Only rewrites when the following instruction matches the expected pattern,
so unrelated loads of the same pool values are untouched.
"""
import re
import sys

src = sys.argv[1]
with open(src) as f:
    lines = f.readlines()

# Build pool label -> list of word values.
# Labels look like ".L18:" followed by "\t.word\t<val>" lines.
# Values may be like "18075" or "gAddrZero+136517520" or "gEwram_02004CE0".
pool = {}
cur = None
for ln in lines:
    m = re.match(r'^(\.L\d+):\s*$', ln)
    if m:
        cur = m.group(1)
        pool[cur] = []
        continue
    m = re.match(r'^\s*\.word\s+(.+?)\s*$', ln)
    if m and cur is not None:
        pool[cur].append(m.group(1).strip())
        continue
    if re.match(r'^\s*\.(text|code|align)', ln):
        # keep cur; words may follow .align
        continue
    if ln.strip() and not ln.startswith('\t') and not ln.startswith('.'):
        cur = None

def pool_val(label, idx):
    """Resolve '.L18+4' -> integer value or None if symbolic."""
    m = re.match(r'^(\.L\d+)(?:\+(\d+))?$', label)
    if not m:
        return None
    base, off = m.group(1), int(m.group(2) or 0)
    words = pool.get(base)
    if not words:
        return None
    wi = off // 4
    if wi >= len(words):
        return None
    v = words[wi]
    try:
        return int(v)
    except ValueError:
        return None

# (pool_value, ldr_reg, add_dst, add_src1, add_src2, new_reg)
RULES = [
    # B32 o1: ldr r0,=0x469b ; add r1,r4,r0  -> r5
    (0x469b, 'r0', 'r1', 'r4', 'r0', 'r5'),
    # B16 q: ldr r2,=0x469a ; add r3,r4,r2 -> r0
    (0x469a, 'r2', 'r3', 'r4', 'r2', 'r0'),
    # Tail: ldr r2,=0x4698 ; add r0,r4,r2 -> r5
    (0x4698, 'r2', 'r0', 'r4', 'r2', 'r5'),
]

out = []
i = 0
n = len(lines)
fixes = []
while i < n:
    ln = lines[i]
    # push/pop r7
    if re.match(r'^\tpush\t\{r4, r5, r6, lr\}\s*$', ln):
        out.append('\tpush\t{r4, r5, r6, r7, lr}\n')
        fixes.append('push r7')
        i += 1
        continue
    if re.match(r'^\tpop\t\{r4, r5, r6\}\s*$', ln):
        out.append('\tpop\t{r4, r5, r6, r7}\n')
        fixes.append('pop r7')
        i += 1
        continue
    m = re.match(r'^\tldr\t(r\d+), (\.L\d+(?:\+\d+)?)\s*$', ln)
    if m and i + 1 < n:
        reg, label = m.group(1), m.group(2)
        val = pool_val(label, 0)
        nxt = lines[i + 1]
        m2 = re.match(r'^\tadd\t(r\d+), (r\d+), (r\d+)\s*$', nxt)
        if m2:
            for (pv, lr, ad, a1, a2, nr) in RULES:
                if val == pv and reg == lr and m2.group(1) == ad \
                   and m2.group(2) == a1 and m2.group(3) == a2:
                    out.append('\tldr\t%s, %s\n' % (nr, label))
                    out.append('\tadd\t%s, %s, %s\n' % (ad, a1, nr))
                    fixes.append('0x%x %s->%s' % (pv, lr, nr))
                    i += 2
                    break
            else:
                out.append(ln)
                i += 1
            continue
    out.append(ln)
    i += 1

with open(src, 'w') as f:
    f.writelines(out)
print('fixes applied: %s' % fixes, file=sys.stderr)
