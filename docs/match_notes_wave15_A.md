# Wave 15 Worker A (TAG=A) — Task_3AFFC Path: sub_0800B148 + Task_3AFFC Retry — Match Notes

Worker: Wave 15 specialist (TAG=A). Date: 2026-10-22.
Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` before start.
Toolchain: `mmbcc/tools/agbcc/bin/{agbcc,old_agbcc}`; `arm-none-eabi` 2.42 (present).
Harness: `/tmp/wave15_A/mk.sh` (B148, 340 B), `/tmp/wave15_A/mk3.sh` (3AFFC, 928 B,
adapted from wave11_C with .rodata concatenation). Hardened assertions throughout.
Staging: `/tmp/wave15_A/` (20 B148 versions v1–v20 + best; 4 3AFFC versions v1–v4 + best; NEVER delete).
Results: `docs/wave15_A_results.tsv`.

**Result: BOTH BLOCKED, but substantial progress.**
- **sub_0800B148 @ 0x0800B148: BLOCKED.** Best: **191 diffs** (v17, 348/340 B,
  old_agbcc), down from 230 (v1 baseline = wave14 v25). Both assigned angles solved.
- **Task_3AFFC @ 0x0803AFFC: BLOCKED.** Best retry: **288 diffs** (v3, 932/928 B,
  old_agbcc), down from 363. Three genuinely new angles tried; one is a major
  structural advance (mid-switch tail label).

## sub_0800B148: Solved Blockers

### R1. Memcheck b16 copy — SOLVED (byte-exact at file offset 0x7C)
**ROM target:**
```
lsls r0,r6,#16; ldrh r3,[r5,#6]; lsls r1,r3,#16; adds r3,r0,#0; cmp r1,r3; beq join
```
**Solution (v8→v11):** Three-part construction.
1. `register u32 bf __asm__("r0") = ((u32)bb) << 16;` pins the fresh value to r0.
2. **Duplicate pin trick (new idiom):** `register u16 mh __asm__("r3");` in the
   inner block, alongside function-scope `register s32 b16 __asm__("r3")`.
   Probe-verified: GCC 2.9 accepts two explicit register variables on the same
   hard register when lifetimes don't overlap (mh dies before b16 is redefined).
   Gives `ldrh r3,[r5,#6]` + `lsls r1,r3,#16`. (Without the pin, mh went to r1;
   a `b16 = *(u16*)` store was dead-store-eliminated because the copy asm
   redefines b16.)
3. Minimal volatile asm for the copy only (branch stays in C):
   `__asm__ volatile ("add %0, %1, #0" : "=r" (b16) : "r" (bf));`
   → `adds r3,r0,#0`. NOTE: must be `add` (no S); `adds` is rejected by GAS 2.42
   ("not supported in Thumb16"). The volatile asm also blocks the compiler from
   seeing through the copy, so `if (m16 != (u32)b16)` emits `cmp r1,r3`.
4. Memcheck-!= path: `u32 t21b; t21b = (aa<<4); t21b |= tm;` gives ROM's
   `mov r1,ip; lsls r0,r1,#4; orrs r0,r2` (r2 = tm preserved).

### R2. Join t21 `ands r0,r4` — SOLVED (byte-exact 16 B at 0xEA)
**ROM target:**
```
movs r1,#15; mov r7,ip; ands r1,r7; movs r0,#16; negs r0,r0; ands r0,r4;
orrs r0,r1; strb r0,[r5,#21]
```
**Solution (v2→v7):** Swapped-operand widened-temp (new angle vs wave14 probe
which only tried `t &= -16`):
```c
u8 a15; u32 t21;
a15 = 15; c24 = aa; a15 &= c24;   /* movs r1,#15; mov r7,ip; ands r1,r7 */
t21 = (u32)-16; t21 &= v21;       /* movs r0,#16; negs; ands r0,r4 */
t21 |= a15; base[21] = (u8)t21;   /* orrs r0,r1; strb */
```
Key findings:
- `t21 = (u32)-16; t21 &= v21;` forces the constant into r0 and `ands r0,r4`
  (pinned r4 can't be the AND destination; result must go to t21's r0).
