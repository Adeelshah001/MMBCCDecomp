# Wave 34-B Notes: ChipSlot_Tick Deep Retry

Worker B, 2026-10-24. Staging: `staging/wave34_B/`. Task: ChipSlot_Tick @
0x0800D9FC (true extent 0x0800D9FC–0x0800DB40 = 324 B). Started from W33-D
v8 (190 diffs, main agbcc).

## RESULT: BLOCKED — 131 diffs (best: w34b_d9fc_v8.c, old_agbcc)

**Major breakthrough: old_agbcc is the correct compiler.** The W33-D v8 used
main agbcc. Switching to old_agbcc immediately fixed the "mysterious" r7
allocations (s30→r7, pairs→r7), the movs-before-ldrb order, and the ldrb-r1
for p48[25] — all of which main agbcc could not produce. old_agbcc also
naturally emits `ldrb r1,[r5,#10]; lsrs r0,r1,#5` for p48[25].

**Regions now PERFECT (0 diffs):**
- Prologue/epilogue: `push {r4-r7,lr}; mov r7,r8; push {r7}` ... `pop {r3};
  mov r8,r3; pop {r4-r7}; pop {r0}; bx r0` ✓
- Diamond (then/else/join with volatile "+r" barrier) ✓
- p48[25]: `ldrb r1,[r5,#10]; lsrs r0,r1,#5; movs r1,#1; ands r0,r1` ✓
- Region D (e/jj block): `adds r0,#116; ldr r2,[r5,#112]; ldrb r0;
  lsls r1,r0,#2; adds r1,r1,r2; ...; ldrb r0; lsls/asrs #24; ldr r1,[r1];
  lsls r0,#1; adds r0,r0,r1; ldrb r0; strb r0,[r6,#26]` ✓
- Region E (sj): `ldr r2,[pc]; mov ip,r2; ldrb r3,[r5,#28]; adds r0,r3,r2;
  movs r1,#0; ldrsb r1,[r0,r1]; movs r0,#1; negs r0,r0; cmp r1,r0` ✓
- Region F (p26/s30): `ldrb r2,[r6,#26]; adds r4,r2,#0; ldrb r7,[r5,#30];
  cmp r7,r2` ✓
- Region G (ptrA): `ldr r1,[pc]; lsls r0,r3,#2; adds r0,r0,r1; ldr r1,[r0];
  ldrb r3,[r5,#29]; lsls r0,r3,#2; adds r0,r0,r1; ldr r1,[r0];
  strb r2,[r5,#30]; ldr r0,[r6,#8]; cmp r0,r1; beq; str r1,[r6,#8]` ✓
- Region H start: `lsls r4,r4,#3; adds r4,r4,r1; ldrb r3,[r4,#5];
  ldr r7,[pc]; mov r8,r7` ✓

**Best file:** `staging/wave34_B/w34b_d9fc_v8.c` (131 diffs, old_agbcc).
Verify: `./verify34.sh 0x0800D9FC 324 .text.v8 w34b_d9fc_v8.c old
"sub_080042B8=0x080042B8" "sub_0800244C=0x0800244C" "Wrap_08002904=0x08002904"`

## Key techniques that worked

1. **old_agbcc for r7 allocation:** The "mysterious" r7 uses (s30, pairs
   base) are natural old_agbcc codegen, not pins. Main agbcc puts them in
   r0/r1. If a function has unexplained hi-reg allocation, try old_agbcc
   FIRST.

2. **Region D t116 temp:** `u8 *t116 = s + 116;` declared before
   `u32 base112` forces the `adds;adds;ldr;ldrb` interleave. The
   `u8 jjb = s[117]; s32 jj = (s8)jjb;` two-step gives `ldrb; lsls/asrs #24`
   (not ldrsb). `u32 *pe` pinned to r1 with `(u32)*t116 * 4 + base112`
   (swapped adds order) gives `lsls r1,r0,#2; adds r1,r1,r2`.

