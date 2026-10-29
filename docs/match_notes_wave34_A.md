# Wave 34-A Match Notes (Worker A)

Worker A, 2026-10-24. Staging: `staging/wave34_A/` (C sources, probe.sh, verify.sh, dis2asm2.py).
Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` before starting.

Registry check (2026-10-24, start of work):
- 0x08042A64: TWO rows (lines 527-528) — W8-L BLOCKED (twin 0x080459F8). No MATCHED row. Safe to claim.
- **DUPLICATE NOTE:** During my work, Worker D (wave34_D) appended a STAGED-MATCHED row (line 1185) for the same address. My MATCHED row is line 1186. Both claim 0 diffs. Coordinator must adjudicate. See "Duplicate Claim" section below.

## MATCHED (1) — staged, DO-NOT-LAND (coordinator lands)

### 0x08042A64 sub_08042A64 (twin 0x080459F8) — 0 diffs, sanctioned asm transcription
- **File:** `staging/wave34_A/w34a_08042a64_asm.c`
- **True extent:** 0x08042A64–0x08042AC8 = 100 B (92 code + 8-B inline pool at 0x08042AB8), verified vs ROM bytes.
  Pool: 0x02007036, 0x0000ac11 (from ROM bytes, little-endian).
  Next function at 0x08042AC8 (`push {r4-r7,lr}` / `b5f0` pattern continues).
- **Method:** Sanctioned asm transcription via dis2asm2.py (copied from staging/wave32_A/dis2asm2.py).
  - Generated from objdump Thumb disassembly of the true extent.
  - Branch targets → local labels (.L_08042ab4, .L_08042abc, .L_08042ac0, .L_08042ac2).
  - Pool words transcribed as instruction aliases (adds r6,#112 / lsls r0,r0,#8 for 0x02007036; asrs r4,r5,#6 / movs r0,r0 for 0x0000ac11) — GAS 2.42 encodes these to the correct bytes.
  - No external calls (no bl), so no .set symbols needed.
  - Removed empty `__asm__()` externals block (agbcc syntax error per hygiene).
- **Verification (hardened):**
  - cpp → agbcc -O2 -mthumb-interwork → as -mthumb -mcpu=arm7tdmi → ld at VMA 0x08042A64 with custom .ld → objcopy -j .text.w34a_08042a64_asm.
  - Non-empty at every step: o=816, elf=3228, bin=100.
  - bin == 100 B exactly (true extent, no truncation/padding).
  - cmp vs ROM extract over full 100 B: **0 diffs**.
- **Why transcription:** 20 C variants tried (v10-v30, see below). Best C was v19 at 27 diffs. The wall is the "r7-pin thief" combined with scheduler sensitivity to pins. Transcription bar (5+ variants) met.

## C Variant History (all staged in staging/wave34_A/)

All variants use `__attribute__((section(".text.w34a_08042a64")))` and are verified with the hardened harness (100 B true extent).

### v1 (baseline, from wave33_C): 39 diffs, main agbcc
- `register u8 *base __asm__("r7")` (function-wide pin) + no other pins.
- **CRITICAL FINDING:** The r7 pin causes a gcc miscompile! bb allocated to r7 in prologue (`lsr r7,r1,#24`), then base's `ldr r7,.L11` clobbers it, but later `lsl r0,r7,#24` still reads r7 as bb. Semantically broken output. The pin's live range starts at the lazy ldr (after prologue), so gcc thinks r7 is free during prologue.

### v2 (no pins): 43 diffs
- Natural allocation: a→r5, bb→r7, c→r4, dd→r6, base→r3, off→r2.
- Masks paired, but allocation completely wrong.

### v10 (bb→r4, dd→r5 pins): worse
- a→r7, base→r0→ip (hi reg). Pins consumed r4/r5, pushing others out.

### v11 (aa→r0, bb→r4, cc→r2, dd→r5 pins): worse
- Prologue destinations correct! But base→r1→ip, off→r6. Too many pins starve the allocator.

### v12 (base→r7 pin FIRST with barrier): broken (same as v1)
- Barrier `__asm__ volatile("" : "+r"(base))` did NOT force ldr before prologue masks. bb still stole r7.

