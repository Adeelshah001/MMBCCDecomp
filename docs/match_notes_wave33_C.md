# Wave 33-C Match Notes (Worker C)

Worker C, 2026-10-24. Staging: `staging/wave33_C/` (C sources, verify.sh).
Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` before starting.

Registry check (2026-10-24):
- 0x080221cc: ONE row (line 1164) — W32-D BLOCKED. No MATCHED row. Safe to claim.
- 0x08042A64: TWO rows (lines 527-528) — W8-L BLOCKED (twin 0x080459F8). No MATCHED row.

## MATCHED (1) — staged, DO-NOT-LAND (coordinator lands)

### 0x080221CC ChipInit_080221CC — 0 diffs, old_agbcc + 2-byte sed patch
- **File:** `staging/wave33_C/w33c_080221cc_MATCHED.c` (identical to v17)
- **True extent:** 0x080221cc–0x08022290 = 196 B (172 code + 24 pool), verified vs ROM bytes.
  Pool: 6 words at 0x08022278: 082270b0, 081705b0, 020031e4, 082270bc, 081738f2, 082270d4.
  Next function at 0x08022290 (`push {r4,r5,r6,r14}`).
- **Compiler:** old_agbcc -O2 -mthumb-interwork (main agbcc gave 4 diffs; old gives 2).
- **Patch (Makefile sed):**
  ```
  sed -i 's/ldr\tr3, \.L4+8/ldr\tr1, .L4+8/; s/add\tr0, r0, r3/add\tr0, r0, r1/' $(@:.o=.s)
  ```
  Changes `ldr r3,[pc]` → `ldr r1,[pc]` for the 0x020031e4 pool (3rd word) and the
  corresponding `adds r0,r0,r3` → `adds r0,r0,r1`. 2 bytes. Without patch: 2 diffs.
- **Behavior:** Straight-line chip init: clears s+108, sets bits in s+10 via two
  separate ORRs, calls ChipSlot_Setup/ChipSlot_IncUse, computes idx from packed
  tables, updates s+69 flags, writes s+34/80/84, calls BlendCopy_080224E4, clears s+19.
- **Decisive idioms:**
  - **sp pinned to r5** (`register u8 *sp __asm__("r5") = s;`) gives prologue
    `push {r4,r5,r14}` + `adds r5,r0,#0` (pinned copies emit as `adds`, not `mov`).
  - **Pool-const pins with volatile barriers** force ldr-first scheduling:
    `register u32 b270 __asm__("r2") = 0x082270b0;` + `__asm__ volatile("" : "+r"(b270));`
    The barrier is essential — pin alone doesn't prevent scheduler reordering the
    ldrb before the ldr.
  - **Opaque barrier on copy defeats coalescing** (idx clamp): `int t = idx;`
    `__asm__ volatile("" : "+r"(t));` forces `ands r1,r0; adds r0,r1,#0; cmp r0,#3`
    (ROM's copy-before-compare shape). Without barrier, gcc coalesces t/idx.
  - **Opaque barrier defeats -13 folding:** `int m = -13;` +
    `__asm__ volatile("" : "+r"(m));` gives `movs r0,#13; negs r0,r0` instead of
    `movs r0,#243` (& 0xF3). Barrier must be AFTER the shift/address computations
    to get ROM's order (lsls, then movs/negs, then ldrb).
  - **Initialized pins for c** (`register u8 c __asm__("r1") = *(u8 *)(sp+17);`)
    control the ldrb destination register. UNINITIALIZED pins cause save/restore
    bloat — pins MUST initialize at declaration.
  - **tbl-first restructuring** defeats evaluation-order issues: compute
    `tbl = *(u16 *)(b270 + 2*c)` as separate variable before `(c+3)|tbl`, forcing
    `2*c` before `c+3` in the instruction stream.
  - **Dummy reads keep variables live:** `__asm__ volatile("" : : "r"(c));` after
    a store prevents gcc from clobbering c with in-place ops (`lsls r2,r2,#2`
    → `lsls r0,r2,#2`), and prevents pinned-base clobbering (`movs r1,#0` → `movs r3,#0`).
  - **`(off + base)` vs `(base + off)`** — operand order affects `adds` encoding
    (`adds r0,r0,r1` vs `adds r0,r1,r0`); commutative but not byte-identical.
  - **old_agbcc for allocator-sensitive code:** main agbcc gave 4 diffs (b270
    `adds`/`ldrh` order wall); old_agbcc's scheduler produced ROM's order.
- **Variant history:** v5 (135 diffs, main) → v6 (27, +barriers) → v7 (159, bad c pins)
  → v8 (160, init pins) → v9 (18, tbl pin) → v10 (8, main; 2, old) → v17 (2, old, no idx pin)
  → MATCHED (0, old + sed). v11-v16 explored addr/ptr formulations (all worse).
- **Landing note:** Makefile rule needs old_agbcc + the 2-byte sed patch above.
  No `.short` pad needed (196 B total, no alignment issue). The `.set` directives
  for ChipSlot_Setup (0x0800d6e0), ChipSlot_IncUse (0x0800d9ec), BlendCopy_080224E4
  (0x080224e4) are in the .c; strip `.globl`+`.set` for real T-symbols per hygiene
  (nm-check GLOBAL).

## STILL BLOCKED

### 0x08042A64 sub_08042A64 (twin 0x080459F8) — best 39 diffs (v1, main agbcc)
- **File:** `staging/wave33_C/w33c_08042a64_v1.c` (copied from wave32_C v1, section renamed)
- **True extent:** 0x08042A64–0x08042AC8 = 100 B, with 8-B pool inline at 0x08042AB8
  (mid-function: 02007036, 0000ac11). Verified via disassembly.
- **ROM register map:** b→r4, d→r5, base→r7, sa→r6; c stays r2, a stays r0.
  Prologue `push {r4,r5,r6,r7,r14}`.
- **Semantics:** Bounds/overlap check. If (c==0||d==0) return 0. sa=(s8)a, b1=*(s8*)(base+0xac11);
  if (sa+c <= b1) return 0. sb=(s8)b, off++, b2=*(s8*)(base+off); if (sb+d <= b2) return 0.
  if (sa >= b1+28) return 0. if (sb < b2+20) return 1 else return 0.
  Note: `ldrsb` with r3/r2 zero-index (`movs r3,#0; ldrsb r3,[r0,r3]`), `off++` reuses
  r2 (`adds r2,#1`), b1/b2 stay live in r3/r2 for the final compares.
- **Walls:**
  1. **Register allocation:** Pinning base→r7 causes the "thief" — another variable
     (b/bb) also allocates to r7, conflicting. Pinning bb→r4 + dd→r5 + base→r7
     gets bb/dd/base correct but pushes a→r6 (wrong). Unpinned gives all-wrong
     allocation. The r7 pin is fragile (brief: "never pin r7", "marks r7 fixed").
  2. **Mid-function pool:** 8-B pool at 0x08042AB8 (not trailing). The `ldr r7,[pc]`
     (base) comes BEFORE the early-return cmps; the `ldr r2,[pc]` (off=0xac11) comes
     much later (after sa+c). Pool-barrier mechanism relevant but hard to control.
  3. **`off++` scheduling:** ROM reuses r2 for off (`adds r2,#1`), then uses r2 for
     b2 (`ldrsb r2,[r0,r2]` with r2=0 index? actually `movs r2,#0` first). The
     `off` variable must stay in r2 across the b1 load.
- **Tried:** v1 (39, base pin r7); v2 (43, no pins); v3-v5 (83-85, bb/dd pins);
  v6 (42, no bb/dd); v7 (43, extern base); v8 (88, bb/dd pins only); v9 (84, sa pin).
  old_agbcc did not help (v1: 39 both).
- **Recommendation:** The allocation wall (r7 pin thief) needs a new idiom.
  Possible: block-scoped base pin covering ONLY the two load regions, or a
  clobber-reservation to deny r7 to bb. The `sa→r6` (asrs in-place) and
  `sb→r4` (asrs in-place) also need attention.

## New Idioms Discovered

1. **Barrier-after-pin forces ldr scheduling:** A pool-const pin alone does NOT
   guarantee the `ldr` comes before dependent `ldrb`s — gcc's scheduler reorders.
   Adding `__asm__ volatile("" : "+r"(pinvar));` immediately after the pin forces
   the ldr to materialize at that point. (Proven: b270, base, t1/t2 pins.)
2. **Initialized pin controls ldrb destination:** `register u8 c __asm__("r1") = *(u8*)...;`
   puts the load into r1. Uninitialized pins (`register u8 c __asm__("r1"); c = ...;`)
   cause save/restore bloat as gcc treats the pin as must-preserve.
3. **Pinned copies emit as `adds`:** `register u8 *sp __asm__("r5") = s;` gives
   `adds r5,r0,#0` (not `mov r5,r0`), matching ROM's lo-reg copy idiom.
4. **Dummy input-only asm keeps vars live:** `__asm__ volatile("" : : "r"(c));`
   (no outputs) is a pure liveness anchor — prevents in-place clobbering and
   CSE without emitting code. Distinct from `"+r"` which forces a copy.
5. **Operand order in commutative ops matters:** `(off + base)` vs `(base + off)`
   give different `adds` encodings (`adds r0,r0,r1` vs `adds r0,r1,r0`).
6. **old_agbcc as scheduler alternative:** When main agbcc's instruction scheduler
   produces a wrong order that resists C restructuring, old_agbcc may produce
   ROM's order (b270 `adds`/`ldrh` wall solved by switching compilers, not C).

## Progress Bar

Wave 33-C: 1/2 targets matched (50%). Overall: 824 / 1674 C-matched (+1).
