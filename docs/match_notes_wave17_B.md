# Wave 17 Worker B notes — Task_3AFFC @ 0x0803AFFC retry (2026-10-22)

## Task_3AFFC @ 0x0803AFFC: BLOCKED, best 351 diffs (was 363), 936/928 B, old_agbcc

Best source: `staging/wave17_B/w17b_3affc_best.c` (old_agbcc, 936/928 B, +8).

### MAJOR BREAKTHROUGH — Tail-sharing structure SOLVED

The ROM's tail-sharing pattern is now reproduced with 8/10 instructions byte-exact:

**ROM pattern:**
```
case 3:  bl Text_SelectBlobIdx; ldr r0,[pc]; adds r1,r4,r0; movs r2,#0; movs r0,#9; b 0x3b33c
case 13: ldr r2,[pc]; adds r1,r4,r2; movs r2,#0; movs r0,#7  (fallthrough)
0x3b33c: strb r0,[r1,#0]          (shared)
0x3b33e: ldr r1,[pc,#12]; adds r0,r4,r1; strb r2,[r0,#0]; movs r5,#1; b epi  (shared tail)
```

**Our output (8/10 exact):**
```
case 3:  bl Text_SelectBlobIdx; ldr r0,[pc]; adds r1,r4,r0; movs r2,#0; movs r0,#9; b shared
case 13: ldr r0,[pc]; adds r1,r4,r0; movs r2,#0; movs r0,#7  (fallthrough)
shared:  strb r0,[r1,#0]
tail:    ldr r1,[pc,#12]; adds r0,r4,r1; strb r2,[r0,#0]; movs r5,#1; b epi
```

Only differences: case 13's pool temp reg (`ldr r0` vs ROM `ldr r2`, 4 bytes).

### Key idioms discovered

1. **Mid-switch `tail_c` label (w15 reconstruction CONFIRMED):**
   Placing `tail_c:` inside case 13's block (after the if/else chain's `break`) causes
   old_agbcc's cross-jumping to merge the `strb r0,[r1]; b tail_c` suffixes from case 3
   and case 13 into a shared block. This reproduces the w15 288-diff result (we got 287).
   File: `b2_midswitch_tailc.c` (287 diffs, 932 B).
   - Critical: blocks must END WITH A JUMP for cross-jumping to fire. The `goto tail_c`
     is essential. Inline tails (b1, 490 diffs) do NOT merge the strb.

2. **Deferred-zero via function-scope variable (NEW):**
   ```c
   u8 z;  // function scope
   // case 3:
   Text_SelectBlobIdx(0x68);
   { u8 *q = p + 0x469c; z = 0; *q = 9; goto tail_c; }
   // case 13:
   { u8 *q = p + 0x469c; z = 0; *q = 7; goto tail_c; }
   // tail_c (mid-switch in case 13):
   tail_c:
       p[0x469d] = z;
       ret = 1;
       goto epi;
   ```
   The `z = 0` in the setups emits `movs r2,#0` after the address setup (source order
   via explicit `u8 *q`). The shared tail reuses r2 (`strb r2,[r0]`), matching ROM.
   Without z, the tail emits `mov r0,#0; strb r0,[r1]` (wrong regs).

3. **Cross-jumping requires jump-terminated blocks (probe-verified):**
   - `probe_xj.c`: `p[4]=9/7; p[5]=0; ret=1; goto tail` in two branches → full suffix
     merged into shared block, zero reused from r5 (ret=0).
   - `probe_xj2.c`: same with 0x469c/0x469d offsets → merged, value in r1, addr in r0,
     zero from r5.
   - Blocks ending with fallthrough do NOT get cross-jump merged.

4. **Block-scope register vars CANNOT cross goto (probe-verified):**
   `probe_pin.c`: `register u32 v __asm__("r0")` in a block, used after `goto` outside
   the block → compile error "`v' undeclared". The "pinned r0/r1/r2" hypothesis in
   its literal form (block-scope pinned regs + goto) is NOT viable in C. The z-variable
   achieves the same observable effect (r2=0 live into shared tail) without pinning.

5. **Zero-reuse pattern:** When a zero-valued register is live (r2 from `z=0`, or r5
   from `ret=0`), the compiler reuses it for subsequent `p[x] = 0` stores instead of
   emitting a new `mov`. This is key to matching ROM's `strb r2,[r0]` (no extra mov).

