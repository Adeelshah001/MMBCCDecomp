# Wave 6 blkB — Blocked-Revisit Match Notes (worker, 2026-10-20)

Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` (read in
place, never copied). Toolchain: `mmbcc/tools/agbcc/bin/agbcc` (main) /
`old_agbcc`. Exact build rule per task. Verification: link section at ROM
address with 2-byte Thumb stubs at bl targets, objcopy, byte-diff.
Scratch: `/tmp/wave6_blkB/`.

Result: **2 UNBLOCKED, 2 BLOCKED (1 permanent).**

## UNBLOCKED (2)

### 1. sub_080230A0 @ 0x080230A0 — UNBLOCKED (0 diffs, old_agbcc)

**Formulation**: `/tmp/wave6_blkB/sub_080230A0_080230A0_MATCHED.c`

The 2-byte diff was ROM's `adds r0,r1,#0` (redundant move) before `cmp r0,#3`.
9 prior variants failed; the fresh angle that worked was **inline-asm for
the move**:
```c
s32 v = 3 & tbl[idx];
s32 w;
__asm__ volatile("add %0, %1, #0" : "=l"(w) : "l"(v));
if (w > 3)
    v = 3;
```
- Use `add` (not `adds`) in the asm string — GAS 2.42 rejects `adds` with
  explicit registers in inline asm (same rule as `lsl`/`asr` from wave5_blk).
- The `w` must be `s32` (signed) to get ROM's `ble` (not `bls`). The `3 & b`
  result in `s32 v` gives signed comparison.

**Other idioms used:**
- **Double-OR pinning**: `register u8 vo __asm__("r0"); vo = 2; vo |= s[0xa];
  vo |= 1;` forces `movs r0,#2; ldrb r1; orrs r0,r1; movs r1,#1; orrs r0,r1`
  (ROM order). Without pinning, compiler swaps r0/r1.
- **Direct base for ldrh**: `u8 *base = (u8 *)0x081705B0; h = *(u16 *)(base+2);`
  gives `ldr r0,=base; ldrh r0,[r0,#2]`. (The `extern u8 arr[]` + `.set`
  approach lost the +2 offset.)
- **Volatile barrier for pool scheduling**: `__asm__ volatile("" ::: "memory");`
  between `idx` calc and `tbl = gTbl_...` forces the `ldr r1,=tbl` to occur
  AFTER the `lsls/lsrs` shifts (ROM order: shifts then load).
- **Hoisted shift**: `v <<= 2;` placed immediately after `q = s + 0x45`
  (before `mask = 13`) gives ROM's `lsls r1,#2` position (early, not late).

### 2. Task_37440 @ 0x08037440 — UNBLOCKED (0 diffs, old_agbcc)

**Formulation**: `/tmp/wave6_blkB/Task_37440_08037440_MATCHED.c`

120-byte mode dispatcher. Prologue wants `r5=p, r4=mode` (unusual).

