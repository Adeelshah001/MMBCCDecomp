#!/usr/bin/env python3
"""Wave 43 landing: .s patch for w43a_0803ff80 (0x0803ff80, 220 B).

Coordinator-sanctioned instruction-order-swap patch (Wave 43).
Worker A's raw C (old_agbcc) builds 220 B with exactly 6 differing
bytes at prologue +6..+11: the compiler emits `add r5, r2, #0` AFTER
the chip-extension pair, ROM has it BEFORE. The patch moves only that
one 2-byte instruction above the 4-byte pair:
- BEFORE (compiler): lsl r1, r1, #16 / lsr r4, r1, #16 / add r5, r2, #0
- AFTER (ROM):      add r5, r2, #0 / lsl r1, r1, #16 / lsr r4, r1, #16
Semantic equivalence (coordinator re-read the ROM disassembly):
the two groups have disjoint register footprints (X reads r2 writes
r5; Y reads r1 writes r1/r4), neither touches memory, the adds flag
result is dead (overwritten by lsls/lsrs/movs, then by the cmp before
the first branch bgt at +0x14), and r5 is first read at +0x68
(cmp r5, r0). Identical for all inputs. C-only steering was exhausted
across Waves 42-43 (both compilers, -O2/-Os, statement/declaration
order, barriers). See staging/w43a_decisions/w43a_0803ff80_sanction_case.md.
"""
import sys

s = open(sys.argv[1]).read()

OLD = "\tlsl\tr1, r1, #16\n\tlsr\tr4, r1, #16\n\tadd\tr5, r2, #0\n"
NEW = "\tadd\tr5, r2, #0\n\tlsl\tr1, r1, #16\n\tlsr\tr4, r1, #16\n"

assert s.count(OLD) == 1, f"compiler-order block count={s.count(OLD)} (expected 1)"
assert s.count(NEW) == 0, "ROM-order block already present; refusing to double-patch"
s = s.replace(OLD, NEW)
open(sys.argv[2], "w").write(s)
