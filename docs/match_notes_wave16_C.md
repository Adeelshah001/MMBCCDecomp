# Wave 16 Worker C notes — leaves-up rows 56-111 (2026-10-22)

## MATCHED (12, coordinator-verified 0-diff)

| Address | Name | Size | Compiler | Source |
|---------|------|------|----------|--------|
| 0x0804b110 | TwoTblOps_0804B110 | 20 B | main agbcc | src/w16c_0804b110.c |
| 0x0804b954 | Flag17Init_0804B954 | 26 B | main agbcc | src/w16c_0804b954.c (fix_tail_align) |
| 0x0800ebd0 | CondSet7_0800EBD0 | 30 B | main agbcc | src/w16c_0800ebd0.c (fix_tail_align) |
| 0x08037914 | ChipFlagSet_08037914 | 64 B | main agbcc | src/w16c_08037914.c |
| 0x0801bd7c | ChipInit_0801BD7C | 104 B | old_agbcc | src/w16c_0801bd7c.c |
| 0x0802316c | ChipInit_0802316C | 100 B | old_agbcc | src/w16c_0802316c.c |
| 0x0801bea0 | ChipInit_0801BEA0 | 110 B | old_agbcc | src/w16c_0801bea0.c |
| 0x08019e0c | ChipInit_08019E0C | 112 B | old_agbcc | src/w16c_08019e0c.c |
| 0x0801962c | ChipInit_0801962C | 110 B | old_agbcc | src/w16c_0801962c.c |
| 0x0801974c | ChipInit_0801974C | 110 B | old_agbcc | src/w16c_0801974c.c |
| 0x08019a3c | ChipInit_08019A3C | 112 B | old_agbcc | src/w16c_08019a3c.c |
| 0x08011b64 | StateMachine_08011B64 | 100 B | main agbcc | src/w16c_08011b64.c |

## New idioms
1. **Double-OR constant-first anti-folding** (old_agbcc): `{ u8 b = p[10]; b = 2 | b; b = 1 | b; p[10] = b; }` — plain `(2|p[10])|1` folds to `3|p[10]`.
2. **Pinned-r0 zero defeats CSE**: `{ register u32 z __asm__("r0") = 0; *(u32 *)(p + 0x6c) = z; }`.
3. **Late pool materialization**: `register u8 *p2 __asm__("r1");` + volatile asm placed *after* shifts.
4. **`(u32)(s8)` call-result temp + early return** for bne-to-pop shapes.
5. **Int-decl callee**: declare u8-returning callee as `u32` when ROM extends with `lsls#16/lsrs#16`.
6. **Goto-ladder prevents return-merging**.
7. **Opaque `adds` copy**: `register u32 c __asm__("r1"); __asm__ volatile("" : "=r"(c) : "0"(s5));` forces `adds r1,r5,#0`.

## Blocked (5)
- **0x0801b47c** (162 B): table pattern, `lsls r2,r0,#3; adds r0,r2,r4` codegen.
- **0x080211ec** (162 B): table variant, `adds r1,r2,#4` intermediate.
- **0x0800e6d0** (120 B): pool duplication (0x02005020 twice); needs full-build check.
- **0x0803aed0** (104 B): pool placement interleave; needs full-build check.
- **0x08011ac8** (154 B): ~122 diffs; 3-state machine, nested branches diverge.
