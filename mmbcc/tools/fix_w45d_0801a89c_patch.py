#!/usr/bin/env python3
"""Wave 45 landing: .s patch for w45d_0801a89c (0x0801a89c, 272 B).

Coordinator-SANCTIONED instruction-order-swap patch (Wave 45).
Worker D's raw C (old_agbcc) builds 272 B with exactly 10 differing
bytes at two sites; C-only steering was exhausted (v2/v4 regressions,
main 26 diffs, old -Os same 10). Both sites are swaps of two adjacent
instructions with disjoint register footprints; neither touches memory;
the adds flag result is dead (next flag consumer is none before the bl,
and bl does not depend on flags); r0/r1 hold the same values at the bl
in both orders. Semantically identical by the same argument the Wave 43
coordinator accepted for 0x0803ff80 (single add moved across a
chip-extension pair). Difference vs 3ff80: two sites instead of one,
and the c0 site additionally moves the shared adds out of the .L13
block into the predecessor, so c0's branch retargets from the shared
adds to the bl directly — the executed instruction sequence is
identical modulo the order of the two independent setup instructions.

Site c0 (+126..+131), built:
  mov r1, #1 / b .L13 (.L13 = shared adds; pad .align follows)
ROM:
  add r0, r4, #0 / mov r1, #1 / b .L13b (directly to the bl)
Site c1 (+160..+163), built:
  mov r1, #2 / (.L13:) add r0, r4, #0 / bl ChipSlot_IncUse
ROM:
  add r0, r4, #0 / mov r1, #2 / bl ChipSlot_IncUse
The .L13b label is placed immediately before the bl; c1 falls through
into it exactly as ROM falls through into the bl. Total size unchanged
(272 B): the patched c0 tail is 6 bytes, so the following .align emits
nothing (position already 4-aligned).
"""
import sys

s = open(sys.argv[1]).read()

OLD_C0 = "\tmov\tr1, #1\n\tb\t.L13\n"
NEW_C0 = "\tadd\tr0, r4, #0\n\tmov\tr1, #1\n\tb\t.L13b\n"
OLD_C1 = "\tmov\tr1, #2\n.L13:\n\tadd\tr0, r4, #0\n\tbl\tChipSlot_IncUse\n"
NEW_C1 = "\tadd\tr0, r4, #0\n\tmov\tr1, #2\n.L13b:\n\tbl\tChipSlot_IncUse\n"

assert s.count(OLD_C0) == 1, f"c0 block count={s.count(OLD_C0)} (expected 1)"
assert s.count(OLD_C1) == 1, f"c1 block count={s.count(OLD_C1)} (expected 1)"
assert s.count(NEW_C0) == 0, "ROM-order c0 block already present; refusing to double-patch"
assert s.count(NEW_C1) == 0, "ROM-order c1 block already present; refusing to double-patch"
assert s.count(".L13") == 2, f".L13 references={s.count('.L13')} (expected 2: branch + label)"
s = s.replace(OLD_C0, NEW_C0)
s = s.replace(OLD_C1, NEW_C1)
open(sys.argv[2], "w").write(s)
