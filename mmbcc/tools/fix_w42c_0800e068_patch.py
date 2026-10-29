#!/usr/bin/env python3
"""Wave 42 landing: .s patch for w42c_0800e068 (0x0800e068, 220 B).

Coordinator-sanctioned 4-byte register-swap patch (Wave 42, w37b precedent).
Worker C's v3 (old_agbcc) builds 220 B with exactly 4 differing bytes, all
in two identical instruction pairs (one per CpuSet path):
- built ldr r0,[r5,#8] (table) + lsl r1,r7,#2 (index), ROM ldr r1 + lsl r0.
  The very next instruction in both paths is adds r0,r0,r1, and addition
  is commutative, so the swap is semantics-preserving: entp is identical.
C-only steering (pin, clobber-reservation) perturbs allocation globally
and was reverted. See staging/w42c_gaps/RESULTS.md.
"""
import sys
s = open(sys.argv[1]).read()


def rep(old, new, tag, expect):
    global s
    assert s.count(old) == expect, f"{tag}: count={s.count(old)} (expected {expect}) for {old!r}"
    s = s.replace(old, new)


# Both CpuSet paths: table pointer r0 -> r1 (2 occurrences)
rep("\tldr\tr0, [r5, #8]\n",
    "\tldr\tr1, [r5, #8]\n", "P1", 2)
# Both CpuSet paths: index shift r1 -> r0 (2 occurrences)
rep("\tlsl\tr1, r7, #2\n",
    "\tlsl\tr0, r7, #2\n", "P2", 2)
open(sys.argv[2], "w").write(s)
