# Wave 20 Worker B — Match Notes

## Matched (3)

| Address | Name | Size | Compiler | Notes |
|---------|------|------|----------|-------|
| 0x0801dfc4 | NewNode_0801DFC4 | 98 | main + FIXALIGN1 | Node_PopAndInit(0,0,0,13); r8 spill for param a; F_0801E87C call |
| 0x08021d10 | BuildList_08021D10 | 114 | main + custom pool sed | Linked-list builder; guard *(s16 *)(*(u8 **)0x020066f0+10) > 5 |
| 0x08024bc8 | Sub_08024BC8 | 76 | old_agbcc | TblLookup_25730 / F_08025A10 wrapper; inline address computation |

All three were flagged targets from Wave 19-B. Coordinator-verified 0-diff in full build.

## New Idioms

### Natural u8 temp defeats pinning-suppression (0x0801dfc4)
`register u8 ra __asm__("r8") = (u8)a;` drops the `lsls r0,r0,#24; lsrs r0,r0,#24`
truncation (compiler proves high bits dead via strb-only use). Fix: route
through a natural temp first:
```c
u8 ta = (u8)a;
register u8 ra __asm__("r8") = ta;
```
The natural temp forces the truncation shifts, then the pinned copy emits
`mov r8, r0`. (Extends Wave 19 "Pinning suppresses u8 truncation shifts" idiom.)

### Pin one variable to force another's register (0x08021d10)
Natural allocation put `i` in r4 and `prev` in r5; ROM has them swapped
(i=r5, prev=r4). Pinning BOTH disrupted codegen, but pinning ONLY `prev`
to r4 forced `i` into r5 naturally:
```c
register u8 *prev __asm__("r4");
// u16 i; (natural -> r5)
```

### Mid-function pool via explicit .short nop (0x08021d10)
The literal pool at +0x14 needs 4-byte alignment. Its `.align 2,0` forces
4-byte SECTION alignment → 2-byte trailing pad (116 B vs 114 B ROM).
FIXALIGN1-extended (replace all with `.align 1,0`) breaks the `ldr`
(assembler can't verify word alignment). Fix: replace pool's `.align 2,0`
with `.short 0x0000` (explicit 2-byte nop). Pool stays at 0x14 (4-aligned
by construction); section alignment drops to 2; no trailing pad.
Makefile:
```make
sed -i '0,/\.align[[:space:]]*2, 0/s//.align 1, 0/' $(@:.o=.s)
sed -i 's/^\t\.align\t2, 0$$/\t.short\t0x0000/' $(@:.o=.s)
```
(Assembler warns "section does not have enough alignment" — harmless;
ldscript places section at 4-aligned address.)

### old_agbcc for register allocation (0x08024bc8)
Main agbcc allocated r2/r1/r2 for the address computation; ROM has
r1/r2/r3. old_agbcc gives the ROM allocation exactly. When register
allocation differs and pinning disrupts, try the other compiler version.

## Attempted / Parked

### 0x08011a78 (78 B) — parked
Control flow and structure matched, but 59 diffs due to AND operand order
(`and r0,r0,r6` vs ROM's `ands r0,r1` with `adds r0,r6,#0` first) and 2-byte
size difference (76 vs 78). Needs different expression shape for the
`(8 & *(base+10))` test.

### 0x08010f34 (84 B) — parked
Bit-test and structure matched, but pool handling differs: ROM uses single
pool entry + `adds r1,r2,#0; adds r1,#24`; attempts either used two pools
or modified r2 directly (`add r2,r2,#24`). Needs a way to force the
copy-then-add pattern while keeping single pool.

### 0x0801029c (86 B) — parked
r8/r9 pins and structure matched, but last store uses `add r4,r4,#65`
(modifying base) vs ROM's `adds r0,r4,#0; adds r0,#65; mov r1,r8`
(preserving base). 30 diffs, 84 vs 86 bytes.

### 0x08002cb0 (78 B) — not attempted
Pools located outside function bounds (0x8002d00+); PC-relative loads
reference absolute addresses. Requires special harness handling.

## Unattempted (70 remaining)
0x08010ec4, 0x0804af20, 0x08011e20, 0x08026740, 0x08016e84, 0x08016efc,
0x0800e440, 0x0800e748, 0x08042ae4, 0x080097cc, 0x0802493c, 0x08026184,
0x080263a4, 0x0800a6bc, 0x0801e174, 0x0801f254, 0x08020b60, 0x08003fc8,
0x0801bf10, 0x0801fcd0, 0x080482d8, 0x08042c04, 0x080405d8, 0x080439d8,
0x080460c0, 0x0801c56c, 0x0800571c, 0x0802d6e0, 0x080291ec, 0x0800e2cc,
0x080224e4, 0x08021b3c, 0x0801b0dc, 0x08002a1c, 0x0801c030, 0x08045838,
0x0803f844, 0x08046810, 0x0804a1f0, 0x0802298c, 0x08045914, 0x0803ad48,
0x08041890, 0x080046b0, 0x0803ac4c, 0x080096bc, 0x08006fe8, 0x0801c428,
0x08049560, 0x0800ac8c, 0x080203e0, 0x08001f1c, 0x08002070, 0x0804d8a8,
0x08034f2c, 0x08007840, 0x0803aaa8, 0x080065bc, 0x08006374, 0x0803643c,
0x080176ac, 0x08025ec8, 0x08007134, 0x08009c7c, 0x080099fc, 0x0801e208,
0x08006ad8, 0x080471d8, 0x08046df8, 0x08008bc8, 0x08010308, 0x080259a4,
0x08004998.

## Coordinator addendum — FIXALIGN1 sed-pattern audit (2026-10-23)

Worker B reported the Makefile pattern `s/\\.align\\s*2, 0/.align 1, 0/` "does not work (the \s fails)" and used `[[:space:]]` instead for the w20b_08021d10 rule. **Audit result: the existing pattern works correctly in this environment.** GNU sed interprets `\s` in BRE (verified: `\t.align\t2, 0` → `\t.align 1, 0`, both tab and space variants). Clean rebuild of all 5 pre-existing sed-pattern rules (w18d_0801f1a8/w18d_080203a4/w18d_0801ee14/w19c_08017620/w19c_08017d00) produced exact sizes (46/58/82/78/78 B) with 2**1 section alignment — FIXALIGN1 behavior intact. The worker's negative test was almost certainly a double-escape artifact (testing `\\.align\\s*` directly in bash passes a literal backslash to sed, matching nothing). Do NOT "fix" the existing patterns — they are correct. (The `[[:space:]]` variant used for w20b_08021d10 is also correct and harmless.)