- `c24 = aa` reuses the dead-at-join c24 (pinned r7) to get `mov r7,ip`.
- `t21 |= a15` (compound) forces the OR destination to r0; plain `|` picked r1.
- Declaring `v21` as `u32` (was u8) eliminated the `lsl/lsr r4` zero-extend
  before the AND (v4: -4 B, 368→364 B). Safe: all v21 uses are ldrb/adds/ands.

### R3. sh!=aa path `orrs r0,r1` — SOLVED
```c
u32 tA, tB; tA = (aa<<4); tB = (v21 & mask); tB |= tA; base[21] = tB;
```
→ `mov r0,ip; lsls r1,r0,#4; adds r0,r2,#0; ands r0,r4; orrs r0,r1`.
Bonus: the compiler now crossjumps the `strb r0,[r5,#21]` with the memcheck
path's (matching ROM's `b 0x800b1da` shared-strb structure).

### tm `adds r0,r2,#0` copy — SOLVED
ROM: `ands r2,r4; adds r0,r2,#0; cmp r0,#2 ... cmp r0,#4`. The copy is a
u8→u32 widening the compiler copy-propagates away (`u32 tmc = tm` was
eliminated). Forced with pinned-r0 + volatile asm:
```c
u8 tm = v21 & mask; register u32 tmc __asm__("r0");
__asm__ volatile ("add %0, %1, #0" : "=r" (tmc) : "r" (tm));
```

## sub_0800B148: Residual Blockers (191 diffs)

