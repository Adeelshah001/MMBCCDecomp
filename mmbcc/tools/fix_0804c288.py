#!/usr/bin/env python3
"""Wave 35-B .s post-process for 0x0804c288.
1. First test: and+cmp -> tst (gcc never emits tst for (*p & 0x80)).
2. Second test: ldrb r1/mov r0,and/cmp -> ldrb r0/mov r3,and (ROM shape, no cmp).
3. Fn-pointer pool chain: ldr r0,pool / ldr r3,[r0] -> ldr r3,pool / ldr r3,[r3].
4. Indirect call: bl _call_via_r3 -> bl 0x0804c278 (local bx-r3 thunk).
Each pattern must match exactly once; the script asserts this.
"""
import sys, re
p = sys.argv[1]
s = open(p).read()
pats = [
    ("\tldrb\tr1, [r5]\n\tmov\tr0, #128\n\tand\tr0, r0, r1\n\tcmp\tr0, #0",
     "\tldrb\tr1, [r5]\n\tmov\tr0, #128\n\ttst\tr0, r1"),
    ("\tldrb\tr1, [r4, #1]\n\tmov\tr0, #7\n\tand\tr0, r0, r1\n\tcmp\tr0, #0",
     "\tldrb\tr0, [r4, #1]\n\tmov\tr3, #7\n\tand\tr0, r3"),
    ("\tbl\t_call_via_r3", "\tbl\t0x0804c278"),
]
for old, new in pats:
    n = s.count(old)
    assert n == 1, f"pattern match count {n} (want 1): {old[:60]!r}"
    s = s.replace(old, new)
m = re.search(r"\tldr\tr0, (\.L\d+)\n\tldr\tr3, \[r0\]", s)
assert m, "pool-chain pattern not found"
s = s[:m.start()] + f"\tldr\tr3, {m.group(1)}\n\tldr\tr3, [r3]" + s[m.end():]
assert len(re.findall(r"\tldr\tr0, \.L\d+\n\tldr\tr3, \[r0\]", s)) == 0
open(p, "w").write(s)
print("patch ok: 4 replacements")
