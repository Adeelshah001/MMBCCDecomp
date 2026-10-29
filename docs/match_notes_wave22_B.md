# Wave 22-B Match Notes (Worker B — recomputed leaves-up layer)

## Layer
Generated `docs/gen_wave22_layer.py` from `gen_wave21_layer.py` (same algorithm:
unmatched, unblocked, not otherwise registered, not excluded functions whose
bl-callees ALL resolve to MATCHED; exclude LEAVE_ALONE {0x0800DD08, 0x0804DC00,
0x080004FC, 0x0800D9FC} and the 4 xref-incomplete L1 dispatchers {0x08036A14,
0x08036DAC, 0x08039058, 0x080493EC}; sort by distinct-caller count desc, then
size asc). Output `docs/wave22_layer.tsv`: **88 candidates**, 2 newly enabled
by wave 21 (w22_new_cal>0).

## Matched (3)

### 0x0800ED20 (34 B) — Setup10308_Flag15_0800ED20, main agbcc
Setup_08010308 wrapper: if the setup returns 1, store 15 into byte 0x20 of
0x02005130 (SetByte20_0800E1F0) and return 1; otherwise return the setup's s8
result. Twin of 0x0800ECF8. Newly enabled by wave 21 (Sub_08010308).
Landed: src/w22b_0800ed20.c. Explicit `.byte 0,0` pad (GAS would emit c046).

### 0x0800ECF8 (38 B) — Setup10270_Flag14_0800ECF8, main agbcc
Setup_08010270 wrapper: if the setup returns 1, store 14 into byte 0x20 of
0x02005130 and return 1; otherwise return the setup's s8 result. Twin of
0x0800ED20. Newly enabled by wave 21 (F_08010270).
Landed: src/w22b_0800ecf8.c. Explicit `.byte 0,0` pad.

**Idioms (both):** codegen-shaped callee externs ((u32,u32,s16,s8)->u32 and
(u8,u32,u8,s8)->u32, ABI-identical to the real defs); interwork epilogue
(`pop {r1}; bx r1`) — the `noiw` variant was tried first and gives `pop {pc}`,
which is wrong here.

### 0x0802493C (124 B) — F_0802493C, old_agbcc
Index validator: `if (a > 29) return 1;`
`q = *(u32 *)(p+20) + (*(u8 *)(*(u32 *)(p+20) + 432)) * 144;`
`r1 = CheckPair_258D8(q, a); if (r1 == 0) return 0; if (r1 == 2) return 5;`
`r2 = GetStride4Byte20(q, a); Clear20_Set21_FF(q, a); Sub_254E0(p, r2);`
`return 0`.
Landed: src/w22b_0802493c.c.

**Idioms:** old_agbcc register allocation (r2 = base+432, r4 = byte);
separate r1/r2 result variables so the CheckPair result stays in r0 (not live
across the next block) while the GetStride result goes to r4 (callee-saved,
live across Clear20_Set21_FF); `(216 << 1)` materializes 432 as `movs`+`lsls`;
recomputed q blocks (no base temp — ROM reloads `*(p+20)` each time).
**Drive-by:** the live symbol at 0x080254e0 is `Sub_254E0` (w17d, 66 B);
the registry's `F_080254E0` (w17c) is superseded and its section is
/DISCARD/ed — extern uses the real matched name per nm hygiene.

## Deferred (with analysis)

### 0x08006374 (420 B, 4 callers) — 377 diffs
Complex tiled rect-fill validator (FillRect). Natural first pass diverged at
byte 16: ROM processes args in order p→r9, d→r0, e→r4, f→r5, g→r7, then spills
a/b/c; my C's order differs. The function has intricate fixed-point loops
(Bresenham-style with `(x<<24)+0x10000>>24` idiom). Needs prologue scheduling
work. Staging: staging/wave22_B/w22b_08006374.c.
Sibling family: 0x08006AD8 (768 B), 0x08007134 (480 B), 0x080065BC (416 B) —
all share the FlagA_8610/8628/8654/8680 + SetIfXZero callee family; matching
one unlocks sibling-shape transfer for the others.

### 0x080097CC (122 B, 2 callers) — prologue scheduler
4× Memcpy16 tile blitter. Structure solved (bytes 0–97 of body match in one
variant), but the prologue extend order is stubborn: ROM emits
`lsls r0,#24; lsls r1,#16` (a, b) BEFORE `lsls/lsrs r4,#16` (c),
`lsls/lsrs r3,#24` (d), `lsls r2,#24; lsrs r2,#19` (e); agbcc (both main and
old) insists on c,d[,e] before a,b regardless of C statement order, barriers,
or temporary layout. The `(u8)e << 5` → `lsl#24/lsr#19` pattern confirmed via
isolated test. Needs a new idiom for forcing arg-extend order.
Staging: staging/wave22_B/w22b_080097cc.c.

### 0x08026184 (126 B, 2 callers) — 68 diffs
Fill/Append initializer with u16 copy loop. Prologue matched via pinning
(q→r5), but the loop increment `(r4<<16)+0x10000` idiom and strh block
allocation remain. Staging: staging/wave22_B/w22b_08026184.c.

### 0x080263A4 (138 B, 2 callers) — 90 diffs
Validation function (TblGet11). Prologue matched; control-flow structure
(single `return 1`/`return 0` blocks with gotos) close but branch targets
diverge due to layout. Staging: staging/wave22_B/w22b_080263a4.c.

### 0x08007728 (74 B, 1 caller) — 35 diffs
Config byte stores with NodeInit_08022FB0. Register allocation (r4=a, r5=b,
r6=c) not achieved; compiler uses r7. Staging: staging/wave22_B/w22b_08007728.c.

### Not attempted (time-box)
0x08006AD8 (768 B, 6 callers), 0x0803643C (438 B, 4 callers, mid-function
pools), 0x08045838 (216 B, 3 callers; 21-D deferred at 129 diffs),
0x08007134 (480 B), 0x08046DF8 (832 B) — big-family members; 0x08010F34 etc.
smaller rows unattempted.

## New Idioms for Catalog
1. **Interwork epilogue check** — `push {lr}` + `pop {r1}; bx r1` means main
   agbcc (interwork); `pop {pc}` means no-interwork. Try main first for
   wrappers.
2. **Separate result variables** — when one call result is live across later
   calls and another is not, use distinct C variables so the allocator keeps
   the live one in a callee-saved reg and the dead one in r0.
3. **`(216 << 1)` for 432** — materializes as `movs r6,#216; lsls r6,#1`
   instead of a pool load.
4. **Recomputed address blocks** — when ROM reloads a base pointer before each
   use, wrap each use in its own block with no shared temp.

## Evidence
- Standalone 0-diff: staging/wave22_B/w22_verify.sh (extended w16c_verify.sh
  with main/old/main_f/old_f/noiw/old_noiw variants).
- Full-build regions byte-identical: 0x0800ED20 (36 B incl. pad), 0x0800ECF8
  (40 B incl. pad), 0x0802493C (124 B). Build green at 8,388,608 bytes.
- Registry: 3 MATCHED rows appended (wave=22).