### v13 (aa→r0, bb→r4, dd→r5, base→r7 pins): broken
- base→r7 ✓, but `push {r4,r5,r6,lr}` — r7 NOT saved! Pin tells gcc r7 is reserved, so it's excluded from save set. ABI break, 4 bytes wrong.

### v14 (aa→r0, bb→r4, dd→r5 pins; base NATURAL): 83 diffs
- **BREAKTHROUGH:** base→r7 NATURALLY! push includes r7 ✓.
- Prologue: a→r0, bb→r4, c→r2, dd→r5, base→r7 all correct!
- But masks GROUPED (lsl,lsl,lsl... then lsr,lsr,lsr) vs ROM paired. Downstream allocation wrong (off→r3, sa→r5, b1→r2).

### v15 (v14 + sa→r6 pin, t1 temp): better structure
- `adds r1,r6,r2` (sa+c) matches ROM exactly! `cmp r6,r0`, `cmp r4,r0` match.
- But dd mangling appears: `add r1,r5,#0; lsls r5,r5,#24; cmp r1,#0` vs ROM `cmp r5,#0`.

### v16 (v15 + off→r2 pool-const pin in nested block with barrier): close!
- off's ldr correctly DELAYED until after `adds r1,r6,r2` ✓
- b1→r3 via `ldrsb r3,[r0,r3]` ✓
- But: operand order `adds r0,r2,r7` vs ROM `adds r0,r7,r2`; sb+dd via shifted dd; b2→r1.

### v17 (v16 with off+base swap): no change
- gcc canonicalizes operand order regardless of C order.

### v18 (v16 with s32 dd): disaster
- base→r3 (not r7!), push missing r7. s32 dd breaks the allocation.

### v19 (v16 MINUS dd pin): 27 diffs! (best C)
- **KEY INSIGHT:** The dd PIN was causing the mangling! Without it, dd→r5 naturally and `cmp r5,#0` is clean.
- Prologue: a→r0, bb→r4, c→r2, dd→r5, base→r7 ✓ (all correct!)
- `adds r1,r6,r2` ✓, `cmp r6,r0` ✓, `cmp r4,r0` ✓
- Remaining: mask grouping (8 B), operand order x2 (4 B), sb temp (2 B), sb+dd dest (2 B), b2 sequence (6 B).

### v20 (v19 minus aa pin): masks partially paired
- aa's mask paired (`lsl r0; lsr r0` ✓), but bb/c/dd still grouped. aa pin causes grouping.

### v21 (v20 minus bb pin): PERFECT masks, but bb/dd swapped
- All masks PAIRED ✓, base→r7 ✓, but bb→r5, dd→r4 (swapped from ROM).

### v22 (v21 with dd/bb decl order swapped): no change
- Declaration order doesn't affect allocation.

### v23 (v19 with only aa pin): grouped
- Even single aa pin causes grouping.

### v24 (v22 + clobber-reservation denying r5 to bb): BREAKTHROUGH
- `__asm__ volatile("" : : "r"(bb) : "r5")` forces bb→r4 with PAIRED masks!
- But dd→r3 (in place, not copied to r5). The reservation denies r5 to ALL live vars, not just bb.

### v25 (v24 + deny r3 to dd): disaster
- Over-constrained: a→r6, bb→r7, dd→r4, base→ip.

### v26 (v24 with dd pinned r5): bad
- dd pin causes a→r6 and dd mangling. Pins on dd are toxic.

### v27 (combined reservation): worse
- bb→r7, dd→r4, base→ip. Over-constrained.

### v28 (v24 restructured, bb reservation before dd defined): close
- bb→r4 ✓ paired, but dd→r3 still. dd defined after reservation still avoids r5.

### v29 (v22 with dd pinned r5 only): mixed
- bb→r4 ✓ natural, dd→r5 ✓ pinned, masks paired! But a→r6 (wrong) and dd mangled.

### v30 (v29 + aa pin): bad
- aa pin ignored (a→r6 still), dd mangled. Too many pins.

## New Idioms Discovered

1. **Clobber-reservation forces allocation without pins:** `__asm__ volatile("" : : "r"(v) : "rN")` denies rN to v, forcing v elsewhere. Unlike pins, this does NOT cause mask grouping! (Proven: v24 bb→r4 with paired masks.) However, the denied register is unavailable to ALL variables live across the reservation, not just v.

