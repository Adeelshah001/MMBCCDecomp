#!/usr/bin/env python3
"""Wave 42 landing: .s patch for w42a_0801b9e8 (0x0801b9e8, 172 B).

Coordinator-sanctioned 4-byte register-encoding patch (Wave 42).
Worker A's v30 (old_agbcc) builds 172 B with exactly 4 differing bytes,
all register fields, semantically identical to ROM in both spots:
- P1: second-call s[16] load: built ldrb r2 + lsl r0,r2,#1, ROM ldrb r3
  + lsl r0,r3,#1 (the loaded byte is consumed immediately by the shift;
  only the scratch register differs).
- P2: tail table-base load: built ldr r3 + adds r0,r0,r3, ROM ldr r1
  + adds r0,r0,r1 (the pool value is consumed immediately by the add;
  only the scratch register differs).
C-only steering was exhausted (~30 variants, v8-v47): direct call-argument
form gives ROM's picks but not load-before-increment order; temp forms fix
the order but shift both picks. See staging/w42a_1b9e8/RESULTS.md.
"""
import sys
s = open(sys.argv[1]).read()


def rep(old, new, tag, expect):
    global s
    assert s.count(old) == expect, f"{tag}: count={s.count(old)} (expected {expect}) for {old!r}"
    s = s.replace(old, new)


# P1: second-call s[16] load (unique: first call uses r1, this one r2)
rep("\tldrb\tr2, [r6, #16]\n\tlsl\tr0, r2, #1\n",
    "\tldrb\tr3, [r6, #16]\n\tlsl\tr0, r3, #1\n", "P1", 1)
# P2: tail table-base load (unique: only .L4+16 load is into r3)
rep("\tldr\tr3, .L4+16\n\tadd\tr0, r0, r3\n",
    "\tldr\tr1, .L4+16\n\tadd\tr0, r0, r1\n", "P2", 1)
open(sys.argv[2], "w").write(s)
