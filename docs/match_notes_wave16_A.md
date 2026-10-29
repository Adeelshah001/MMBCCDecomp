# Wave 16 Worker A notes — Task_3AFFC path (2026-10-22)

## sub_0800B148 @ 0x0800B148: BLOCKED, best 95 diffs (was 191)

Best source: `staging/wave16_A/w16a_b148_best.c` (old_agbcc, 344/340 B, +4).
Iteration history: w16a_b148_v0.c … v10.c; probes: probe_cc4.c, probe_c1*.c, probe_jb*.c, probe_r7save.c.

### Breakthrough — prologue save-set SOLVED
`push {r4-r6,lr}` vs ROM `push {r4-r7,lr}` fixed by **unpinning c24**
(`register u32 c24 __asm__("r7")` → natural `u32 c24`). The compiler then
naturally allocates c24 to r7 AND includes r7 in the save-set.
**Root cause: explicit register variables are excluded from GCC 2.9's
save-set computation** — only compiler-allocated uses of a callee-saved
register trigger saving it. (aa-u8→u32 in wave14 v15→v20 broke it by forcing
an r7 scratch.) Propagate this idiom to other prologue-save-set blockers.

### New idioms
1. **c24-reuse for join base:** `c24 = (u32)base9; ((u8 *)c24)[20]` →
   `mov r7,r9` + `ldrb [r7,#imm]` (c24 already in r7 from t30/t31; avoids
   pinned-pointer address materialization).
2. **Branchless `(cc&4)?2:0`:** `u8 m4 = cc & 4; s32 t = -(s32)m4; t >>= 31;
   t &= 2;` → exact ROM `ands; lsls/lsrs #24; negs; asrs #31; ands`
   (probe-verified; original used arithmetic, not a ternary).
3. **c3 via pinned+volatile:** `register u32 cc3 __asm__("r3");
   __asm__ volatile("mov %0,r8":"=r"(cc3))` forces `mov r3,r8`;
   `register u32 c3 __asm__("r1")` forces shift into r1 →
   `ands r1,r4` (r4=1 reuse from c1).
4. **Tail zero via dead v21:** `v21 = 0; base[9] = (u8)v21;` →
   `movs r4,#0; strb r4,[r5,#9]` (reuses dead pinned r4).

### Byte-exact regions
prologue (16 B), memcheck (R1), join-t21 (R2), sh-path (R3), tail (14 B),
(cc&4) block.

### Remaining 95 diffs (all allocator-tuning; structures correct)
- t30/t31 regalloc: const/-65/load regs differ (r3/r2/r0 vs r2/r0/r3),
  load-vs-movs ordering
- join v20 block regalloc (r6/r2/r1 vs r2/r1/r6)
- c1 block (c1 in r2 vs r1)

## Task_3AFFC @ 0x0803AFFC: BLOCKED, 363 diffs (unchanged)

Best source: `staging/wave16_A/w16a_3affc_best.c` (v0 baseline + BEE0 fix,
old_agbcc, 928/928 B).

### Findings
- BEE0 signature corrected to `void sub_0800BEE0(u32,u32)` per landed
  callee — no codegen change (confirms wave14 note).
- **Mid-switch `tail_c` reconstruction (Angle B1) did NOT reproduce
  wave15's 288-diff result** — yielded 366 diffs/940 B. The v3 file was lost
  in the /tmp wipe and the prose was insufficient to reconstruct the exact
  cross-merged `p[0x469c]` store sharing.
- ROM pattern confirmed: case 3 sets up (r0=9, r1=&p[0x469c], r2=0) and
  branches to shared `strb r0,[r1,#0]` at 0x803B33C; case 13 sets up
  (r0=7, …) and falls through. r2=0 is caller-provided for the later
  p[0x469d]=0.

### Recommended next angles
- Macro/register-pinning hypothesis: pinned r0/r1/r2 setup + deferred store
  via goto (most promising untried angle for tail sharing).
- Mode 2/4 `lsls;ldr;lsrs` interleave and g8 regalloc remain.
