# Wave 17 Worker C Match Notes (2026-10-22)

## Matched (16)

### ChipInit family (10)
All wrap Node_PopAndInit + Vec2_SetMirrored. Two sub-families:
- **6-param** (0x0801aa70 arg6, 0x0801b98c arg8, 0x0801cd50 arg10): `(u8 a,u8 b,u8 c,u16 d,u16 e,u8 *f)`, Node_PopAndInit(0,1,c,ARG), q[16]=a, q[17]=b, q[18]=0, Vec2(d,e), IncU8_12(f), n[44]=f. 92 B.
- **5-param** (0x0801ebf0 arg15, 0x0801e990 arg14): `(u8 a,u8 b,u8 c,u16 d,u16 e)`, Node_PopAndInit(0,1,c,ARG), q[16]=a, q[17]=b, q[18]=0, Vec2(d,e). No IncU8_12, no n[44]. 82 B.
- **78 B variant** (0x0801ab94 arg7, 0x08017a44 arg4, 0x0801bbb4 arg9): `(u8 a,u8 b,u16 c,u16 d,u8 *e)`, Node_PopAndInit(0,1,b,ARG), q[16]=a, q[17]=0, q[18]=0, Vec2(c,d), IncU8_12(e), n[44]=e. No +120 stores.
- **0x080178a8** (84 B): `(u8 a,u8 b,u16 c,u16 d,u8 *e)`, Node_PopAndInit(0,1,b,3), p[0]=c, p[1]=d (u16*(n+120)) BEFORE q stores, then Vec2, IncU8_12, n[44]=e.
- **0x0801709c** (40 B): `(u8 a)`, Node_PopAndInit(0,0,0,0) leaf, q[16]=a, q[17]=0, *(q+40)=0.

### Table functions (4)
- **0x0804a2dc** (70 B, main): TblState_0804A2DC. Pool 0x0200BD10. `int v` (not u16) avoids lsl/lsr. `goto Lend` → `b.n` shared epilogue.
- **0x080112fc** (248 B, main): Search_080112FC. Flag-init loop `if (a+3==i)` (plain, defeats LICM). Table walk with goto adv/loop. Negative-s8: `(u16)(-(s8)p[x])` (reload+negate) forces movs+ldrsb+negs.
- **0x080113f4** (194 B, main): TableWalk_080113F4. Same walk, returns u8*.
- **0x08025a10** (84 B, main): F_08025A10. TblLookup_25730 + SumStrides/AddTbl compare. **Idiom**: declare u16-returning callees as u32 to AVOID (u16) extension when ROM lacks lsl/lsr (inverse of wave16 int-decl).

### old_agbcc (2)
- **0x080254e0** (66 B, old): F_080254E0. GetMaskedByte/Append. old_agbcc fixes regalloc.
- **0x0802541c** (70 B, old): F_0802541C. F_0802533c loop + Fill_253BC. old_agbcc.

## Blocked (6)
- **0x08002300** (330 B): VRAM blitter. 287 diff bytes (old). Prologue reg-alloc divergence.
- **0x0800d800** (468 B): Setup. ROM s→r5/hi4→r4; pin achieves alloc but agbcc rejects `__asm__` stmts / pinned-reg assignments with stack args.
- **0x08043918** (180 B): Dispatch. Stride→r7/r5val→r5; pinning interferes with (u8)/(u16) conversions.
- **0x0800dde4** (192 B): RGB555 blender. 146 diffs, structural (dst/mask r8/r9 swap).
- **0x0802583c** (80 B): c→r4 alloc needs pin; pin causes shift-before-copy vs ROM copy-then-shift; agbcc rejects separate pin assignment.
- **0x08009f78** (74 B): a→r4 alloc; pin causes weird codegen.

## Deferred (large)
- 0x08006ad8 (768 B), 0x080439d8 (184 B, same as 43918), 0x08006374 (420 B), 0x0803643c (438 B), 0x080405d8 (180 B, same as 43918).

## New idioms
1. Harness: dedup repeated bl targets in auto-mapping (`awk '!seen[$2]++'`).
2. `int v = TblValidate()` (not u16) → plain `adds`, no lsl/lsr.
3. `goto Lend` at end → `b.n` shared epilogue.
4. Plain `a+3==i` defeats LICM; `(u16)(a+3)` triggers hoisting.
5. Negative-s8: `(-(s8)p[x])` reload+negate.
6. u32-decl for u16 callee to AVOID extension (inverse idiom).
7. agbcc: `__asm__` stmts / pinned-reg assignments fail with stack args (also fails with 3 params for separate assignment).
