# Wave 33-D Notes

Worker D, 2026-10-24. Staging: `staging/wave33_D/`. Verify harness:
`staging/wave33_D/verify.sh` (ADDR SIZE SEC SRC CC [SYMDEFS...]; clean-room
recompile → link at true ROM address → objcopy → cmp vs baserom at
file offset (addr − 0x08000000); non-empty asserted at every step).

## Task 1: 0x08004998 pure-C swap-in — STAGED, VERIFIED

- **Staged:** `staging/wave33_D/w25b_08004998_pureC.c` (drop-in content for
  `mmbcc/src/w25b_08004998.c`), `staging/wave33_D/04998_MAKEFILE_SWAP.txt`
  (exact Makefile before/after).
- **Verified:** 0 diffs over true extent 108 B (0x08004998–0x08004A04),
  main agbcc, NO python patch. Clean-room recompile, all steps non-empty.
- **Registry:** W25-B MATCHED row (`mmbcc/src/w25b_08004998.c`) stays — NO new
  row (duplicate rule).
- **Callee:** `DrawText_048B4` (real build symbol in `src/wave13_D_old.c`
  @0x080048B4); source updated from v27's `F_080048B4` to the real name,
  re-verified 0 diffs.
- **Makefile change:** delete the `python3 tools/patch_w25b_08004998.py`
  line; update the comment block (exact text in `04998_MAKEFILE_SWAP.txt`).
  `tools/patch_w25b_08004998.py` becomes unused — flagged, NOT deleted
  (coordinator decision).

## Task 2: Blocked revisits

### MATCHED: 0x0804C8A4 LoopSet_0804C8A4 — 72 B, 0 diffs, main agbcc
- **File:** `staging/wave33_D/w33d_0804c8a4_MATCHED.c`
- **True extent:** 0x0804C8A4–0x0804C8EC = 72 B.
- **Registry:** only prior row is W6-L4 BLOCKED — coordinator appends MATCHED.
- **Callee:** `CallVia_Mem1` (real build symbol, `src/wave4_i.c` @0x0804CA1C).
- **Wall broken (W6-L4):** ROM `adds r0,r7,#0; ands r0,r1` (mask copied to r0)
  vs C's `adds r0,r1,#0; ands r0,r7` (v copied to r0). **Explicit copy asm**
  (`__asm__ volatile("add %0,%1,#0" : "=r"(dst) : "r"(src))`) forces the
  mask→r0 copy, defeating the temp rotation — pure C, no post-process patch.
- **New finding:** the `(a & v) == 0` test after the forced copy emits ROM's
  *redundant* `ands r0,r1; cmp r0,#0` — the combiner does NOT merge the cmp
  (combiner-defeating via the opaque copy).
- **No pins:** four call-live vars (p, n, m1, m2) naturally allocate to
  r4/r5/r6/r7 with correct `push {r4-r7,lr}` prologue. (Pinning r7 would have
  broken the push — pinned r7 not saved.)
- **Declaration order = emission order:** `m1` declared inside `if (n > 0)`
  so `movs r7,#128` lands after the `ble`, matching ROM.
- Path: v1 (12 diffs, r7 pin broke prologue) → v2 (10 diffs, no pins,
  prologue fixed) → v3 (0 diffs, m1 declaration moved).

### MATCHED: 0x0804DC00 Sram_VerifyCompare — 46 B code, 0 diffs, main agbcc
- **File:** `staging/wave33_D/w33d_0804dc00_MATCHED.c`
- **True extent:** 0x0804DC00–0x08004DC30 = 48 B (46 code + 2 pad `00 00`;
  GAS emits `46c0` — standard land-time pad fix via `.short 0x0000` sed).
- **Registry:** only prior row is W0 BLOCKED (`src/sram.c`) — coordinator
  appends MATCHED.
- **Wall broken (W0):** ROM lays mismatch-return block before loop-continue
  (`cmp; beq continue; subs r0,r3,#1; b return; continue: ...`). **Goto form**
  (`if (*b++ == *a++) goto cont; return b-1; cont: ...`) reproduces the
  block order — the "basic-block ordering" wall was a source-shape issue.
