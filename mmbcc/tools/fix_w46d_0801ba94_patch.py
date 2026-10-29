#!/usr/bin/env python3
"""Wave 46 landing: .s patch for w46d_0801ba94 (0x0801ba94, 256 B).

Coordinator-SANCTIONED register-field patch (Wave 46, same class as
the Wave 42 0x0801b9e8 register-encoding patch), extended by a
push/pop-mask adjustment that is provably neutral here:
  - o1 home r4 -> r7 (load + both (s16) casts): r4 holds mode, dead on
    the c1 path (mode's only later use is c2's str, a disjoint path);
    r4 is reused as the s44 temp in the else branch only AFTER o1's
    last use, so the rename conflicts with nothing; r7 is otherwise
    unused in the function (no other r7 bytes differ).
  - push/pop mask +r7: saving/restoring an otherwise-unused
    callee-saved register is neutral, AND the frame shift is uniform:
    every sp-relative access in the body is frame-local (offsets <= 8:
    CopyMirrored dest sp+4, o0 load sp+4, o1 load sp+8, stores sp+0),
    with identical offsets in built and ROM code — there are NO
    caller-stack-arg reads (those would sit at sp+28/32 and would
    differ in offset bytes; the only diffs are the 5 patched bytes).
    Push and pop change symmetrically, so the frame balances.
C-only steering was exhausted (r7 pins poison to 260 B / ~144 diffs;
commutative flips canonicalized back; main -O2 worse at 17 diffs).
"""
import sys
inp, outp = sys.argv[1], sys.argv[2]
text = open(inp).read()
subs = [
    ("\tpush\t{r4, r5, r6, lr}\n", "\tpush\t{r4, r5, r6, r7, lr}\n", 1),
    ("\tldr\tr4, [sp, #8]\n", "\tldr\tr7, [sp, #8]\n", 1),
    ("\tlsl\tr3, r4, #16\n", "\tlsl\tr3, r7, #16\n", 2),
    ("\tpop\t{r4, r5, r6}\n", "\tpop\t{r4, r5, r6, r7}\n", 1),
]
for old, new, count in subs:
    assert text.count(old) == count, \
        f"{old!r} count={text.count(old)} (expected {count})"
    assert new not in text, f"NEW already present (double-patch?): {new!r}"
    text = text.replace(old, new)
open(outp, "w").write(text)
print("patched: 5 register-field substitutions applied")