**Key idioms:**
- **Block-scope r1 pinning for `g[0x14]|=1`**: 
  ```c
  { register u8 *g __asm__("r1") = gEwram_02004E40; g[0x14] |= 1; }
  ```
  Forces `ldr r1,=0x02004E40; movs r0,#1; ldrb r2,[r1,#20]; orrs r0,r2`.
  (Without pinning, or with function-scope `mode` pinning, compiler uses r0
  for base. The pinning must be block-scoped to avoid interfering with
  `mode`'s r4 allocation.)
- **Goto-beq for 2-case dispatch**: `if (mode == 0) goto case0; if (mode == 1)
  goto case1; goto epi;` gives ROM's `cmp r4,#0; beq; cmp r4,#1; beq; b`
  (compare chain, NOT a jump table). A `switch` or `if/else` gives `bne`.
  (Note: the goto structure changes prologue allocation — the r1 pinning
  above is required to compensate.)
- **Volatile barrier for table load order**:
  ```c
  u32 *tbl = (u32 *)0x082300E0;
  __asm__ volatile("" ::: "memory");
  idx = p[0x469f];
  ```
  Forces `ldr r1,=tbl` BEFORE `ldr r2,=0x469f` (ROM order).
- **Inline asm for `p[5]++` store**: The compiler eliminated the `strb` in
  `p[5]++` (dead-store elimination confusion with `mode`). Forced via:
  ```c
  u8 m;
  __asm__ volatile("ldrb %0, [%1, #5]\n\t" "add %0, #1\n\t" "strb %0, [%1, #5]"
                   : "=&l"(m) : "l"(p));
  ```
  (Use `add` not `adds`; `=&l` earlyclobber for the temp.)
- **Declaration order for `movs`**: `u8 *q = p + 0x4699; u8 z = 0;` (z AFTER q)
  gives `ldr r1,=0x4699; adds r0,r5,r1; movs r1,#0; strb r4,[r0]; strb r1,[r5,#5]`
  (ROM order: offset load, address, zero, stores). Reversed order gives
  `movs` too early.

## BLOCKED

### Task_3AFFC @ 0x0803AFFC — BLOCKED (tail-sharing crossjump)

926-byte 16-case dispatcher. Prologue/dispatch/JT byte-exact; mode bodies
mostly correct. Blocker is the shared `strb r0,[r1]` tail (TailA @ 0x803b38c)
used by 12 sites.

- Goto-based sharing (`q=p+0x469d; v=*q+1; goto t_inc; ... t_inc: *q=v;`)
  causes old_agbcc to MERGE the identical inc blocks and hoist conditions
  into the merged block. The `if` conditions vanish (replaced by
  unconditional branches). (v1/v3 experiments)
- Volatile q/v prevents merging but spills to stack (unusable).
- Inline `strb` (v2) gives 944 bytes vs ROM 926; mode bodies correct but
  layout shifts.
- TailC (@0x803b33c, modes 3+13) and TailD (@0x803b386, mode 12-else+15)
  are additional crossjump targets.

**What works:** Prologue (with r0 pinning for g base), dispatch, JT (all 16
entries), mode 0/6/10 inline inc, mode 2/4 table lookup (with volatile-split
`lsl`/`lsr` for `lsls#24; ldr; lsrs#22` scheduling).

**Status**: See `/tmp/wave6_blkB/t_3affc_status.md`. Formulations in
`/tmp/wave6_blkB/t_3affc_v*.c`. Needs a new angle to defeat block merging
(e.g., per-mode unique formulations).

### Vec2_CopyMirrored @ 0x0800DD08 — PERMANENTLY BLOCKED (2 bytes)

See `/tmp/wave6_blkB/vec2_vintage_conclusion.md` for full test.

**Vintage test**: No compiler/flag/code combination produces ROM's
`pop {r2}; bx r2`. Tested: agbcc/old_agbcc × -O1/-O2/-Os × interwork,
no-interwork (`pop {r4,pc}`), register pressure, type variants, r1-live,
natural vs asm formulations. All give `pop {r1}; bx r1`.

**ROM survey**: 479 functions use `pop {r1}; bx r1`, only 1 uses
`pop {r2}; bx r2` (this function). Our gcc 2.9 matches the original 479/480
times — NOT a systematic version difference, but a lone heuristic anomaly.
The original's epilogue scratch-register chooser picked r2 for this specific
register-pressure pattern; ours picks r1. Cannot be influenced from C.

**Verdict**: Stays permanently blocked. Do not retry.

## New generalizable idioms

1. **Inline asm for redundant moves**: `__asm__ volatile("add %0,%1,#0"
   : "=l"(dst) : "l"(src));` forces `adds rX,rY,#0`. Use `add` (not `adds`)
   for GAS 2.42. (sub_080230A0)

2. **Block-scope register pinning for globals**: `register u8 *g
   __asm__("r1") = gEwram_...;` forces a specific register for a global base
   without affecting function-scope allocation. (Task_37440: r1 for
   `g[0x14]|=1`; Task_3AFFC: r0 for same)

3. **Volatile memory barrier for load scheduling**: `__asm__ volatile(""
   ::: "memory");` between a computation and a pool load forces the load to
   occur after (not before). Use to match ROM's `ldr` positions.
   (sub_080230A0: table base after shifts; Task_37440: table before offset)

4. **Declaration order controls `movs` position**: Declaring `u8 z = 0;`
   AFTER `u8 *q = p + off;` places the `movs` after the address computation,
   matching ROM's `ldr; adds; movs` order. (Task_37440 case1)

5. **Hoisted shift via early statement**: Placing `v <<= 2;` immediately
   after address computation (before other ops) forces early `lsls`
   scheduling. (sub_080230A0)

6. **Goto-beq for small switches**: `if (x == 0) goto L0; if (x == 1) goto L1;`
   produces `cmp; beq; cmp; beq` compare chains (not jump tables) for 2-case
   dispatches. (Task_37440)

7. **Inline asm for dead-store elimination**: When the compiler eliminates a
   necessary `strb` (e.g., `p[5]++` where p[5] aliases a register-held value),
   force it with `__asm__ volatile("ldrb %0,[%1,#5]\n\tadd %0,#1\n\tstrb
   %0,[%1,#5]" : "=&l"(t) : "l"(p));`. (Task_37440 case0)

## Files for coordinator

- `/tmp/wave6_blkB/sub_080230A0_080230A0_MATCHED.c` — 0 diffs (old_agbcc)
- `/tmp/wave6_blkB/Task_37440_08037440_MATCHED.c` — 0 diffs (old_agbcc)
- `/tmp/wave6_blkB/vec2_vintage.c` — 2-byte diff (agbcc/old_agbcc)
- `/tmp/wave6_blkB/vec2_vintage_conclusion.md` — vintage test verdict
- `/tmp/wave6_blkB/t_3affc_status.md` — Task_3AFFC blocker analysis
- `/tmp/wave6_blkB/wave6_blkB_results.tsv` — summary table
- `/tmp/wave6_blkB/verify.py` — verification harness (reusable)

**Landing notes**:
- sub_080230A0: old_agbcc, uses inline asm (`add` not `adds`) and
  `register __asm__` pinning. Keep in its own section/file.
- Task_37440: old_agbcc, uses block-scope pinning and inline asm. The
  `goto` structure is load-bearing for the `beq` dispatch.
- Both need `.set` absolute symbols (see files).

## Coordinator landing notes (2026-10-20 ~21:35 EDT)

Both claims independently verified by coordinator via clean-room harness
(/tmp/coord_verify_wave6.py pattern): non-empty artifacts at every step
(112 B / 120 B .bin), baserom file offset = addr - 0x08000000, exact byte
counts, `cmp -l` clean. 0 diffs on both. Landed in
`mmbcc/src/wave6_blkb_old.c` (old_agbcc) with ldscript slots at
0x080230A0 and 0x08037440; full build re-verified — only the 7 known
dirty sections remain.

Landing details:
- `.set` stripped for matched symbols: sub_0800D6E0 -> ChipSlot_Setup,
  sub_0800D9EC -> ChipSlot_IncUse, EntryMgr_Teardown, EntryMgr_Setup
  (extern declarations renamed to the real matched names in the landed
  file; this caught an actual build error — the worker's extern names
  were the raw sub_08XXXXXX aliases).
- `.set` kept for unmatched callees sub_0800B368/sub_0800B308 with
  `.thumb_func` marking (direct bl, no ARM veneer), plus data symbols
  gBase_081705B0, gTbl_020031E4 (0x020031E4, distinct from
  gEwram_020031E4), gEwram_02004E40.
