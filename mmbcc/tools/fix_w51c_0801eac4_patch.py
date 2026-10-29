#!/usr/bin/env python3
"""Wave 51 landing: .s patch for w51c_0801eac4 (0x0801eac4, 268 B).

Coordinator-SANCTIONED single-site register-field patch (Wave 51).
Worker's raw C (old_agbcc -O2 -mthumb-interwork) builds 268 B with
exactly 2 differing bytes at one site (+176/+178), personally verified
by the coordinator from built + ROM disassembly:

- +176/+178: second-arg load temp r0 -> r3.
  OLD: ldrb r0, [r5, #0] / lsrs r2, r0, #4
  NEW: ldrb r3, [r5, #0] / lsrs r2, r3, #4
  (Wave 42/48 register-field class: the temp is read ONLY by the
  shift; its value in r2 is identical in both versions; in the built
  version r0 is overwritten by `adds r0, r4, #0` at +178 before any
  read; in ROM r3 is overwritten by `ldrb r3, [r2, #0]` at +186
  (0x0801ebaa) before any read — no read of r3 between the site and
  that overwrite in either version. ldrb touches no flags; the lsrs
  sets flags identically. Call args at the following bl (r0 = r4,
  r1 = orrs result, r2 = shifted value) are identical; instruction
  count unchanged; no pool word changes; no branch retargets. Entry
  state identical and all other bytes byte-exact, so patched state
  converges to ROM's at the site.)

This sanction is for this ONE window in 0x0801eac4 ONLY. It does NOT
extend to any other function or site.
"""
import sys

inp, outp = sys.argv[1], sys.argv[2]
text = open(inp).read()

OLD = ("\tldrb\tr1, [r5, #1]\n"
       "\torr\tr1, r1, r0\n"
       "\tldrb\tr0, [r5]\n"
       "\tlsr\tr2, r0, #4\n"
       "\tadd\tr0, r4, #0\n"
       "\tbl\tSub_0800D6E0\n")
NEW = ("\tldrb\tr1, [r5, #1]\n"
       "\torr\tr1, r1, r0\n"
       "\tldrb\tr3, [r5]\n"
       "\tlsr\tr2, r3, #4\n"
       "\tadd\tr0, r4, #0\n"
       "\tbl\tSub_0800D6E0\n")

count = text.count(OLD)
assert count == 1, f"OLD block found {count} times, expected exactly 1 — aborting before write"
text = text.replace(OLD, NEW)
open(outp, "w").write(text)
print(f"patched 1 site (OLD block asserted exactly once)")
