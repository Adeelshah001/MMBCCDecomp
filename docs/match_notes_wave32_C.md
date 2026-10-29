# Wave 32-C Notes

Worker C, 2026-10-24. Staging: `staging/wave32_C/`. Verify harness: `staging/wave32_C/verify.sh`
(adapted from wave31_C; `old` = old_agbcc, `main` = agbcc, both `-O2 -mthumb-interwork`).

## MATCHED (2) — staged, DO-NOT-LAND (coordinator lands)

### 1. 0x080249B8 TblPairSwap_080249B8 — 0 diffs, main agbcc
- **File:** `staging/wave32_C/w32c_080249b8_MATCHED.c`
- **True extent:** 0x080249B8–0x08024A30 = 120 B (118 code + 2 pad), verified vs ROM bytes.
- **Registry:** MATCHED row appended (checked all rows first — no prior row).
- **Behavior:** `if (a > 29 || b > 29) return 1; q = *(p+20) + (*(u8 *)(*(p+20)+432)) * 144;`
  `if (CheckPair_258D8(q,a) || CheckPair_258D8(q,b)) Tbl_SwapAndUpdate_080259A4(q,a,b); return 0.`
  Two-index pair check + swap-and-update dispatch; sibling of F_0802493C.
- **Decisive idioms:**
  - Goto shape for ROM branch layout (`if (call) goto upd; if (!call) goto ret0; upd: ...; ret0: return 0`)
    giving `bne`/`beq`/fall-through (the `||` and nested-if shapes added a branch).
  - **Triple block-scoped pin** defeats gcc's temp rotation (`r7/r1/r2` → ROM `r1/r2/r3`):
    `register u32 c432 __asm__("r1") = (216 << 1);`
    `register u8 *e __asm__("r2") = q + c432;`
    `register u8 t __asm__("r3") = *e;`
    → `movs r1,#216; lsls r1,r1,#1; adds r2,r0,r1; ldrb r3,[r2]; lsls r1,r3,#3; ...`
    Pure C — the brief's anticipated `.s` post-process patch was NOT needed.
  - Sibling q-computation idiom (`u8 t = *(q + (216 << 1)); q + (u32)t * 144`); recomputed q blocks.
