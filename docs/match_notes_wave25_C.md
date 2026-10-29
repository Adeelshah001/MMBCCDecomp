# Wave 25 Worker C notes (2026-10-23)

Worker C: six ShiftPair_Copy_800C wrapper siblings.
Result: **6 MATCHED, 0 BLOCKED.**

Staging: `staging/wave25_C/` (harness `w25c.sh`, `addrs_sizes.txt` with
true extents incl. trailing pools).
Final C files: `staging/wave25_C/w25c_<addr>.c` (section `.text.w25C_<addr>`).
Patch script: `staging/wave25_C/w25c_08041890_patch.sh` (epilogue sed).

## Family structure

Each function = two halves. Each half: `switch ((s8)p[off])` with cases
1 and 3 (default: skip):
- **case 1**: configure EWRAM struct at base:
  `*(u16*)(base+40)=C40; *(u16*)(base+42)=C42;`
  `b = ((*p44 | 1) & (C42-SUB)) | 32; *p44 = b;`
  `w = (*(u16*)(base+44) & ~0x3C0) | ORH; *(u16*)(base+44) = w;`
  `ShiftPair_Copy_800C(base, idx); p[off] = 2;`
- **case 3**: `*(base+44) &= -2; p[off] = 0;`
- Half 2 uses off2, base2, different constants, idx=2.

Per-function constants (C40 / C42 / SUB / ORH / idx; half1 then half2):

| addr | half1 | half2 | q2 reg | EWRAM bases |
|------|-------|-------|--------|-------------|
| 0x0803f844 | 108/12/43/0x40/1 | 108/64/95/0x80/2 | r4 | 0x02004D48 / 0x02004D7C |
| 0x08046810 | 152/12/43/0x40/1 | 152/128/159/0x80/2 | r5 | 0x02004D48 / 0x02004D7C |
| 0x08045914 | 292/12/43/0x40/1 | 292/128/159/0x80/2 | r5 | 0x02004DB0 / 0x02004DE4 |
| 0x0804a1f0 | 108/12/43/0x40/1 | 108/64/95/0x80/2 | r4 | 0x02004D48 / 0x02004D7C |
| 0x0803ad48 | 136/0xFFFC/negs31/0x40/1 | 136/64/95/0x80/2 | r4 | 0x02004D48 / 0x02004D7C |
| 0x08041890 | 292/12/43/0x40/1 | 292/128/159/0x80/2 | r5 | 0x02004D48 / 0x02004D7C |

True extents (code + trailing pool, verified from ROM bytes):
3f844=220, 46810=220, 45914=228, 4a1f0=220, 3ad48=228, 41890=228.

## Matched (6)

### 0x0803f844 — ShiftPairCfg_3F844 (220 B), old_agbcc, 0 diffs
Template for the family. Key idioms discovered:
- `switch ((s8)q[0])` directly (no named v1) keeps v1 in r0.
- `b` (u32) pinned to r1 via `register u32 b __asm__("r1")` + 
  `__asm__ volatile("movs %0, #1" : "=r"(b))` defeats the compiler's
  value-propagation (it reused v1==1 for the constant 1).
- `~0x3C0` as the AND mask pools as 0xFFFFFC3F (not 0xFC3F).
- `__asm__ volatile("" : "+r"(base))` barrier prevents folding
  `base+44` into the pool (case 3).
- `u32 m = 2; m = -m;` gives `movs r1,#2; negs r1,r1` (not folded to 254).
- `u32 t = C42; *(u16*)(base+42) = t; b &= t - SUB;` gives the
  `movs/subs/ands` sequence (t must be live for the runtime subtract).

### 0x08046810 — ShiftPairCfg_46810 (220 B), old_agbcc, 0 diffs
Half2 has strh42=128 (same as ORH=0x80). The compiler hoists 128 to r4
early (`movs r4,#128`) and uses `orrs r1,r4`, forcing q2 to r5.
Reproduced via `register u32 c128 __asm__("r4")` +
`__asm__ volatile("movs %0, #128" : "=r"(c128))` placed after strh40,
with `w |= c128`. The strh42 uses a fresh `movs r2,#128` (literal).

### 0x08045914 — ShiftPairCfg_45914 (228 B), old_agbcc, 0 diffs
C40=292 via `__asm__ volatile("movs %0, #146\n\tlsl %0, %0, #1" : "=r"(v40))`
(GAS pre-UAL: `lsl` not `lsls`). EWRAM bases 0x02004DB0/0x02004DE4.

### 0x0804a1f0 — ShiftPairCfg_4A1F0 (220 B), old_agbcc, 0 diffs
Direct copy of 3F844 template (different offsets only). 0 diffs on first try.

### 0x0803ad48 — ShiftPairCfg_3AD48 (228 B), old_agbcc, 0 diffs
Half1: strh42=0xFFFC via `u32 v = 0xFFFC; *(u16*)(base+42) = v;`
(pool load to r2); mask via `u32 m = 31; m = -m;` (`negs`).

### 0x08041890 — ShiftPairCfg_41890 (228 B), old_agbcc + sed, 0 diffs
Same shape as 45914. **Unique**: ROM epilogue is `pop {r1}; bx r1`
(not `pop {r0}; bx r0`). C cannot steer this; sed patch required:
`w25c_08041890_patch.sh` replaces `pop {r0}`/`bx r0` with `pop {r1}`/`bx r1`
in the .s before assembling. Verified 0 diffs after patch.

## Registry
- All six addresses grep-clean against docs/match_status.tsv before work.
- ShiftPair_Copy_800C (0x0800800c) is MATCHED (src/wave9_d_old.c);
  used as `.set` absolute symbol in staging (coordinator: use real extern).

## New idioms for catalog
1. **Pin+asm for forced movs**: `register u32 b __asm__("r1");` +
   `__asm__ volatile("movs %0, #1" : "=r"(b));` forces `movs r1,#1`
   when the compiler would otherwise reuse a known-constant register.
2. **Barrier vs pool folding**: `__asm__ volatile("" : "+r"(base))`
   stops `base+const` folding into the literal pool.
3. **negs via variable**: `u32 m = 2; m = -m;` emits `movs`+`negs`
   instead of folding to an 8-bit constant.
4. **u32 for pool constants**: `u32 v = 0xFFFC;` (not bare `0xFFFC`)
   gets the pool load into the right register.
5. **Sibling-shape transfer works**: match one, adapt constants;
   the allocator reproduces r4/r5 and hoisting differences from constants.
