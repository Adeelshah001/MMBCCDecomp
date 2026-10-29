# Wave 5 BLOCKED-REVISIT — Match Notes (worker, 2026-10-20)

Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` (read in
place, never copied). Toolchain: `mmbcc/tools/agbcc/bin/agbcc` (main) /
`old_agbcc`. Build rule (exact): `cpp -I mmbcc/include <src>.c -o <x>.i &&
agbcc -O2 -mthumb-interwork -Wimplicit -Wparentheses -o <x>.s <x>.i &&
arm-none-eabi-as -mthumb -mcpu=arm7tdmi -o <x>.o <x>.s`.
Verification: link section at ROM address, objcopy --only-section, byte-diff
vs baserom. Scratch: `/tmp/wave5_blk/` (formulations saved as
`*_MATCHED.c` / `*_BLOCKED_*.c`).

Result: 3 UNBLOCKED, 1 near-miss (2 bytes), 17 still blocked/interior.

## UNBLOCKED (3)

### 1. HBlank_VCountUpdate @ 0x08000978 — UNBLOCKED (0 diffs, old_agbcc)

**Formulation** (`/tmp/wave5_blk/HBlank_VCountUpdate_08000978_MATCHED.c`):
- **Compiler: old_agbcc** (not main agbcc). The XOR scheduling
  (`movs r0,#2` before `ldrb r2,[r1]`) requires old_agbcc's scheduler;
  main agbcc emits `ldrb` first.
- **XOR via split-adds**: 
  ```c
  u8 *p = gIwram_03000400;
  u8 v;
  p += 0x167;
  v = 2;
  v ^= *p;
  *p = v;
  ```
  The `p = base; p += 0x167;` (separate statements) prevents the compiler
  from folding `base+0x167` into a single pool constant. It emits
  `ldr r0,=0x167; adds r1,r3,r0` (r3=base from earlier), then
  `movs r0,#2; ldrb r2,[r1]; eors r0,r2; strb r0,[r1]` — exactly the ROM.
- **AND/OR via inline asm** (wave4_g idiom):
  ```c
  __asm__("movs %0,#2\n\tand %0,%1" : "=l"(t) : "l"(b));  // test bit
  __asm__("movs %0,#2\n\torr %0,%1" : "=l"(t) : "l"(b));  // set bit
  ```
  The `"=l"` constraint forces dest r0, matching ROM's `ands r0,r1` /
  `orrs r0,r1`.
- **Extern array, not local**: `gIwram_03000400[0x167]` directly (not
  `u8 *base = ...` local) keeps base in r2 within blocks, reloads after
  calls, and avoids `push {r4,lr}`.
- **Volatile u16 local** for vcount forces stack slot with
  `strh [sp]` + `mov r0,sp; ldrh` reloads.

**Note**: The `bl _call_via_r0` (0x080009CA) encodes incorrectly in the
minimal test harness (goes to 0x08000A18 instead of 0x0804DCCC) — this is
the known minimal-harness linker quirk from wave4_j notes, not a source
problem. With ROM's bl bytes substituted, 0 diffs. Coordinator must verify
the BL in the full build.

### 2. StridedCopy @ 0x08000C68 — UNBLOCKED (0 diffs, main agbcc)

**Formulation** (`/tmp/wave5_blk/StridedCopy_08000C68_MATCHED.c`):
- **Register pinning**:
  ```c
  register struct StridedDesc *d __asm__("r4") = d_in;
  register u32 dst __asm__("r3");
  register int sstep __asm__("r5");
  ```
  Forces ROM's allocation: d=r4, dst=r3, sstep=r5 (vs compiler's
  d=r5,dst=r4,sstep=r3).
