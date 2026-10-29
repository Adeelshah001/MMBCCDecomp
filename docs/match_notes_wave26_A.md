# Wave 26-A Notes: Rect-fill family (0x08006AD8 priority, siblings)

## Summary

**Status:** All four BLOCKED. **Major progress on 0x08006AD8:** discovered via
full ROM decode that the Wave-25 v17 C was SEMANTICALLY WRONG in multiple
places (not just allocation). Corrected semantics + inline-asm prologue (byte-
perfect) yield best v20 at 583 diffs / 748B (frame 44 vs ROM 40). The remaining
wall is a pure allocator priority inversion that resisted all tried idioms.

**Baserom SHA-1 verified:** `72309736f3820470c6f372d6a05ad1f16bc5a946` before starting.
All four were BLOCKED in registry (none skipped). Staging only; no landing.

## 0x08006AD8 — TilemapRectFill_6AD8 — BLOCKED (best: v20, 583 diffs)

### Semantic corrections (vs Wave-25 v17 C)

Full ROM disassembly decode revealed v17's C was wrong:

1. **Mode else-branch:** v17 had `if (c < f-1) return; if (c < f) return; mode=2;`.
   ROM has `if (c < f-1) goto after; if (c < f) mode=2; else return;` — i.e.
   `else if (c >= f-1) { if (c >= f) return; mode=2; }`. (ROM continues with
   mode unchanged where v17 returned.)

2. **hs reuses rd:** v17 had separate `hs = (u32)(u8)(f - rb) << 24` after a
   `return` guard. ROM has: `if (rb+rd >= (s8)f) rd = (u8)(f - rb);`
   `hs = (u32)rd << 24;` — rd (r8) is reused, then hs takes r8. The `blt`
   goes to the shift, not to return.

