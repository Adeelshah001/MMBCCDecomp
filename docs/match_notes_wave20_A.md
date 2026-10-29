# Wave 20 Worker A notes — Task_3AFFC @ 0x0803AFFC (2026-10-23)

## Task_3AFFC @ 0x0803AFFC: BLOCKED, best 4 diffs (was 28), 928/928 B, old_agbcc

Best source: `staging/wave20_A/w20a_best4.c` (also `w20a_03_g81.c`,
`w20a_01_best20.c` intermediate). Harness: `staging/wave20_A/build_3affc.sh`
(wave19 harness, T=wave20_A). Isolated probes: `staging/wave20_A/probes/`.

### Progress: 28 → 4 diffs (86% reduction)

**Interleave SOLVED (8 B)**, **g8-in-r2 SOLVED (14 B)**. Remaining 4 B are two
mirrored contextual regalloc preferences (case 14 / store6) resistant to all
C-level nudges; explicit-register reservation works in isolation but poisons
global allocation in the full function.

### Key idioms discovered / applied

1. **Split-shift interleave via explicit register + dual empty-asm barriers
   (NEW, big win — 8 B):** ROM's `lsls r0,#24; ldr r1,[pc]; lsrs r0,#22` is a
   scheduler artifact old_agbcc never produces (all -O levels, both agbcc
   vintages, `-fschedule-insns*` unsupported). Reproduced byte-exact with:
   ```c
   register u32 r __asm__("r0");   /* binds call's raw r0, no zero-extend */
   sub_08024384(0x1000);
   r -= 50;
   __asm__("" : "+r" (r));                       /* barrier 1: blocks combine
                                                    distributing <<24 over -50 */
   t = r << 24;
   tbl = (u32 *)0x08232128;
   __asm__ volatile ("" : "+r" (t), "+r" (tbl)); /* barrier 2: blocks combine
                                                    merging shifts across the
                                                    pure pool load; forces tbl
                                                    materialization here */
   t >>= 22;
   fn = *(u32 *)((u8 *)t + (u32)tbl);            /* t-as-pointer gives
                                                    adds r0,r0,r1 */
   ```
   Result: `sub; lsl r0,#24; ldr r1; lsr r0,#22; add r0,r0,r1; ldr r0,[r0]`
   — byte-exact vs ROM. Semantics preserved: `t` keeps only low 8 bits of
   `(ret-50)` through `<<24`, so `(u8*)tbl + t` == `tbl[(u8)(ret-50)]`.
   Lessons: (a) `(r-50)<<24` gets distributed by combine even across
   statements — needs barrier 1; (b) combine merges `lsl`/`lsr` across a pure
   `ldr` — needs volatile barrier 2; (c) mentioning `tbl` in barrier 2 forces
   the load between the shifts (else GCC sinks it after); (d) `(u8*)t +
   (u32)tbl` (index-as-pointer) yields `add r0,r0,r1`, plain `tbl+t` yields
   `add r1,r1,r0`. The empty asm emits a harmless `.code 16` directive.
   Applied to cases 2 and 4 (tables 0x08232128 / 0x08232140).

2. **Scoped r1-reservation forces g8 copy into r2 (NEW — 3 B):** the allocator
   picks r1 for `adds r?,r0,#0` because r1 is free. Reserving r1 in a tight
   scope pushes the copy to r2:
   ```c
   {
       register u32 hold __asm__("r1");
       __asm__ volatile ("" : "=r" (hold));  /* define, zero code */
       g8 = gEwram_02004E40[8];              /* ldrb r0; adds r2,r0,#0 */
       __asm__ volatile ("" : "+r" (hold));  /* keep live, zero code */
   }
   ```
   r1 is reused normally after the scope (verified). Note: a *pinned copy*
   (`register u32 g8c __asm__("r2"); g8c = g8;`) does NOT work — the compiler
   sees through it and emits `ldrb r2` directly (no copy). The reservation
   must target the register you want to DENY, not the one you want.