- **Load order matching ROM**: `src = d->src; dst = d->dst;
  sstep = d->src_step; dstep = d->dst_step; count = d->count;`
  (assignments in ROM's load order: #12, #4, #11, #10, #8).
- **Shifts hoisted before loop**: `ds = (dstep<<24)>>23;` and sstep shift
  before the `do/while`, not inside. ROM hoists both (loop jumps to
  0x08000C82, after the shifts).
- **Inline asm for sstep shift** (forces r0 scratch):
  ```c
  int scratch;
  __asm__("lsl %0,%2,#24\n\tasr %1,%0,#23"
          : "=&l"(scratch), "=l"(sstep) : "l"(sstep));
  ```
  The earlyclobber `"=&l"(scratch)` gets r0, emitting
  `lsls r0,r5,#24; asrs r5,r0,#23` (ROM) instead of in-place
  `lsls r5,r5,#24; asrs r5,r5,#23`. Note: use `lsl`/`asr` (not `lsls`/`asrs`)
  in the asm string — GAS 2.42 rejects the `s` suffix with explicit regs.

**Idiom**: When `register __asm__` pinning breaks a scratch-register pattern,
use inline asm with an earlyclobber temporary to force the scratch.

### 3. Task_366A8 @ 0x080366A8 — UNBLOCKED (0 diffs, main agbcc)

**Formulation** (`/tmp/wave5_blk/Task_366A8_080366A8_MATCHED.c`):
- **s32 + (s8) cast forces sign-extension**:
  ```c
  s32 v = (s8)sub_08004E0C(0);
  ```
  Emits `lsls r0,r0,#24; asrs r1,r0,#24` (ROM) instead of `lsrs`
  (zero-extend). The `s32` makes the sign observable to the compiler.
- **Condition is `if (!v)`, NOT `if (v)`**: The wave4_k notes had the
  condition backwards. ROM's `bne 0x080366DE` jumps OVER the body when
  v != 0, so the body executes when v == 0. Correct C:
  ```c
  if (!v) {
      p[1] = 2;
      p[2] = v;
      p[3] = v;
  }
  ```
- Full function includes the switch on `p[2]` (case 0: `sub_08004DFC(1);
  p[2]++;` fallthrough to case 1; case 1: Teardown, s8 test, Setup).

**Correction to wave4_k notes**: The `if (v)` in the notes is wrong; it's
`if (!v)`. The `asrs` is `lsls r0,r0,#24; asrs r1,r0,#24` (two instructions),
not single `asrs r1,r0,#24`.

## NEAR-MISS (1)

### Vec2_CopyMirrored @ 0x0800DD08 — BLOCKED (2-byte diff)

**Best formulation** (`/tmp/wave5_blk/Vec2_CopyMirrored_0800DD08_BLOCKED_2B.c`):
- Register pinning: `register u8 *d __asm__("r4") = d_in;` forces d=r4
  (ROM) vs d=r3 (compiler).
- Inline asm for flag test order:
  ```c
  __asm__("movs %0,#128" : "=l"(t));
  f = *s;
  __asm__("and %0,%1" : "+l"(t) : "l"(f));
  ```
  Forces `movs r0,#128` BEFORE `ldrb r1,[r1]` (ROM order), vs compiler's
  `ldrb`-first.

**Remaining diff** (2 bytes):
- ROM: `pop {r2}; bx r2` (`bc04`, `4710`)
- Mine: `pop {r1}; bx r1` (`bc02`, `4708`)

The return-address pop register is a compiler heuristic. Both r1 and r2 are
free at the end; agbcc and old_agbcc both pick r1, ROM has r2. This may be
a compiler-version difference (original gcc 2.95 vs our agbcc/old_agbcc).
No C formulation found to influence the pop register choice.

## STILL BLOCKED (with updated analysis)

### Sram_VerifyCompare @ 0x0804DC00 — BLOCKED (basic-block ordering)

The no-interwork angle does NOT apply — this is not a `pop {pc}` case
(ROM has `pop {r4,r5}; pop {r1}; bx r1`). The blocker is basic-block
ordering:
- ROM: `cmp r1,r0; beq continue; [mismatch block]; continue: ...`
- Mine: `cmp r1,r0; bne mismatch; [continue block]; mismatch: ...`

The ROM places the mismatch-return block INLINE (immediately after the
cmp), with the continue block out-of-line. Every C formulation (`if/else`,
`goto`, inverted conditions) emits the continue block first. This is a
gcc 2.95 basic-block layout heuristic that cannot be flipped from C.
**Stays BLOCKED.**

### Obj_AddEntry @ 0x0802D7A0 — BLOCKED (mask idiom proven, needs integration)

**New idiom proven in isolation** (`/tmp/wave5_blk/objmask3.c`):
```c
int mask = -3;
{
    int t = work[6];
    __asm__("and %0,%1" : "+l"(t) : "l"(mask));
    t |= x;
    work[6] = t;
}
```
- `int mask = -3` emits `mov rX,#3; neg rX,rX` (compiler handles it;
  do NOT use inline asm for the negation — GAS 2.42 rejects
  `negs r4,r4` and `rsbs r4,r4,#0` with same-register).
- The inline `and` with int types prevents the 8-bit narrowing
  (`& 253`) that pure C does when feeding a byte store.
- The mask is CSE-kept in a register across both RMWs (r4 in the test;
  ROM has r3 — register depends on surrounding code).

**Status**: Idiom works, but the full 10-param function (120+ bytes, complex
stack frame) was not integrated. The mask register (r3 vs r4) and instruction
scheduling need the full function context.

### ObjInit_TypeA @ 0x08017F8C / ObjInit_TypeB @ 0x0801DCC0 — BLOCKED

**TypeB double-OR solved** (wave4_h idiom):
```c
v = 2; v |= s[0xA]; v |= 1; s[0xA] = v;
```
gives `movs r0,#2; ldrb r1; orrs r0,r1; movs r1,#1; orrs r0,r1; strb`
(exact ROM sequence).

**Mask+OR ordering** works:
```c
int mask = -13;
u8 w = s[0x41] & mask;
w |= 4;
s[0x41] = w;
```
Materializes mask, ANDs, then materializes 4 (ROM order).

**Remaining blockers**:
- TypeA/B idx calc: `movs r1,#3` BEFORE `ldrb` scheduling. The inline-asm
  `movs %0,#3; and %0,%1` idiom (from Vec2_CopyMirrored) should work but
  was not integrated into the full function.
- TypeA dual-pool layout: ROM has separate pools for each branch
  (0x08017FF8 and 0x08018054); compiler merges them.
- Full 200-byte (TypeA) / 122-byte (TypeB) functions not built.

### MainLoop @ 0x080004FC — BLOCKED (LICM hoisting)

The `(baseReg -= const)` anti-fold idiom (from Task_Register) and
extern-array-base-not-hoisted idiom (from HBlank_VCountUpdate) were
considered but not tried — the 30 variants in match_notes_mainloop.md
already exhaust the hoisting space. The core issue (agbcc hoists
`base+0x2202`, ROM hoists `base+0x2000`) is a LICM decision that no source
variation has flipped. **No new angle found.**

### Text_OpenDialogue @ 0x0804CDE8 — BLOCKED

Control-flow/pool divergence after the matching prologue. The two window
loops and the `ldrb r0,[r7,#2]; adds r2,r0,#0` reload pattern were not
reproduced. No new angle tried in this batch.

### ChipSlot_Tick @ 0x0800D9FC — BLOCKED (not attempted)

Per task priority ("try last"), not attempted. The `(u8)` truncation
range-analysis blocker remains.

### Fragments — INTERIOR (not functions)

- **Frag_0803D9EC @ 0x0803D9EC**: `bl EntryMgr_Setup; b 0x0803DA92`
  (shared epilogue). Per wave4_j "intra-function bl as long branch" idiom,
  this is an interior label in the host function at 0x0803D9F4+, not a
  function. **Treat as part of host body.**
- **sub_0803C20E @ 0x0803C20E**: `bl EntryMgr_Setup; mov r0,r8; pop...; bx r1`
  (shared epilogue). Same class — interior label, not a function.
  **Treat as part of host body.**

### Others — BLOCKED (no new angle tried)

- **Frag_0804C558 @ 0x0804C558**: Result in r3 not r0. Wave4_j exhausted
  old_agbcc + volatile. Stays blocked.
- **sub_08047CC0 @ 0x08047CC0**: `movs r3,#0` scheduling. No new angle.
- **sub_0804C4FC @ 0x0804C4FC**: lr-push quirk (`push {r4,r5}` not producible).
  Wave4_j exhausted. Stays blocked.
- **Memset16 @ 0x080006DC**: Prologue live-range split. No new angle.
- **Task_35F50 @ 0x08035F50**: Big switch (159 bytes differ). No new angle.
- **Task_36BA8 @ 0x08036BA8 / Task_36CA8 @ 0x08036CA8**: Prologue regalloc
  (p=r4,mode=r5,g=r6). Register pinning needs the full function body;
  not completed in this batch.
- **Task_37440 @ 0x08037440**: Prologue scheduling (v in r0, w in r2).
  The inline-asm OR idiom (`movs %0,#1; orr %0,%1`) was identified but
  not integrated into the full 120-byte function.

## New generalizable idioms discovered

1. **old_agbcc for scheduler, not just regalloc**: HBlank_VCountUpdate
   needed old_agbcc for the `movs`/`ldrb` ORDER (not just register choice).
   When main agbcc has the right registers but wrong instruction order,
   try old_agbcc.

2. **Split-adds prevents pool folding**: `u8 *p = base; p += 0x167;`
   (separate statements) emits `ldr r0,=0x167; adds r1,r3,r0` instead of
   folding to `ldr r0,=base+0x167`. Use when ROM computes address as
   base+offset with separate pool loads.

3. **Register pinning + inline-asm scratch**: When `register __asm__("rX")`
   pinning breaks a scratch-register pattern (e.g., `lsls r0,r5,#24`),
   use inline asm with earlyclobber:
   ```c
   int scratch;
   __asm__("lsl %0,%2,#24\n\tasr %1,%0,#23"
           : "=&l"(scratch), "=l"(dst) : "l"(src));
   ```
   (Use `lsl`/`asr`, not `lsls`/`asrs`, in GAS 2.42 inline asm.)

4. **s32 + (s8) cast forces sign-extension**: `s32 v = (s8)func();` emits
   `lsls r0,r0,#24; asrs r1,r0,#24` where pure `s8 v` gets optimized to
   `lsrs` (zero-extend). Use when ROM has the sign-extend but the sign is
   semantically unobservable.

5. **int mask + inline asm AND prevents narrowing**: For `u8 & ~N` where
   ROM does 32-bit `& -N`:
   ```c
   int mask = -N;
   int t = byte;
   __asm__("and %0,%1" : "+l"(t) : "l"(mask));
   ```
   The `int` types + asm prevent the compiler's 8-bit narrowing
   (`& 253`). The mask is CSE-kept across multiple uses.

6. **Inline asm for movs-before-load order**: When ROM does
   `movs r0,#C` BEFORE `ldrb r1,[rX]` (compiler does load-first):
   ```c
   __asm__("movs %0,#C" : "=l"(t));
   f = *p;
   __asm__("and %0,%1" : "+l"(t) : "l"(f));
   ```
   Forces the materialization before the load.

## Files for coordinator

- `/tmp/wave5_blk/HBlank_VCountUpdate_08000978_MATCHED.c` — 0 diffs (old_agbcc)
- `/tmp/wave5_blk/StridedCopy_08000C68_MATCHED.c` — 0 diffs (agbcc)
- `/tmp/wave5_blk/Task_366A8_080366A8_MATCHED.c` — 0 diffs (agbcc)
- `/tmp/wave5_blk/Vec2_CopyMirrored_0800DD08_BLOCKED_2B.c` — 2-byte diff
- `/tmp/wave5_blk/objmask3.c` — mask idiom proof (Obj_AddEntry)
- `docs/wave5_blk_results.tsv` — summary table
- `docs/match_notes_wave5_blk.md` — this file

**Landing notes**:
- HBlank_VCountUpdate: needs old_agbcc Makefile override (like text.c,
  wave3_e_old.c). Verify the `bl _call_via_r0` bytes in the full build
  (minimal harness has the known linker quirk).
- StridedCopy: main agbcc, but uses `register __asm__` pinning and inline
  asm — verify it doesn't break other functions in the TU (keep in its own
  file/section).
- Task_366A8: main agbcc. Corrects wave4_k notes (condition is `if (!v)`).