3. **m1/m2 inside loop1:** v17 computed them before the loop. ROM computes
   them INSIDE loop1 body (after t&0x8000 check): m1 spilled to [sp,#32],
   m2 in r7. Loop2 recomputes `(mode&1)<<24` into r7 per iteration.

4. **Loop1 entry:** v17 used a for-loop (gcc propagated i=0 to `0 < hs`).
   ROM has a separate `if (i >= (s8)(hs>>24)) return;` then a do-while with
   latch `(s32)((u32)i<<24) < (s32)hs`. Loop1 exits to RETURN (not loop2).

5. **Loop2 only via s_a==0:** `if (s_a == 0) goto L2` before loop1; loop1
   never falls through to loop2.

6. **flag spilled as u8** ([sp,#28], zero-extended store); **b16 spilled**
   ([sp,#36]); **i reuses r9** (rb's register after rb dies).

### Register allocation (ROM truth)

- Pins: r6=ctx, r9=rb→i, r8=rd→hs, sl=pa.
- r5=dst, r7=m2. Spills (10 slots, frame 40): a,c,e,X,Y,mode,W,flag,m1,b16.
- r4 = scratch; r2/r3 = temps (row/w2 in loop1 else-branch).

### What was tried (v19–v28)

- **v19:** Corrected semantics with separate rb/rd/hs/i vars. 740B, 618 diffs.
  Issues: hs spilled, i spilled, dst in r8, b16 in r5.
- **v20:** Single `r9v` (u32, r9: rb→i) and `r8v` (u32, r8: rd→hs) pinned vars.
  748B, 583 diffs (BEST). Frame 44 (11 slots): extra spill is row/w2 (u16
  locals) at [sp,#36]/#40; ROM keeps them in r2/r3.
- **v21:** Dummy live-range extension for b16 (`asm(""::"r"(b16))` at end).
  b16 spills correctly, but flag takes r5 (was in reg). 752B, 644 diffs.
- **v22:** Dummy uses for b16+flag. Frame balloons to 48 (cascade). Worse.
- **v24:** Flag dummy use right after its real use (not at end). No improvement.
- **v25:** `volatile` for flag/b16. WORSE: generates pointer-based
  `strb r0,[r4,#0]`, frame 48.
- **v26:** Pin dst→r5. No improvement (still 11 slots, row/w2 spill).
- **v27:** Late-declared dst pin. No improvement.
- **v23:** old_agbcc on v20. Similar (752B, 640 diffs).
- **v28:** -O1 on v20. Worse (621 diffs).

### The remaining wall (precise)

Allocator priority inversion per `QTY_CMP_PRI = (log2(refs)*refs*size)/(death-birth)`:
- Want: dst→r5, m2→r7 (high priority: many refs, loop depth).
- Got: b16→r5 (v20), flag→r5 (v21), m2→spill, row/w2→spill.
- b16/flag have short live ranges → high priority despite few refs.
- Dummy-use extension works for b16 but shifts the problem to flag; extending
  both causes spill cascade (frame 48).
- Pins (dst→r5) don't help — allocator still spills row/w2 due to pressure.

### Files

- `staging/wave26_A/w26a_08006ad8_v20.c` — best (748B, 583 diffs, frame 44).
- `staging/wave26_A/w26a_08006ad8_v19.c` — corrected semantics, separate vars.
- `staging/wave26_A/w26a_08006ad8_v21.c` … `v28.c` — variants (see above).
- `staging/wave26_A/harness.sh` — build/verify harness.
- `staging/wave26_A/rom_08006ad8.dis` — full ROM disassembly.
- `staging/wave26_A/v19.dis`, `v20.dis`, etc. — candidate disassemblies.

## 0x08007134 — RectFill_7134 — BLOCKED (best: v1, 431 diffs)

### Prologue (ROM)

```
push {r4-r7,lr}; mov r7,sl; mov r6,r9; mov r5,r8; push {r5-r7}; sub sp,#16
adds r5,r0,#0; ldr r0,[sp,#48]; lsls/lsrs r1,#16; mov r9,r1
lsls/lsrs r2,#16 -> r7; lsls/lsrs r3,#16 (d in r3); lsls/lsrs r0,#24
str r0,[sp,#0]; movs r0,#0; str r0,[sp,#4]
```
ctx→r5, b→r9, c→r7, d in r3, e→spill[0], mode=0→spill[4]. Frame 16.

### What was tried

- **v1:** Inline-asm prologue (adapted from 6AD8 idiom) + W24-A v4 body with
  renamed vars. 496/480B (16 over), 431 diffs, frame 20 vs 16.
  - Prologue byte-perfect EXCEPT one extra `adds r4,r3,#0` (d capture; ROM
    keeps d in r3 with no mov).
  - Frame 20 (5 slots) vs ROM 16 (4 slots) — extra spill shifts offsets.
  - Body from v4 (426 diffs at 500B) — allocation diffs remain.

### Files

- `staging/wave26_A/w26a_08007134_v1.c` — best (496B, 431 diffs).
- `staging/wave26_A/rom_7134.bin` — ROM extract.

## 0x080065BC — FillRect_65BC — BLOCKED (not attempted)

Prologue decoded in W24-A: 7 params; ctx→r9, d→sl, e→r7+spill, f→r6, g→r5+spill;
b,c spill. Inline-asm prologue idiom should apply. Time-boxed on 6AD8/7134.

## 0x08006374 — FillRect_6374 — BLOCKED (not attempted)

Prologue decoded in W24-A: 8 params; ctx→r9, (stack u8)→r6→sl; b,c,d,f,g spill.
Calls 0x080065BC 2x. Inline-asm prologue idiom should apply. Time-boxed.

## Recommendations for next worker

1. **0x08006AD8:** The semantic corrections are the key progress. For the
   allocation wall, try: (a) splitting dst into two variables to shorten its
   range and boost priority; (b) the `u8 *pa = a;` first-local idiom for
   flag/b16; (c) reordered live ranges — define b16 later (closer to use) to
   shorten its range and LOWER priority (counterintuitive but per the formula,
   shorter range = HIGHER priority, so LONGER range = lower — already tried
   via dummy use); (d) accept that this may need the coordinator's Makefile
   sed for a targeted fix.
2. **0x08007134:** Fix the d capture (avoid the extra mov — perhaps by not
   capturing d in prologue and instead reading r3 via a separate tiny asm
   AFTER the prologue, or by restructuring). Then attack the frame (20→16).
3. **Siblings 65BC/6374:** Apply inline-asm prologue idiom; their bodies are
   simpler (no complex loops like 6AD8).