- **New idiom — dead-parameter reuse:** `len = (u32)-1;` after the zero-check
  reuses the dead `len` param (r2) for the loop-invariant -1, giving ROM's
  `movs r2,#1; negs r2,#2` + `cmp r4,r2`. (A separate `s32 neg1` variable
  went to r6 with an extra push; pinning neg1 to r2 conflicted with len.)
- Path: v1 (25 diffs, -1 rematerialized in loop) → v2 (13 diffs, neg1 var
  in r6) → v3 (39 diffs, r2 pin broke) → v4 (0 diffs, len reuse).

### MATCHED: 0x080260D4 F_080260D4 — 52 B, 0 diffs, main agbcc
- **File:** `staging/wave33_D/w33d_080260d4_MATCHED.c`
- **True extent:** 0x080260D4–0x080026108 = 52 B.
- **Registry:** only prior row is W15-D BLOCKED — coordinator appends MATCHED.
- **Callee:** `SetIfGt199` (real build symbol, `src/wave7_g2_old.c`
  @0x0802571C).
- **Wall broken (W15-D):** loop-top s16 extend hoist resists LICM. **Volatile
  barrier on s32 temp** forces the explicit extend:
  ```c
  s32 t = (s32)i + 1;
  __asm__ volatile("" : "+r" (t));
  i = (s16)t;
  ```
  gives ROM's `adds r4,#1; lsls r4,r4,#16; lsrs r0,r4,#16; asrs r4,r4,#16`.
- First-try match.

### BLOCKED (still): 0x0800D9FC ChipSlot_Tick — best 190 diffs (v8)
- **File:** `staging/wave33_D/w33d_0800d9fc_BEST.c` (v8).
- **True extent:** 0x0800D9FC–0x08000DB40 = 324 B.
- **Registry:** BLOCKED row exists (W2-A) — no new row.
- **HARD BLOCKER BROKEN:** ROM's explicit `(u8)` truncation
  (`lsls r0,r2,#24; lsrs r0,r0,#24`) in the diamond, which 15+ variants
  could not produce (compilers range-analyze `(x>>4)&1` as 0/1). **Volatile
  `"+r"` barrier inside the else-branch makes the value opaque, forcing
  the truncation.** Probe (`staging/wave33_D/probe_d9fc_diamond.c`)
  reproduces the exact diamond shape:
  `beq else; adds r0,r3,#0; eors r0,r2; b join; else: lsls/lsrs; join: strb`.
- **Also solved:** prologue `push {r4-r7,lr}; mov r7,r8; push {r7}` via r8
  pin (W24-D: r8 pins give correct save/restore); `ldr r2,[pc]; mov r12,r2`
  via ip pin; `movs r3,#1; ands r2,r3` via block-scoped r3 pin (does NOT go
  function-wide — probe proved); p48→r6 via r6 pin (prologue intact).
- **Remaining walls (190 diffs):** intricate register allocation —
  p26→r4 copy (`adds r4,r2,#0`), s[30]→r7, r3v→r3, s[28] reloads (not CSE),
  pool-load temp r7 vs r1, `movs r0,#128`/`ldrb` order in diamond (2 B).
  The r4 pin for p26 disrupted allocation (251 diffs). Needs systematic
  pressure engineering beyond this wave's budget.
- **Callees:** `sub_080042B8` (BLOCKED), `sub_0800244C` (BLOCKED),
  `Wrap_08002904` (MATCHED).

### DUPLICATE (not claimed): 0x08002E80
- Achieved 0 diffs with main agbcc pure C
  (`staging/wave33_D/w33d_08002e80_DUPLICATE.c`), breaking the W14-D/W22-C
  4-byte scheduling wall via: `&tmp` address taken before dispcnt
  materialization (mov r1,sp first); memory barrier + block-scoped r1/r4
  pins for the `|=` block (`mov r1,sp; mov r0,sp; ldr r2,[pc]` order);
  `"+r"` barriers to defeat `stmia` fusion in the tail.
- **Registry already MATCHED** (W23-A, `src/w23a_08002e80.c`, old_agbcc).
  NOT claimed. Kept as reference (proves main-agbcc pure-C alternative).