### What did NOT work

- **Per-case asm barriers:** Confirmed not viable (old_agbcc drops empty volatile asm).
  Not retried per task instructions.
- **Inline tails (b1):** 490 diffs, 932 B. Without `goto`, cross-jumping doesn't merge
  the strb. Worse than baseline.
- **Mode 2/4 `lsls;ldr;lsrs` interleave:** Could NOT reproduce. Probes (`probe_m2.c`,
  `probe_m3.c`) with various formulations (explicit shifts, split statements) all
  produce `lsls; lsrs; ldr` (shifts together). Main agbcc also doesn't interleave.
  The ROM's `subs; lsls; ldr; lsrs` order resists C-level control with old_agbcc.
  Likely requires a different compiler version or specific scheduler behavior.
- **Case 9 z9 variable:** Block-scope `u8 z9 = 0` got g8 into r2 (correct!) but
  disrupted other regs; net 367 diffs (worse). Reverted.
- **Removing explicit `u8 *q`:** 357 diffs (worse than 351). The explicit q is needed
  for the `mov r2,#0` ordering (after address setup, before value mov).

### Remaining issues (351 diffs)

- **Size:** 936/928 B (+8). The two `mov r2,#0` (4 B) are CORRECT (ROM has them).
  One extra 0x469d pool word (4 B) vs baseline. 4 B of bloat from baseline persists.
- **Case 13 pool reg:** `ldr r0` vs ROM `ldr r2` (4 B). Regalloc nuance, resists tuning.
- **Modes 2/4:** `lsls; lsrs; ldr` vs ROM `lsls; ldr; lsrs` (interleave not reproduced).
- **g8 regalloc:** Case 9/13 g8 in r1 vs ROM r2 (partially addressed, needs work).
- **Dispatch region:** Switch dispatch `uxth/uxtb/cbz` regs differ from ROM.
- **0x240-0x33f region:** ~220 diffs, mostly case bodies (9-15) with regalloc differences.

### Iteration history

- b0_base.c: 363 diffs, 928 B (baseline, w16a_3affc_best.c)
- b1_inline_tail.c: 490 diffs, 932 B (inline tails, no goto — merge failed)
- b2_midswitch_tailc.c: 287 diffs, 932 B (w15 reconstruction — tail_c mid-switch)
- b3_zvar.c: 357 diffs, 936 B (added z variable, wrong ordering)
- b4_qorder.c: 351 diffs, 936 B (explicit q for ordering — TAIL SOLVED)
- b5_work.c: 367 diffs, 936 B (case 9 z9 experiment — reverted)
- b6_work.c: 357 diffs, 936 B (removed q — worse, reverted)
- w17b_3affc_best.c: 351 diffs, 936 B (b4 copy, current best)

### Probes

- `probe_pin.c`: Block-scope register vars + goto → compile error. Pinning hypothesis
  in literal form NOT viable.
- `probe_xj.c`, `probe_xj2.c`: Cross-jumping behavior with small/large offsets.
  Confirmed: jump-terminated blocks merge; zero reused from live reg.
- `probe_2st.c`: Two-store sequence, long suffix merge with r5 zero.
- `probe_m2.c`, `probe_m3.c`: Mode 2/4 interleave attempts. All failed to reproduce
  `lsls; ldr; lsrs`.

### Build harness

`staging/wave17_B/build_3affc.sh <cfile> [tag]`: Compiles with old_agbcc -O2
-mthumb-interwork, links `.text.<section>` at 0x0803AFFC, extracts 928 bytes,
diffs vs ROM. Asserts non-empty at each step.

## Recommendation for next worker

The tail-sharing is SOLVED. Focus on:
1. **Size reduction** (936→928): eliminate the extra 0x469d pool, find the 4 B bloat.
2. **Mode 2/4 interleave**: May need a different approach (or accept as blocked).
3. **g8 regalloc**: The z-variable pattern might work for case 9 if tuned carefully.
4. **Case bodies**: The 0x240-0x33f region has ~220 diffs; systematic case-by-case
   work could yield big wins.

The `u8 z` + `u8 *q` + mid-switch `tail_c` pattern is the key idiom. It should be
propagated to similar tail-sharing patterns in other functions.