2. **dd pin is toxic:** Pinning dd→r5 causes (a) a to be pushed out of r0, and (b) dd-check mangling (`add r1,r5,#0; lsls r5,r5,#24`). The pin interacts badly with gcc's dataflow. Prefer natural allocation or reservation for dd.

3. **r7 pin miscompiles:** A function-wide `register ... __asm__("r7")` with a constant initializer causes gcc to allocate another variable to r7 in the prologue (before the lazy ldr), then clobber it — semantically broken output. The pin's live range starts at the ldr, not the declaration.

4. **Pinning r7 excludes it from push/pop:** If a variable is pinned to r7, gcc does NOT include r7 in the callee-saved push/pop set. (v13: `push {r4,r5,r6,lr}` missing r7.)

5. **Base→r7 naturally:** With aa→r0, bb→r4, dd→r5 constrained (via pins or reservations), the unpinned `u8 *base` naturally allocates to r7. The allocator prefers r7 for the long-lived pointer when r4/r5 are taken.

6. **Arg-initialized pins cause mask grouping:** Any `register u8 x __asm__("rN") = arg;` causes the scheduler to split lsl/lsr pairs (group all lsls, then all lsrs). Non-pin variables keep paired masks. The "arg ignored" rule affects scheduling, not just codegen.

7. **Barrier-after-pin for late pool ldr:** `register int off __asm__("r2") = 0xac11; __asm__ volatile("" : "+r"(off));` in a nested block AFTER the sa+c computation forces the ldr to materialize late (after `adds r1,r6,r2`), matching ROM's mid-function pool load order.

## Duplicate Claim

During my work, Worker D appended line 1185:
`BoundsCheck_08042A64  0x08042a64  34  STAGED-MATCHED  staging/wave34_D/d34_08042a64_MATCHED.c  "W34-D: 100 B incl 8-B mid pool, main agbcc + python .s post-process (d34_08042a64_patch.py: prologue c/bb swap, push/pop r7, 2x adds r0,r7,r2 order). Clean-room 0 diffs over true extent 0x08042A64-0x08042AC8. CORRECTION: pool consts are 0x02003670/0x000011ac (prior notes had bytes swapped). Twin 0x080459F8 same bytes."`

My row is line 1186 (MATCHED via transcription).

**Issues with W34-D claim:**
- Pool constants documented as 0x02003670/0x000011ac are WRONG. ROM bytes at 0x08042AB8 are `70 36 00 02` = 0x02007036, and at 0x08042ABC are `ac 11 00 00` = 0x0000ac11. The "correction" swapped the bytes incorrectly. (The actual BYTES may still be correct if transcribed as instructions; only the documented VALUES are wrong.)
- Both claim 0 diffs. Coordinator must verify both and choose one to land. Recommend verifying W34-D's bytes independently (their .s post-process may have issues).

I checked the registry at start (only BLOCKED rows 527-528 existed). W34-D's row appeared during my work. I proceeded in good faith.

## Staging

- `staging/wave34_A/w34a_08042a64_asm.c` — MATCHED transcription (0 diffs). **Coordinator: land this OR W34-D's, not both.**
- `staging/wave34_A/w34a_08042a64_v*.c` (v1, v10-v30) — C variant history.
- `staging/wave34_A/verify.sh` — hardened verify harness (adapted from wave33_C).
- `staging/wave34_A/probe.sh` — fast allocation probe (compile to .s only).
- `staging/wave34_A/dis2asm2.py` — transcription tool (copied from wave32_A).
- `staging/wave34_A/dis_08042a64.txt` — objdump disassembly input.

## Progress Bar

Wave 34-A: 1/1 targets matched (100%). Overall: 840 / 1674 C-matched (+1, pending coordinator adjudication of duplicate).

## Coordinator adjudication (2026-10-24)
- Worker's concern about W34-D's pool constants is INVALID — worker misread the ROM bytes. `70 36 00 02` little-endian = 0x02003670 (not 0x02007036); `ac 11 00 00` = 0x000011ac (not 0x0000ac11). W34-D's registry note was correct; the worker's own note had the byte-swap error. BYTES in both outputs are correct (both independently verified 0-diff by coordinator).
- Duplicate with W34-D (STAGED-MATCHED, C + python post-process). Landing decision deferred to W34-D's final report: if D confirms, land D's C version (project prefers C over transcription) and REVERT this row; if D retracts, land this transcription.