## Task 3: Bulk leaves-up — 9 NEW MATCHES

All verified 0 diffs, main agbcc, clean-room. Registry checked — no prior
rows for any. Coordinator appends MATCHED rows.

| Addr | Size | File | Notes |
|------|------|------|-------|
| 0x08005268 | 10+2 pad | w33d_08005268_MATCHED.c | void forwarder to F_08002300 (BLOCKED, stub) |
| 0x0800B3EC | 12 | w33d_0800b3ec_MATCHED.c | calls F_0800B520 (BLOCKED, stub), returns 1 |
| 0x08004E50 | 14+2 pad | w33d_08004e50_MATCHED.c | u8 arg truncation, calls F_08004E60 (stub) |
| 0x0804AD3C | 14+2 pad | w33d_0804ad3c_MATCHED.c | (s8) sign-extend of F_08004AD7C return (stub) |
| 0x08024CC0 | 22+2 pad | w33d_08024cc0_MATCHED.c | (u8),(u8)→(u16) wrapper of F_080249B8 (MATCHED) |
| 0x08007F3C | 24 | w33d_08007f3c_MATCHED.c | (u16),(s8),(s8),0 → F_08007F54 (stub) |
| 0x0800EA14 | 24+4 pool | w33d_0800ea14_MATCHED.c | volatile s16 store + ldrsh reload, F_0800BF6C (BLOCKED, stub) |
| 0x0800EE70 | 24+4 pool | w33d_0800ee70_MATCHED.c | same, 255 instead of 128 |
| 0x080111B4 | 24+4 pool | w33d_080111b4_MATCHED.c | p[4]=a,p[1]=p[0]=0, calls F_0800B3EC(0,0) |

**New idiom (0800EA14):** two-pointer volatile/non-volatile pair — volatile
`s16*` for the store, plain `s16*` for the load — gives ROM's
`strh` + `movs r2,#0; ldrsh r0,[r1,r2]` (agbcc won't emit `ldrsh` from a
volatile load; plain `s16*` does).

**Note (080111B4):** caller passes `(0,0)` to F_0800B3EC (`movs r0,#0;
movs r1,#0` before bl) though the callee is `void(void)` — prototype
mismatch is caller-side only; same symbol at link.

## New idioms for the catalog
1. **Explicit copy asm defeats temp rotation:** `__asm__ volatile("add %0,
   %1, #0" : "=r"(dst) : "r"(src))` forces a redundant register copy,
   defeating gcc's temp-rotation (LoopSet mask→r0). The resulting
   `(copy & v) == 0` test emits the *redundant* `ands; cmp` (combiner does
   not merge through the opaque copy).
2. **Volatile `"+r"` barrier forces explicit truncation:** makes a
   range-analyzed value opaque, forcing `lsls/lsrs #24` (u8), `lsls/lsrs #16`
   (u16), or `lsls/asrs #16` (s16) materialization. Breaks the ChipSlot_Tick
   diamond wall and the F_080260D4 s16-hoist wall.
3. **Dead-parameter reuse:** reassigning a dead parameter (`len = -1`)
   forces a loop-invariant constant into the parameter's register
   (Sram_VerifyCompare: `cmp r4,r2` with r2=-1).
4. **Block-scoped r3/r4/r6 pins are safe:** do NOT mark function-wide (r7 is
   the exception — pinned r7 not saved). Prologue intact with r4/r6 pins.
5. **r8/ip pins:** give correct `mov r7,r8; push {r7}` save/restore and
   `ldr; mov r12` sequences for hi-reg allocation.
6. **Memory barrier defeats pool-load hoisting:** `__asm__ volatile(""
   ::: "memory")` between address materialization and pool-pointer
   assignment forces `ldr [pc]` after the movs (08002E80).
7. **`"+r"` barrier defeats `stmia` fusion:** barrier on the pointer between
   store and increment forces `str` + `adds` instead of `stmia` (08002E80).

## What's next
- Coordinator lands: 04998 swap (Makefile), 12 new MATCHED rows + sources.
- ChipSlot_Tick: diamond wall broken; needs allocation engineering (r4/r7/r3).
- 459 unattempted Thumb functions remain; smallest-first continues.
