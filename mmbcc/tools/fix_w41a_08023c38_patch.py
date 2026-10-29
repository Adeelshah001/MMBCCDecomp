#!/usr/bin/env python3
"""Wave 41 landing wrapper: .s patch for w41a_08023c38 (0x08023c38, 172 B).
Patch logic extracted VERBATIM from the worker's verified patch_v9.py;
only the I/O was re-wired to argv in/out (Makefile convention).
Step 1: fold `lsr r0,r0,#3; add r6,r0,#0` into single `lsr r6,r0,#3`.
Step 2 (second __modsi3 block only): keep m2's unsigned copy in r2, extend
into r1 (old_agbcc coalesces copy+extend into r1; ROM keeps them separate).
"""
import sys
s = open(sys.argv[1]).read()
OLD = "\tlsr\tr0, r0, #3\n\tadd\tr6, r0, #0\n"
NEW = "\tlsr\tr6, r0, #3\n"
assert s.count(OLD) == 1, f"patch1 pattern count = {s.count(OLD)} (expected 1)"
s = s.replace(OLD, NEW)
parts = s.split("bl\t__modsi3")
assert len(parts) == 3, f"expected exactly 2 bl __modsi3, got {len(parts)-1}"
tail = parts[2]
assert tail.count("\tlsr\tr1, r0, #16\n") == 2, "second-block lsr count"
assert tail.count("\tlsl\tr1, r1, #16\n") == 1, "second-block lsl count"
tail = tail.replace("\tlsr\tr1, r0, #16\n", "\tlsr\tr2, r0, #16\n")
tail = tail.replace("\tlsl\tr1, r1, #16\n", "\tlsl\tr1, r2, #16\n")
s = parts[0] + "bl\t__modsi3" + parts[1] + "bl\t__modsi3" + tail
open(sys.argv[2], "w").write(s)
print("w41a patch applied (lsr-fold + second-modsi3 r2 copy)")
