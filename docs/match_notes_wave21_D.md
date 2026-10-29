# Wave 21-D Match Notes (Worker D)

## Matched (6)

### 0x08010E7C (36 B) — F_08010E7C, main agbcc
Setup_08010EC4 wrapper, 5th arg 0. Twin of 0x08010EA0.
Landed: src/w21d_08010e7c.c.

### 0x08010EA0 (36 B) — F_08010EA0, main agbcc
Same wrapper, 5th arg 1. Twin of 0x08010E7C.
Landed: src/w21d_08010ea0.c.

### 0x08010270 (42 B) — F_08010270, main agbcc + FIXALIGN1
Setup_0801029C wrapper: `(b, a==0?1:3, (s16)c, (s8)d)`.
FIXALIGN1: per-file sed replaces ALL occurrences (exact 42 B section).
Landed: src/w21d_08010270.c.

### 0x080439D8 (184 B + 12 B pool) — DrawObj_080439D8, old_agbcc
Renders via 3× GatedDispatch + Gfx_BlitRequest.
idx from `p[0x46A9]>>4 + p[0x46AA]`.
Pools: 0x46A9, 0x08232D84, 0x08232DF0.
Landed: src/w21d_080439d8.c.

**New idioms:**
- **Codegen-shaped callee extern**: declare callee `(u8,s8,s8,s8,u8)->u32`
  (ABI-identical) so s8 args keep entry sign-extension and the call yields
  a word (gcc emits post-call lsl/lsr extend for u8-typed call results;
  ROM lacks it). Wrapper definitions return u32 for the same reason;
  observed callers extend the result themselves (e.g. 0x0800ECF8
  sign-extends = s8 use).
- **old_agbcc scheduler** emits ROM's `ldrb; lsr #4` *before* second address
  computation (main agbcc interleaves it late).
- **Pinned r4/r6** (`register u8 *r4 __asm__("r4")`,
  `register u32 zero __asm__("r6")`) reproduce ROM allocation (idx→r7, v→r5);
  r7 is pushed here so r7-pin risk noted but avoided — sub-word pins break
  codegen, u32 pins to pushed regs are safe.
- **Empty-asm barrier** `__asm__ volatile("": "+r"(tbl))` pins a pool load
  before a call.

### 0x08024F30 (20 B + 4 B pool) — F_08024F30, main agbcc
`F_0802611C(((u8 **)0x02007090)[5], a)`.
**Idiom:** empty-asm barrier on pool base prevents gcc from folding base+20
into the pool constant (ROM pools 0x02007090, uses `ldr r0, [r0, #20]`).
Landed: src/w21d_08024f30.c.

### 0x08024F70 (20 B + 4 B pool) — F_08024F70, main agbcc
`Loop3_08026144(((u8 **)0x02007090)[5], a)`. Sibling of F_08024F30.
Landed: src/w21d_08024f70.c.

## Blocked (2)

### 0x080405D8 (180 B) — 1 diff, GAS limitation
`adds r0,r0,r1` (0x1840) vs ROM `adds r0,r1,r0` (0x1808). 179/180 correct,
semantically identical. Sibling of DrawObj_080439D8 (TblStride_24818,
r4[20]/[21], pools 0x46A8/0x082329E0/0x08232B90).
Inline-asm forced the ldrb order; the adds operand order is unfixable under
GAS (GAS rejects `adds` mnemonic with Rd==Rm; `.short` possible but
communicating the result needs extra moves).
Staging: staging/wave21_D/w21d_080405D8.c.

### 0x080119DC (48 B) — 5 diffs, scheduler artifact
Structure solved. Second if-block:
- ROM: `ldr r0,[r4,#8]; ldrh r1,[r1,#14]; adds r0,r1,r0`
- Mine: `ldrh r0,[r1,#14]; ldr r1,[r4,#8]; adds r0,r0,r1`
Scheduler load-order + adds-operand-order artifact. Multiple C formulations
tried (volatile reload, f8 temp, h+f8 order, scoped f0) — all preserve the
5-diff pattern or worsen allocation.
Staging: staging/wave21_D/w21d_080119DC.c.

## Attempted / Deferred

### 0x08045838 (216 B)
Complex duplicated-switch config function (2× blocks, bit manipulations,
ShiftPair_Copy_800C calls). Attempt at 129 diffs (switch version); needs
register-allocation + sequencing work. Deferred.
Staging: staging/wave21_D/w21d_08045838.c.

### 0x08011A78 (78 B)
State-init function with TableWalk_080113F4 call. Attempted with pinned r1/r2/r6
(49-61 diffs). Register allocation + branch structure not yet solved. Deferred.
Staging: staging/wave21_D/w21d_08011A78.c.

## New Idioms for Catalog

1. **Codegen-shaped callee extern** — declare external callees with
   `(u8,s8,s8,s8,u8)->u32` signature (ABI-identical to actual) to preserve
   s8 entry sign-extension and avoid post-call lsl/lsr extends.
2. **Barrier against pool folding** — `__asm__ volatile("": "+r"(base))`
   prevents gcc from folding `base+const` into the pool constant, forcing
   ROM's `ldr reg, [reg, #imm]` pattern.
3. **Volatile forces redundant loads** — `*(volatile u16 *)` forces a reload
   even when gcc would reuse a register (matches ROM's duplicated ldrh).
