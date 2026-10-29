# Wave 25-A Notes: Rect-fill family (0x08006AD8 priority)

## Summary

**Status:** All four BLOCKED. **Major breakthrough:** cracked the prologue wall
for 0x08006AD8 with a new idiom — **inline-asm prologue** (adapted from the
w15c MaskWrite23 precedent). Best candidate `final_08006AD8_v17.c` emits a
byte-perfect prologue *instruction sequence* (35 insns in exact ROM order),
correct 768B size, and the previously-missing `mode=0` store. Remaining wall:
frame 44 vs ROM 40 (one extra spill slot from a body priority inversion).

## The breakthrough idiom: inline-asm prologue

**Problem:** The rect-fill prologue needs `ctx→r6`, `b→r9`, `d→r8`, `pa→sl`
with spills for `a/c/e`, in EXACT ROM order (ctx-copy BEFORE a-spill). Pinned
C copies (`register ... __asm__("r6") = ctx`) get the registers right but emit
AFTER `assign_parms`, wrong order. Natural allocation gets the order right but
wrong registers (ctx→r8, b→r5, d→r6).

**Solution (w15c precedent):** Emit the prologue as a single `__asm__ volatile`
block. Key tricks:
1. **Params are UNUSED in C** — referenced only as hardcoded `r0`/`r1`/`r2`/`r3`
   and `[sp,#72]`/`[sp,#76]` in the template. No `"r"` inputs for params.
   This suppresses `assign_parms` entirely (no param homes emitted).
2. **Outputs tie C vars to regs/slots:** `"=r"` for pinned regs (r6/r9/r8/sl),
   `"=m"` for spill slots (s_a/s_c/s_e). The compiler allocates the stack
   slots; the template uses `%0` etc., so prologue and body stay consistent.
3. **Two asm blocks** (10-operand limit): Block 1 does ctx→r6, a-spill, d/e
   loads, b→r9, c-spill, d→r8, e-spill, pa→sl. Block 2 does X=0, Y=50,
   mode=0, W=0xB000 in exact ROM order. (Block 2 was needed because the
   `mode=0` store was dead-store-eliminated when done in C.)
4. **Nested block** for body locals, so their inits emit AFTER the asm blocks.

**Result (v17):** Prologue bytes 1-70 match ROM's instruction sequence
exactly, except the frame `sub sp,#44` vs `#40` (the one remaining diff in
the prologue). The `[sp,#72]`/`[sp,#76]` hardcodes are correct for frame=40;
with frame=44 they load from the wrong address, but the BYTES match.

## What was tried (0x08006AD8)

- **v1 (pinned copies):** ctx_c→r6, b_c→r9, d_c→r8, pa→sl correct, but c→r5,
  e→r7 (should spill), frame 44. Order wrong (pins after assign_parms).
- **v2 (pins + c/e live-range extension):** c/e spill correctly via end-of-function
  `__asm__("" : : "r"(c/e))`, but +8B reload bloat at epilogue, frame 48.
- **v3 (`"m"` constraint):** Worse — sub-word stack slots ([sp,#0] halfword).
- **v5 (natural baseline):** ctx→r8, b→r5, c→r7, d→r6, e→r9. Order right, regs wrong.
- **v6 (extend b):** b spilled (too much).
- **v7-v9 (asm prologue attempts):** Hit the 10-operand limit; learned to hardcode
  regs and avoid `"r"` inputs (suppresses assign_parms).
- **v10 (nested block):** Correct order! Frame 48.
- **v11-v13 (body pins):** Pinning dst→r5, m2→r7, hs→r8 causes body starvation
  (too many pins → extra spills like w2). Sub-word (u8) pins NOT honored.
- **v14 (m2 dummy-use boost):** No effect.
- **v17 (X/Y/mode/W in asm Block 2):** 768B correct size, mode=0 store present,
  655 diffs (mostly from frame-shifted stack offsets).
- **v18-v21:** Various pin/dummy-use/inline attempts; whack-a-mole (fixing one
  spill causes another). v21 (inlined m2) was worse (776B).

## The remaining wall (precise)

**Frame:** 44 (11 slots) vs ROM 40 (10 slots). 
- Mine spills: s_a(#0), s_c(#4), s_e(#8), X(#12), Y(#16), mode(#20), W(#24),
  flag(#28), i(#32), m1(#36), m2(#40).
- ROM spills: a(#0), c(#4), e(#8), X(#12), Y(#16), mode(#20), W(#24), flag(#28),
  m1(#32), b16(#36).
- **Difference:** I spill `i` and `m2`; ROM spills `b16`. (hs is in r8 in both
  via the r8v reuse, or spills in some variants.)
- **Root cause:** Priority inversion. `b16` (2 refs, short range) gets a reg in
  mine but spills in ROM; `i` (loop counter, many refs) and `m2` (4 refs) spill
  in mine but get regs in ROM. Pins fix specific regs but starve the body
  (5-6 pins leave only r4/r5 free, body needs more). Dummy-use tuning either
  does nothing or causes spill cascades.

**Body:** With the frame fixed, the body allocation (dst→r5, m2→r7, hs→r8)
  should follow, but the priority inversion must be solved first.

## Recommendations for next worker

1. **Use the inline-asm prologue idiom** (`final_08006AD8_v17.c`) as the base.
   It solves the prologue completely. Do NOT go back to C pins.
2. **Attack the ONE extra spill slot.** Ideas not yet tried:
   - Merge `b16` and `hs` into one variable (they're both u32, used in sequence).
   - Change `i` from u8 to u32 (or pin to r4 with u32 — the u8 pin failed).
   - Restructure the loop to avoid spilling `i`.
   - Use `__attribute__((noinline))` or other hints (unlikely to help).
3. **Sibling transfer:** The idiom should apply directly to 0x08007134,
   0x080065BC, 0x08006374. Their prologues are decoded in W24-A notes.
   0x08007134 is the best next target (480B, prior best 426 diffs).

## Files

- `staging/wave25_A/final_08006AD8_v17.c` — best candidate (768B, perfect prologue).
- `staging/wave25_A/v*.c` — progression (v1..v21, see above).
- `staging/wave25_A/harness.sh` — build/verify harness (fixed `-j .text` for
  ld-merged sections).
- All `.s/.o/.bin/.rom/.dis` intermediates kept for inspection.

## Verification

ROM SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` before starting.
All four functions were BLOCKED in the registry (none skipped). No landing
attempted (staging only, per DO-NOT-LAND).
