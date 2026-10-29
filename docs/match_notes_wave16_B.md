# Wave 16 Worker B notes — leaves-up rows 0-55 (2026-10-22)

## MATCHED (15, coordinator-verified 0-diff)

| Address | Name | Size | Compiler | Source |
|---------|------|------|----------|--------|
| 0x08017000 | Node_PopAndInit | 132 B | main agbcc | src/w16b_08017000.c |
| 0x08020ed4 | Node_PopAndInit_20ED4 | 132 B | main agbcc | src/w16b_08020ed4.c |
| 0x0804580c | CountNonzeroStride | 44 B | main agbcc | src/w16b_0804580c.c |
| 0x08025754 | SumStrides_25754 | 60 B | main agbcc | src/w16b_08025754.c |
| 0x08024434 | Dispatch_24434 | 124 B | main agbcc | src/w16b_08024434.c |
| 0x08025054 | Fwd_25054 | 28 B | main agbcc | src/w16b_08025054.c |
| 0x08010ba0 | Fwd_10BA0 | 20 B | main agbcc | src/w16b_08010ba0.c |
| 0x080467dc | Count_467DC | 52 B | main agbcc | src/w16b_080467dc.c |
| 0x0800ea30 | Set_0EA30 | 28 B | main agbcc | src/w16b_0800ea30.c |
| 0x0800ebf0 | Fwd_EBF0 | 36 B | main agbcc | src/w16b_0800ebf0.c |
| 0x0801ab34 | Sub_1AB34 | 64 B | old_agbcc | src/w16b_0801ab34.c |
| 0x080253bc | Fill_253BC | 60 B | main agbcc | src/w16b_080253bc.c |
| 0x080257fc | Sub_257FC | 64 B | main agbcc | src/w16b_080257fc.c |
| 0x0802666c | Sub_2666C | 64 B | main agbcc | src/w16b_0802666c.c |
| 0x080266ac | Sub_266AC | 68 B | main agbcc | src/w16b_080266ac.c |

## New idioms
- **register __asm__("r7") pinning miscompiles on agbcc**: silently uses uninitialized r7. Fix: leave 4th callee-saved param unpinned; allocator naturally places it in r7.
- **u16 increment idiom**: `t = ((u32)i << 16) + 0x10000; i = t >> 16;` reproduces ROM's `lsls/movs#128+lsls#9/adds/lsrs` (plain `i++` gives simple `adds`).
- **Absolute-base-to-local**: `u8 *base = RomBase; … base + 24` as separate statement defeats pool constant folding.
- **Pool-load hoisting**: assigning table base to a local before use forces ROM's early `ldr r1,[pc]` ordering.
- **Widened int temps**: `int v = -113; v &= *p;` yields `movs #113; negs`.
- **old_agbcc for register allocation**: 0x0801ab34 needed old_agbcc.

## Blocked (3)
- **0x08002300** (330 B): 41 diffs (old_agbcc). Count init coalescing; third loop field8 reload reg.
- **0x08016e0c** (64 B): 34 diffs. Instruction scheduling (adds before lsls/lsrs).
- **0x080254e0** (66 B): 38 diffs. Scheduling; needs 3 callee-saved regs.

## Skipped
- **0x0804a2dc**: INTERIOR (registry).