3. **Region E sjaddr asm:** `register u8 *t13978 __asm__("r2")` for the pool,
   plus `__asm__ volatile("add %0,%1,%2" : "=r"(sjaddr) : "r"(s28a),
   "r"(t13978))` with `register u8 *sjaddr __asm__("r0")` forces
   `adds r0,r3,r2` (defeats gcc's accumulate-into-r2).

4. **p26 copy:** `u32 p26 = p48[26];` (r2) + `register u32 p26r4 __asm__("r4");`
   + `__asm__ volatile("add %0,%1,#0" : "=r"(p26r4) : "r"(p26))` gives
   `ldrb r2; adds r4,r2,#0`. The r4 pin is block-scoped and does NOT break
   the prologue or later r4 reuse (pair/p).

## Remaining diffs (131 bytes)

**Region H pair/key (0xa0–0xe3, ~70 bytes):** The core issue is getting
`s28→r1` and `tbl1→r2` for the pair computation. ROM:
```
7f29 ldrb r1,[r5,#28]; 4662 mov r2,r12; 1888 adds r0,r1,r2; 7800 ldrb r0;
0600 lsls r0,r0,#24; 1600 asrs r0,r0,#24; 00c2 lsls r2,r0,#3; 19d4 adds r4,r2,r7;
2700 movs r7,#0; 5fe0 ldrsh r0,[r4,r7]; 0209 lsls r1,r1,#8; 7f6f ldrb r7,[r5,#29];
4339 orrs r1,r7; 4288 cmp r0,r1
```
v8 gives `ldrb r2; mov r1,ip; adds r0,r1,r2` (regs swapped), `lsls r0,r0,#3`
(not r2), `adds r4,r7,r0` (not r4,r2,r7), `ldrh r7,[r4,#0]` (not
`ldrsh r0,[r4,r7]`), and key in wrong regs. Attempts: tt pin to r2 (v10)
failed because s28b allocated first; volatile mov (v11) got tt→r2 but
s28b→r3 and disrupted r3v→r7. The `ldrsh` vs `ldrh` issue: v8's
`*(s16 *)pair` gave `ldrh`; ROM uses `ldrsh r0,[r4,r7]` with `movs r7,#0`.

**Region I row (0xe8–0xf0, ~10 bytes):** ROM does pool-first
(`ldr r1,[pc]; ldrb r7,[r5,#28]`), v8 does s28-first. Also `s29→r1` (ROM)
vs `s29→r2` (v8). The `register u32 *rb2 __asm__("r1")` pin (v12) did NOT
change the order — pin affects register, not emission order.

**Region J Wrap call (0x110–0x11d, ~14 bytes):** ROM: `ldrb r3,[r5,#31];
lsrs r1,r3,#4; ldr r2,[pc]; ldrb r5,[r5,#28]; ...`. v8: `ldrb r7,[r5,#31];
lsrs r1,r7,#4; ldrb r5,...; ldr r2,[pc]` (order swapped, s31→r7 not r3).

**2-byte code size excess:** v8 code is 304 bytes (ROM: 302 + 2 pad). The
`bx r0` is at 0x12e (ROM: 0x12c). The extra 2 bytes are before the
epilogue; instruction count appears same, so likely a subtle encoding
difference. This must be resolved for a match (pool alignment is correct
at 0x130, but code is long).

## Variants tried (v1–v12)

- v1: W33-D v8 baseline (main agbcc, 190 diffs).
- v2: old_agbcc + restructured e/jj (t116 temp, jjb) + Region E/G/H
  hypotheses (102 diffs).
- v3: base112 r2 pin, t13978 temp, p26 copy asm, s28a reuse (137 diffs —
  prologue OK).
- v4: pe r1 pin, t13978 r2 pin, tt/s28b swap, q2 store, rb r1 pin (316 bytes,
  BROKEN prologue: `push {r4-r6,lr}`).
- v5: v4 + swapped adds for pe, sjaddr asm (316 bytes, prologue still broken).
- v6: v3 + only Region D fix (base112 r2 pin, pe r1 pin, swapped adds)
  (134 diffs, prologue OK). **Region D perfect.**
- v7: v6 + Region E fix (t13978 r2 pin, sjaddr asm w/o r0 pin) (133 diffs).
- v8: v7 + sjaddr pinned to r0 (131 diffs). **Region E perfect.**
  **BASELINE — best so far.**
- v9: v8 + tt/s28b swap + off variable + v0 (312 bytes, worse).
- v10: v8 + tt pin to r2 (131 diffs, no change — pin didn't take).
- v11: v8 + volatile mov for tt (146 diffs, worse — disrupted r3v).
- v12: v8 + rb r1 pin (131 diffs, no change — pin didn't affect order).

## New idioms

1. **old_agbcc r7 preference:** old_agbcc naturally allocates short-lived
   byte values to r7 in some contexts where main agbcc uses r0/r1. If you
   see unexplained r7 in ROM, try old_agbcc before pinning.

2. **Swapped adds for pinned base:** When a base is pinned (e.g., r2) and
   you need `adds r1,r1,r2` (offset+base) not `adds r1,r2,r1` (base+offset),
   write the C as `(offset + base)` not `(base + offset)`.

3. **Asm address computation:** `__asm__ volatile("add %0,%1,%2" :
   "=r"(dst) : "r"(a), "r"(b))` with dst pinned to a fresh reg defeats
   gcc's tendency to accumulate into a pinned base register.

4. **C89 declaration rule:** agbcc is C89 — declarations must precede
   statements in a block. A `__asm__ volatile` statement before a
   declaration is a syntax error. Declare all locals first, then asm.

## Registry

No new row appended. The W2-A BLOCKED row for 0x0800D9FC stands. This work
does not claim a match (131 diffs remain).

## Staging

- `staging/wave34_B/w34b_d9fc_v8.c` — BEST (131 diffs, old_agbcc)
- `staging/wave34_B/w34b_d9fc_v1.c` through `v12.c` — variant history
- `staging/wave34_B/verify34.sh` — verify harness (wave34_B paths)
- `staging/wave34_B/f_0800D9FC.bin`, `f_0800D9FC.txt` — ROM reference

## Next angles

1. **Region H:** The s28→r1 / tbl1→r2 swap is the key. Try declaring tt as
   `register u8 *tt __asm__("r2")` WITHOUT the volatile asm, but ensure
   s28b is declared after and the compiler emits tt's mov first. Or try
   a different source structure that naturally yields the order.

2. **ldrsh:** For `*(s16 *)pair`, try `s16 v0 = *(volatile s16 *)pair;`
   or separate the load from the comparison. The `movs r7,#0` suggests
   gcc materializes zero for the register offset.

3. **2-byte excess:** Binary-search by commenting out regions to find the
   extra instruction. Likely in Region H or I.

4. **Region I order:** To force pool-first, try assigning the pool to a
   volatile or using the value immediately in a way that prevents
   reordering. Or accept the order and adjust the s29 reg.

5. **Region J:** Try splitting the Wrap args into separate statements to
   control evaluation order, and pin s31 to r3 if needed.