- **Landing note:** Makefile rule needs the bx-r1 pad sed:
  `sed -i 's/^\tbx\tr1$$/\tbx\tr1\n\t.short\t0x0000/' $(@:.o=.s)`
  (GAS emits `46c0` nop to 4-align the 118-B section; explicit `.short` keeps ROM's 2 zero pad bytes.)

### 2. 0x0802D574 Lookup_02D574 — 0 diffs, old_agbcc
- **File:** `staging/wave32_C/w32c_0802d574_MATCHED.c`
- **True extent:** 0x0802D574–0x0802D5A8 = 52 B (50 code + 2 pad), verified vs ROM bytes.
- **Registry:** MATCHED row appended (only prior row was W8-M BLOCKED — no duplicate).
- **Behavior:** branch-chain lookup: `v==2 → 4`, `v==3 → 1`, `v==4 → 3`, `v==1 → 2`, else `255`.
- **Decisive idioms:**
  - Goto form reproduces ROM's `beq`/`bgt`/`beq` branch layout (if/else chain gave `bne`/`bls`).
  - Block-scoped pins `register s32 v2 __asm__("r1") = v;` + `register u32 r __asm__("r2") = 255;`
    — pins do **not** cause a `push {lr}` frame under old_agbcc (they did under main agbcc).
  - `s32 v = (u8)a0;` — signed variable with u8 mask gives `bgt` for `v > 2`
    (plain `u8 v` gave `bhi`; `(s32)v` cast folded).
  - Declaration order = emission order: `v2` before `r` so `adds r1,r0,#0` precedes `movs r2,#255`.
  - `if (v > 2)` uses r0 (v); inner `v2 == 3/4` uses r1 — matches ROM's register split.
- **Landing note:** Makefile rule needs the bx-lr pad sed:
  `sed -i 's/^\tbx\tlr$$/\tbx\tlr\n\t.short\t0x0000/' $(@:.o=.s)`

## DUPLICATE — not claimed (registry already MATCHED)

### 0x08004998 HexFormat_08004998 — pure-C alternative to W25-B's patch version
- Registry already has W25-B MATCHED (`mmbcc/src/w25b_08004998.c`, "main agbcc + python patch").
  **No new registry row appended** (duplicate rule).
- **Pure-C 0-diff version staged:** `staging/wave32_C/w32c_08004998_v27.c`
  (108 B incl pool, main agbcc, 0 diffs, NO post-process patch).
  Coordinator may consider swapping it in to drop the python patch dependency.
- **New idioms proven here:**
  - **Pool-const pin with initialization** (`register u32 poolr __asm__("r1") = 0xFFFF0000u;`)
    forces the literal-pool load into r1 — supersedes W22-D "pinning ignored for constants".
    With the pool pinned (no r7 denial needed), c naturally lands in r7, breaking the
    W24-D catch-22 (denying r7 for the pool prevented c→r7).
  - **Combiner-defeating mask:** `register u32 dm __asm__("r0") = d;` +
    `__asm__ volatile("" : "+r" (dm));` forces gcc to materialize the u16 mask
    (`lsls r3,r3,#16; lsrs r0,r3,#16`) instead of folding it into the shift.
    (Non-volatile barrier also works in probes but perturbs allocation in real functions;
    volatile barrier on a pinned reg is safe.)
  - **Explicit copy asm:** `__asm__ volatile("add %0, %1, #0" : "=r" (tmp) : "r" (d16));`
    forces the redundant `adds r0,r2,#0` that empty `"+r"` barriers wouldn't emit.
  - Unpinning `tmp` (leaving it unpinned) let gcc choose r0 and emit ROM's
    `mov r3,sp; adds r1,r3,r0` for `&buf[tmp]`.
- Path: v7 (pool pin → c in r7!) → v13–v22 (mask folding fights) → v23 (5 diffs) →
  v24 (prologue perfect) → v27 (0 diffs).

## STILL BLOCKED

### 0x08042A64 sub_08042A64 (twin 0x080459F8) — best 39 diffs
- Bounds/overlap check, 100 B true extent (0x08042A64–0x08042AC8) with 8-B pool inline
  at 0x08042AB8 (mid-function — pool-barrier mechanism relevant).
- ROM: b→r4, d→r5, base→r7, sa→r6; pools 0x02007036, 0x0000ac11.
- Tried: W8-L base (58 diffs, good alloc via `gBase042A64` extern but b1 loaded twice +
  3rd pool word for 0xac12); v1 (39 diffs, single-b1 + `off++`, but base pin→r7
  conflicted with b→r7); v2–v6 (raw-constant/`gAddrZero`/pin variants — base lands
  in ip, or pin breaks the push, or b→r6).
- **Walls:** (1) `off++` reuse (`adds r2,#1`) vs separate 0xac12 pool word — needs the
  offset as a live variable without perturbing base→r7; (2) pinning base→r7 marks r7
  fixed so gcc drops it from the push; (3) mid-function pool placement (2 words at
  0x08042AB8, not trailing).
- Staged attempts: `w32c_08042a64_v1.c` … `w32c_08042a64_v6.c`, `w32c_08042a64_base.c`.

## Idiom catalog additions
- Triple block-scoped pin for temp rotation (c432→r1, e→r2, t→r3) — pure-C alternative
  to `.s` post-process patches for scheduler reorder walls.
- Pool-const pin must INITIALIZE at declaration (`= CONST`); separate assignment folds.
- `s32 v = (u8)a0` for signed branches on masked values (keeps `lsl/lsr`, gives `bgt`).
- Pins are compiler-sensitive: r1/r2 pins caused `push {lr}` under main agbcc but are
  clean under old_agbcc (0x0802D574).
- `__asm__ volatile("add %0, %1, #0" : "=r" (dst) : "r" (src))` forces a redundant
  register copy that empty barriers won't emit.
- `__asm__ volatile("" : "+r" (x))` after a u16→u32 conversion forces the mask to
  materialize (defeats combiner folding); non-volatile variant works in probes but
  perturbs real-function allocation.
