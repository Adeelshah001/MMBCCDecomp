# Wave 13 Worker E Match Notes

Worker: Wave 13 batch E (TAG=E). Date: 2026-10-22.
Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` before start.
Toolchain: `mmbcc/tools/agbcc/bin/{agbcc,old_agbcc}`; `arm-none-eabi` 2.42 (GAS 2.42).
Harness: `staging/wave13_E/build.sh` (hardened v3: custom ld script, non-empty
assertions, offset = addr − 0x08000000, exact byte counts, `cmp -l` zero diffs).
Staging: `~/workspace/mmbcc-decomp/staging/wave13_E/`.

**Result: 2 MATCHED, 4 BLOCKED (3 with significant progress).**

Targets were chosen from `docs/match_status.tsv` (status=BLOCKED) that had NOT
been attempted recently (waves 4–10 vintage) and for which the Wave 11–12 new
angles applied. Skipped per task: 0x080244B0, 0x0800BEE0, 0x080241F8,
0x08024384, 0x0800B148 (other workers), Vec2_CopyMirrored, Sram_VerifyCompare,
MainLoop, ChipSlot_Tick (leave-alones).

## MATCHED (2)

### TblHword_11C58 @0x08011C58 (40 B, old_agbcc, 0 diffs) — LANDED

Wave 8-U BLOCKED (40 B table lookup). Behavior: returns `tbl[b*2 + a*32]`
from the u16 table at 0x08173EEC, or 0 if a > 5 or b > 15.

**New angles that cracked it** (all proven necessary via 9 iterations):
1. **Pinned COPY register**: `register u8 ac __asm__("r3")` on the copy of `a`
   (plain primary `u8 aa = a`) forces `adds r3,r0,#0` after the in-place
   extension — defeats the systematic allocator difference (Wave 12 idiom).
2. **Empty volatile barrier** `("" : "+r"(aa))` forces the full `lsls/lsrs #24`
   extension of `a` in r0 BEFORE the copy (compiler otherwise merges the lsr
   into the copy as `lsr r3,r0,#24`).
3. **Non-empty asm templates emitting exact shifts**: the vintage split b's
   extension as `lsls r1,r1,#24` (in place) + `lsrs r0,r1,#24` (extend-move),
   which no C pattern reproduces (compiler either extends fully in r1 or
   moves to r2). Solution: `register u32 braw __asm__("r1")` (uninitialized —
   grabs r1 raw, avoiding the u8→u32 init extension); `"lsl %0,%0,#24"` and
   `"lsr %0,%1,#24"` emit the two instructions verbatim. bc is u32 so the
   later `cmp` needs no re-extension.
4. **`register u8 *tbl __asm__("r2")`** assigned after the checks + empty
   barrier forces the pool load into r2 BEFORE the index shifts (compiler
   otherwise schedules the shifts first).
5. **`register int t __asm__("r1")`** forces `lsl r1,r3,#5`; statement order
   `addr = bc<<1; t = ac<<5; addr += t;` reproduces the exact shift order.
6. **Wave10_H idiom**: `__asm__ volatile("add %0,%0,%1" : "+r"(addr) : "r"(tbl))`
   forces `adds r0,r0,r2` (compiler commutes to `add r2,r2,r0` otherwise).

Staged: `staging/wave13_E/e1_11c58_MATCHED.c` (deterministic across 3 builds).

### IsSpecialChip_3FACC @0x0803FACC (72 B code + 4 B trailing pool, old_agbcc, 0 diffs) — LANDED

Wave 10-L B1 BLOCKED (72 B decision tree). Behavior: returns 1 if chip ID is
in {0x1030} or 0x30..0x36 or {0x3030, 0x2030} or {0x4030}, else 0.

**CORRECTION to docs/match_notes_wave10_L.md B1**: the third large constant
is **0x2030, NOT 0x3020**. ROM bytes at 0x0803FB04 are `30 20 00 00` =
0x00002030; the 0x1030/0x2030/0x3030/0x4030 pattern confirms it. The Wave 10
"combiner does subs r0,#16" observation was an artifact of the wrong constant
in the staged C (0x3030−0x3020=16); with the correct 0x2030 the compiler
emits a proper pool load.

**New angles that cracked it**:
1. **Pinned registers**: `register int a __asm__("r1") = chip` gives
   `lsls r0,r0,#16; lsrs r1,r0,#16` (extend-move fused); then
   `register int b __asm__("r2") = a` gives `adds r2,r1,#0`. Defeats the
   systematic allocator difference (compiler eliminated the b-copy).
2. **Variable-constants** `int lo = 0x30; int hi = 0x36;` defeat the frontend
   fold of `a < 0x30` into `cmp #0x2F; ble`; ROM has `cmp r1,#48; blt`. (The
   frontend only folds literal constants, not variables that the backend
   later constant-propagates.)
3. Opaque `+r` barrier on c3030 (belt-and-braces against combiner).
4. old_agbcc's mid-function pool dump after unconditional branches reproduces
   the ROM pool placement exactly.

Staged: `staging/wave13_E/e2_3facc_MATCHED.c`. Full 76 B extent verified
(72 B code + 4 B trailing 0x4030 pool at 0x0803FB14).