3. **Early-zero via separate `u8 z = 0` statement (NEW — 9 B):** ROM's g8==1
   block does `movs r1,#0` immediately after computing `q` (reusing dead r1),
   ours did it late. A standalone `u8 z = 0;` before `*q = g8;` forces the
   early materialization:
   ```c
   } else if (g8 == 1) {
       u8 *q = p + 0x469c;
       u8 z = 0;          /* movs r1,#0 lands here */
       *q = g8;
       p[0x469d] = z;    /* ldr r2; adds r0,r4,r2; strb r1,[r0] */
       ret = 1;
   }
   ```
   With g8 in r2 this reproduces ROM's block byte-exact.

### What did NOT work

- **Interleave via -O1/-O2/-O3/-Os, main agbcc, agbcc_arm**: all emit
  `lsl;lsr;ldr`. agbcc_arm emits ARM (not Thumb) code — unusable.
  `-fschedule-insns` not supported by these builds.
- **Pinned g8c copy**: collapses to direct `ldrb r2` (compiler forwards).
  Barrier between load and copy does not prevent the forwarding.
- **Natural g8 variants** (`u32 g8`, `s8 g8`, case-3 early-out shape): all keep
  r1 (or r0) — the r2 choice specifically needs r1 denied.
- **Case-14/store6 regalloc (4 B remaining)**: see below.

### Remaining diffs (4 bytes) — BLOCKED with notes

- 0x3B36B–0x3B36C (2 B): case 14 `p[0x469d]++`: ours `ldr r2,[pc,#12];
  adds r1,r4,r2`, ROM `ldr r0,[pc,#12]; adds r1,r4,r0`.
- 0x3B387–0x3B388 (2 B): store6 `p[0x469d] = 6`: ours `ldr r0,[pc,#20]`,
  ROM `ldr r2,[pc,#20]`.

Both are pure contextual register preferences for the 0x469d pool load.
Tried for case 14: r2-reservation via scoped explicit register (works in
isolation: `ldr r0` achieved — but in the full function it poisons global
allocation: +8 B, 74 widespread diffs, so abandoned); decomposed
`q = p+off; v = *q; *q = v+1`; explicit `p[0x469d] = p[0x469d] + 1` — all keep
r2. Tried for store6: `u8 v = 6` first (broke layout: 848 B — goto-into-block
confuses old GCC); q-form `q = p+0x469d; *q = 6` (no change). Notably case 2's
identical `p[0x469d]++` uses r2 in BOTH ours and ROM (matches) — so the
allocator distinguishes case 14's context (args `(const,0,0,0)` vs case 2's
`(fn,mem,mem,0)`) in ROM's compiler but not in old_agbcc. This is a
compiler-vintage allocator heuristic difference, not reachable via C shape.

### Recommendations for next worker

1. The 4 B need either a different old_agbcc build with ROM's allocator
   heuristics, or a non-disruptive way to deny r0/r2 at those two points.
   The scoped-reservation idiom is proven but currently poisons global
   allocation — a tighter variant (e.g. reservation via clobber rather than
   explicit reg-var) might work.
2. The split-shift interleave idiom (barrier 1 + volatile barrier 2) is
   generalizable to any `lsl;ldr;lsr` scheduler artifact.
3. The r1-denial idiom generalizes: to force the allocator off its preferred
   register, reserve that register in a tight scope — but verify no global
   poisoning (check size first).

### Files

- `staging/wave20_A/w20a_best4.c` — best source (4 diffs, old_agbcc)
- `staging/wave20_A/w20a_01_best20.c` — intermediate (20 diffs, interleave only)
- `staging/wave20_A/w20a_03_g81.c` — same as best4 (4 diffs)
- `staging/wave20_A/build_3affc.sh` — build harness
- `staging/wave20_A/probes/il_v*.c, g8_*.c` — isolated probes
- `staging/wave20_A/bld_*.bin928`, `diff_*.txt` — build artifacts