1. **Prologue save-set (8 B):** ours `push {r4,r5,r6,lr}` / `mov r6,r9` /
   `mov r5,r8` / `push {r5,r6}`; ROM `push {r4-r7,lr}` / `mov r7,r9` /
   `mov r6,r8` / `push {r6,r7}`. r7 (c24's pin) is not saved because it's not
   live across calls; v21/base/bb are saved despite the same. Tried: `"+r"`
   (c24) in prologue asm — no change. Likely a GCC 2.9 quirk with explicit
   register variables; resists C-level control. (Epilogue pop lists differ
   correspondingly; same sizes, only list bits.)
2. **t30/t31 blocks (~20 B):** register allocation drifted after the v21-u32
   change (ours `ldrb r1`/`ands r1,r0` vs ROM `ldrb r3`/`ands r0,r3`, etc.).
   The widened-temp idiom sites need re-tuning under the new allocation.
3. **Join base9 block (~15 B):** ROM does `mov r7,r9` then `ldrb [r7,#imm]`
   directly. Ours materializes addresses (`mov r0,#20; add r0,r0,r7`).
   Tried: duplicate pin `register u8 *b9 __asm__("r7")` (v16/v19) — compiler
   clobbered r9 (`mov r9,r0`); c24-reuse + natural `u8 *b9` (v17, current best)
   gives `mov r7,r9; add r6,r7,#0` (+2 B tax, uses r6 not r7).
4. **c1 block (~10 B):** ours `(cc>>1)&1` via `lsls/lsrs` bitfield extract;
   ROM via `lsrs r1,r0,#1; movs r4,#1; ands r1,r4`.
5. **c3 block (~10 B):** similar allocation drift.
6. **`(cc&4)?2:0` (~6 B):** ours `cmp/beq`; ROM branchless
   `ands; lsls/lsrs #24; negs; asrs #31; ands #2`.
7. **Size:** 348 vs 340 (+8). Contributors: join-base9 `add r6,r7,#0` (+2),
   t30/t31 and c1/c3 extras.

## Task_3AFFC Retry: New Angles

Baseline v1 = wave11_C v18 (363 diffs, 928/928 B, old_agbcc). Callee
declarations already correct: `void SyncObjFlagBits_BEE0(u32,u32)`,
`u8 TblGetByte_241F8(u16)`, `u8 TblGetByte_24384(u16)`,
`u8 sub_0800B148(u8,s16,u8)` (s16 confirmed by ROM call sites:
`adds r1,r0,#0; lsls r1,#16; asrs r1,#16` before both `bl 0x800b148`).
All other callees MATCHED (EntryMgr_Teardown, Text_SelectBlobIdx, Sub200,
Check_B308, sub_0800B368).

### Angle A: main agbcc full-function — FAILED (366 diffs)
Built v1 unchanged with main agbcc: 366 diffs vs 363 (old_agbcc). Main agbcc's
scheduler/allocator is worse for this function's crossjump structure. Rejected.

### Angle B1: mid-switch `tail_c` label — MAJOR PROGRESS (288 diffs)
**New idea:** moved the `tail_c:` label from after the switch to INSIDE case
13's block (after its if-else, before `break`). The compiler now emits the
shared tail at ROM's address 0x803B33C (was 0x803B37A) — the 8-byte modes 10–15
layout shift is fixed. Moreover, the compiler cross-merged the `p[0x469c]`
store: case 3 sets up `(r0=9, r1=&p[0x469c])` and branches to the shared
`strb r0,[r1,#0]`; case 13 falls through with `(r0=7, ...)` — exactly ROM's
register-setup sharing pattern.
**Why not 0 diffs:** 932 vs 928 B (+4). Our tail redundantly materializes the
`p[0x469c]=7` setup (ldr/adds/movs = 6 B) instead of sharing the strb purely
via caller register setup like ROM; plus `p[0x469d]=0` uses `movs r0,#0`
instead of ROM's caller-provided `r2=0`. The C `p[0x469c] = 7; goto tail_c`
can't express "defer the store, just set up registers."
Best: v3 (`w15a_3affc_best.c`), 288 diffs.

### Angle B2: no gotos, inlined tails — FAILED (491 diffs)
Removed both `goto tail_c`, inlined `p[0x469d]=0; ret=1;` at each site:
491 diffs, 932 B. old_agbcc does NOT crossjump the duplicates. Confirms
wave11_C: gotos are required for the size; the problem is purely placement,
which B1 addresses.

### Not retried (documented for future)
- Mode 2/4 `lsls;ldr;lsrs` interleave (compiler fuses shifts; needs an
  intervening op that emits no code — empty asm is ignored by old_agbcc).
- g8 in r1 vs r2 regalloc (per-mode ldr variation resists pinning).
- Mode 3 tail `movs r2,#0` setup before shared tail.
- B148 is still BLOCKED, so 3AFFC's 4th callee can't resolve (independent of
  the above — 3AFFC's bytes don't depend on B148's body, only the call
  sequence, which is already correct).

## Files (all in /tmp/wave15_A/, NEVER delete)
- `w15a_0800b148_best.c` — best B148 (v17, 191 diffs, 348 B)
- `w15a_0800b148_v1.c` … `w15a_0800b148_v20.c` — iteration history
  (v1=wave14-v25 baseline 230; v7=R2 solved; v11=R1 solved; v12=memcheck-!= OR;
  v13=R3 solved; v15=tm copy; v17=best; v20=prologue +r probe, no change)
- `w15a_3affc_best.c` — best 3AFFC retry (v3, 288 diffs, 932 B)
- `w15a_3affc_v1.c` (363 baseline), `w15a_3affc_v2.c` (main agbcc, 366),
  `w15a_3affc_v4.c` (no gotos, 491)
- `mk.sh`, `mk3.sh` — harnesses; `probepin.c` — duplicate-pin probe
- `rom_b148.bin/.dis`, `rom_3affc.bin/.dis`, `ours_v*.dis` — reference

## What's Next
1. **B148:** The 6 residual blockers are all localized; the function is now
   191 diffs with 4 byte-exact regions (prologue-42 B prefix, memcheck,
   join-t21, sh-path). The prologue save-set is the hardest; t30/t31/c1/c3
   are allocator tuning. If B148 lands, 3AFFC's call sites are already correct.
2. **3AFFC:** v3's mid-switch label is the new baseline (288). The +4 B tail
   setup and mode 2/4 interleave are the next targets. A promising untried
   shape: make case 13's g8==1 set up registers via pinned temps instead of
   a C store, so the shared `strb` is purely caller-driven like ROM.
3. **Idioms to propagate:** duplicate-pin same-register trick (verified safe
   when lifetimes don't overlap); swapped-operand `t=(u32)-N; t&=pinned` for
   `ands r0,rN`; `|=`/`&=` on the temp holding the desired destination
   register; `mov r7,ip`-via-dead-pinned-var reuse.