## BLOCKED (4)

### B1. sub_08004398 @0x08004398 (80 B) — allocation + LICM

Struct initializer with fixed-point countdown loop. Best: 88 B (8 over).

**What was tried**: Natural C gives 88 B with the `ldr r0,=0xFFFF0000` correctly
INSIDE the loop (via `register int k __asm__("r0") = 0xFFFF0000;` inside the
loop body — new angle: pinned constant forces the pool load at the use point).
However:
- Prologue allocation diverges systematically: mine puts q→r6/a3→r5/a4→r2,
  ROM has q→r5/a3→r6/a4→r3. Pinning the copies (qq→r5, c3→r6, c4→r3) fixes
  allocation but causes spill code (r8 save/restore, +16 B).
- The `(s16)a3` re-extension (`lsls r0,r6,#16; asrs r3,r0,#16`) is hoisted by
  old_agbcc's LICM; ROM recomputes it each iteration. Tried: opaque `&a3s`
  escape + "memory" clobbers (gives stack reloads, not the r6 pattern);
  register clobbers (too destructive). The vintage compiler simply had weaker
  LICM — likely a version difference, not defeatable via source.

**Precise diff**: 88 vs 80 B; prologue register homes + loop-invariant
re-extension. Needs a compiler version with weaker LICM or .s transcription.

### B2. sub_08042A64 @0x08042A64 (100 B) — allocation

Bounds/overlap check (twin at 0x080459F8). Best: 108 B (8 over).

**What was tried**: Natural C gives 108 B. The compiler NATURALLY emits the
`lsls r1,r1,#24; lsrs rX,r1,#24` (lsl + lsr-move) pattern — no asm needed!
Issues:
- Register homes: mine b→r7/d→r6/base→ip, ROM b→r4/d→r5/base→r7.
  Pinning bb→r4/dd→r5 works for the copies (`lsr r4,r1,#24` ✓) but pushes
  `a` out of r0 and causes base→r7 to clobber it; pinning base→r7 causes r7
  not to be saved (compiler bug?) or r8 spills.
- Offset pooling: using `int off = 0x11ac; off++;` gives a single pool (not
  two), but the compiler puts off in r3 instead of reusing r2.
- ROM pools are 0x02003670/0x11ac (NOT 0x02007036/0x0000ac11 as the Wave 8
  notes state — another typo).

**Precise diff**: 108 vs 100 B; systematic r4/r5/r7 vs r7/r6/ip allocation.
The pinned-copy angle works for b/d but the 4-register interaction (a, b, d,
base) defeats it. Needs different C structure or allocator nudging.

### B3. sub_080030C4 @0x080030C4 (108 B) — load scheduling

Struct copy with fixed-point interpolation. Best: 108 B size match but 80
diffs (structure diverges).

**What was tried**: The ROM does `ldr r2,[r3,#0]` (s[0]), uses r2, then
`ldr r3,[r3,#4]` (s[1], reusing r3). Tried: a/b locals, s[1] on-demand,
explicit temporaries for the `((s16)r5+120)` computation. The compiler either
loads both upfront or reassociates the arithmetic (`sub r1,r1,#120` before the
(s16)r5 extension, vs ROM's `lsls; asrs; adds #120; subs` as a unit).
The else-branch store order (d[1],d[0],d[3],d[2],d[5],d[4]) was reproduced.

**Precise diff**: Load scheduling and arithmetic reassociation. Needs exact
load scheduling control.

### B4. sub_0800D3A0 @0x0800D3A0 (118 B) — not attempted

Complex config function (Wave 8-U). ROM uses r4,r3,r5 for variables, r6 for
poolA (0x02004F80). Has a dead `if (r3==2)` branch and `(u8)(-(s8)r4)`.
Not attempted due to time; the pinned-copy + opaque-pool angles may apply
but the 118 B size and interacting constraints make it a hard target.

## New idioms discovered

1. **Non-empty asm templates for exact shifts**: `"lsl %0,%0,#24"` /
   `"lsr %0,%1,#24"` emit verbatim Thumb shifts when the vintage's
   extension placement (in-place lsl + cross-register lsr) is unproducible
   in C. Use uninitialized pinned registers to grab raw values.
2. **Variable-constants defeat frontend folds**: `int lo = 0x30;` used in
   `if (a < lo)` gives `cmp #48; blt`, not `cmp #0x2F; ble`. The frontend
   only folds literal constants.
3. **Pinned constant in loop forces pool load**: `register int k
   __asm__("r0") = 0xFFFF0000;` inside a loop body emits `ldr r0,[pc,#..]`
   at the use point, defeating LICM hoisting of the constant.
4. **Corrections to prior notes**: 0x0803FACC uses 0x2030 (not 0x3020);
   0x08042A64 uses 0x02003670/0x11ac (not 0x02007036/0x0000ac11).

## Environment note

`mktemp -d /tmp/wave13_E/job_XXXXXX` fails (no /tmp/wave13_E dir); fixed
harness to use `/tmp/w13e_job_XXXXXX`.
