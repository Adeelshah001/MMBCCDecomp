# Wave 16 Worker D notes — blocked revisits (2026-10-22)

## MATCHED (6, coordinator-verified 0-diff)

| Address | Name | Size | Compiler | Source |
|---------|------|------|----------|--------|
| 0x0803618c | ResetStateBlock_3618c | 80 B (68+12 pool) | main agbcc | src/w16d_0803618c.c |
| 0x08005fc0 | ObjSlotInit_05FC0 | 84 B (80+4 pool) | main agbcc | src/w16d_08005fc0.c |
| 0x08021e64 | ObjInit_21E64 | 112 B (100+12 pool) | old_agbcc | src/w16d_08021e64.c |
| 0x0804c7b4 | TblLookup_0804C7B4 | 52 B (44+8 pool) | main agbcc | src/w16d_0804c7b4.c |
| 0x08027c84 | RecInit_08027C84 | 48 B (36+12 pool) | main agbcc | src/w16d_08027c84.c |
| 0x0802fd68 | F_0802FD68 | 56 B | main agbcc | src/w16d_0802fd68.c |

## New idioms (decisively applied)
- **Tied-opaque pool anti-folding** (3618c, 4C7B4, 27C84): `__asm__ volatile("" : "=r"(x) : "0" (CONST))` defeats constant folding into pool words.
- **Volatile-barrier shift/pool interleaving** (4C7B4): `(u32)idx<<16`, tied-opaque pool loads, then `>>=13` reproduces ROM's `lsls/ldr/ldr/lsrs` interleave.
- **Divided-syntax `add %0,%0,%1`** forces `adds` operand order (05FC0, 4C7B4, 27C84, 21E64).
- **Opaque zero defeats r5 zero-CSE** (21E64): tied empty asm with input `0` gives fresh `movs r0,#0` per store; push drops to `{r4,lr}`.
- **Late-assigned `u16 zero` pins r4** (3618c); **scoped `int one`** forces `movs r3,#1` before `ldrb` (05FC0, 21E64 two-step OR via int temp defeats `2|1` folding).
- **`p += pool` keeps p in r0** (05FC0); **`(u8)a<<5` combiner-folds** to `lsls#24/lsrs#19`.
- **u32-prototype extern** forces word `ldr` when callee takes u8 (27C84).
- **Goto branch layout** reproduces `cmp/beq/cmp/beq/b` with fallthrough (2FD68).

## Still blocked (updated diffs)
- **0x0804dd9c**: NOT a function — 2-byte `mov pc,lr` (0x46F7) padding. Candidate for `BYTE()` in ldscript.
- **0x0804bfd4**: Far pools at 0x804c280/0x804c284 (680-byte pc offset) — cannot match standalone; pool distance is a TU-layout property.
- **0x0800cc24** (InitRegs): 70 diffs — `r7=0x10000` u16-increment idiom (`lsls r0,#16; movs r7,#128; lsls r7,#9; adds r0,r7; lsrs r0,#16` inside loop) resists both compilers.
- **0x08002960** (BlendMasked): 74 diffs — in-loop `push {r0,r1,r7}`/`pop` spill not reproduced; both compilers use r8/ip high registers.
- **0x080374b8 / 0x08049A08 / 0x08037600**: not attempted; regalloc blockers as previously documented (112/122/214 diffs).
- **0x080173d4** (TblSlotInit): attempted — 10–14 diffs; ROM wants `ldrb r3`, `adds r1,r1,r2`, `movs r1,#254`-before-`ldrb`. Staging: `staging/wave16_D/f173d4.c` (not claimed).
- **0x0801e14c** (SlotCopy): attempted — 8 diffs; `ldrb r2,[r4,#9]`/`adds r0,r0,r1` vs `ldrb r0`/`add r1,r1,r0`; r2 pin ignored. Staging: `staging/wave16_D/f1e14c.c` (not claimed).
