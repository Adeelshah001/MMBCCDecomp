# Wave 11 Worker C (TAG=C) — Task_3AFFC @ 0x0803AFFC — Match Notes

Worker: Wave 11 specialist (TAG=C). Date: 2026-10-21.
Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` before start.
Toolchain: `mmbcc/tools/agbcc/bin/old_agbcc`; `arm-none-eabi` 2.42.
Harness: `staging/wave11_C/mk.sh` (improved: full 928B extent incl inline JT+pools,
`.rodata` concatenation fallback, non-empty assertions).
Staging: `~/workspace/mmbcc-decomp/staging/wave11_C/` (NEVER delete).
Results: `docs/wave11_C_results.tsv`.

**Result: BLOCKED. Best: 363 diffs, 928/928 bytes (was 661 diffs W7, 590 diffs W10).**

## Critical Corrections to Prior Notes

1. **True extent is 928 bytes** (0x0803AFFC–0x0803B3A0), not 926. The final pool
   word at 0x803B39C (`9d 46 00 00` = 0x0000469D) is included; next function starts
   at 0x803B3A0.

2. **Function returns u32** (not u8). Epilogue: `adds r0,r5,#0` with no truncation;
   `ret` is set to 1 in modes 3-else, 9-g8==1, 13-g8==0, 13-g8==1.

3. **sub_0800B148 2nd param is s16** (not u16). Declaring as `(u8, s16, u8)` gives
   ROM's `adds r1,r0,#0; lsls r1,#16; asrs r1,#16` (verified by probe). The u16
   declaration gives `lsrs` (wrong).

4. **Mode 7/11 use `beq epi`** (`if ((s8)... == 0) break;`), **mode 1 uses `bne`**
   (`if ((s8)... != 0) { inc }`). Different C shapes per mode.

5. **Mode 9 g8==1 uses `p[0x469c] = g8`** (variable, not constant 1). ROM does
   `strb r2,[r0]` storing g8 directly (r2=1 in this branch).

6. **Mode 15 is `p[0x469d] = 6`** (not `++`). Falls through into TailD (shared
   with mode 13-else). Wave7's "mode++" was wrong.

7. **Mode 14 is B368(0x0823190C,0,0,0)** with inc on success. The SelectBlob(0x68)
   at 0x803B350 belongs to mode 13-else, not mode 14. Wave7 misattributed this.

8. **0x02002F54 access**: ROM does `ldr r1,=0x02002F50; ldrh r1,[r1,#4]`. Use
   `((u16 *)gEwram_02002F50)[2]` not `*(u16 *)0x02002F54`.

## Three Angles Tried

### Angle 1: Per-case opaque asm barriers — NOT VIABLE

**Finding:** old_agbcc **completely ignores** empty `__asm__ volatile("")`, with or
without `"memory"` clobber or `"+r"` constraints. Probe confirmed: no `#APP` markers
in .s, no effect on optimization. Non-empty asm (e.g., `"mov r0, r0"`) IS honored
but emits bytes, defeating the match.

**Conclusion:** Angle 1 cannot work with this compiler. The wave10 suggestion
assumed GCC would honor empty barriers; old_agbcc (GCC 2.9-era) drops them.

### Angle 2: Macro hypothesis with register pinning — PARTIAL

**Success:** Scoped `register u8 *gp __asm__("r0")` for the `g[0x14] |= 1` prologue
gives ROM's exact `ldr r0,=0x02004E40; movs r1,#1; ldrb r2,[r0,#20]; orrs r1,r2;
strb r1,[r0,#20]` (vs natural `ldr r1,...; movs r0,#1...`).

**Failure:** The per-mode `ldr rX` variation (r0 at modes 1,7,12,14; r2 at modes
2,4,8,11) could not be reproduced via pinning. Explicit temporaries and zero
variables were tried; the allocator's choices depend on full-function context
in ways that resist source-level control. The `g8` variable (mode 9/13) allocates
to r1 in my builds vs r2 in ROM; no C tweak found to force r2.

### Angle 3: JT-in-section harness — SUCCESSFUL

**Finding:** The JT **is** inline in `.text` (not `.rodata`). The wave10 concern
was unfounded for this function — agbcc emits the JT inline, and the mk.sh
extracts it correctly as part of the 928B extent. The JT entries match automatically
once code layout matches (modes 0-9 JT entries are now correct).

## Current Best (v18): 363 diffs, 928/928B

**Modes 0-9:** Address-aligned, 91% byte-identical (26 diffs / 292 bytes).
Remaining diffs:
- Branch offsets (7B): will resolve when layout is perfect
- Mode 2/4 table-index ldr interleaving (8B): ROM `lsls r0,#24; ldr r1,[pc];
  lsrs r0,#22`; mine `lsls; lsrs; ldr`. Tried: direct index, table variable,
  split shifts, compound assignment, GetPtr-style. Compiler always fuses.
  The `GetPtr_0800dcf8` precedent shows this codebase uses split shifts with
  intervening memory ops, but the minimal intervening op (just the ldr) fuses.
- Mode 3 tail (6B): ROM `movs r2,#0; movs r0,#9; b TailC`; mine `movs r0,#9;
  b tail_c`. The `movs r2,#0` setup before the shared tail could not be reproduced.

**Modes 10-15:** Disrupted by explicit `goto tail_c` (v13+). The goto gives the
right SIZE (928) by sharing tails, but places `tail_c` at 0x803B37A (should be
0x803B33C), shifting modes 10-15 by 8 bytes. Natural C (v12/v19) has correct
layout but wrong size (932B, 491 diffs) due to no tail sharing.

## The Fundamental Blocker

The ROM's TailC/TailD/TailA are placed at 0x803B33C-0x803B38E (between mode 13
and mode 14) via the original compiler's natural crossjumping. My compiler:
- **Without gotos:** Does NOT merge the tails sufficiently (932B, too big).
- **With gotos:** Merges but places the tail in the wrong location (disrupts layout).

The original source must have a structure that causes the compiler to BOTH merge
AND place correctly. Possible structures not yet tried:
- The `p[0x469c]=X; p[0x469d]=0; ret=1` sequences might use a helper macro that
  expands differently per site (e.g., with different temporary names affecting
  allocation).
- The mode 9 `p[0x469c] = g8` (variable) vs mode 3/13 constants suggests the
  original may have had subtle per-site differences we haven't captured.
- A `switch` with explicit `default:` instead of `if (mode > 15) goto epi` might
  affect the CFG layout and tail placement.

## Recommended Next Angles

1. **Remove gotos, fix tail sharing via structure:** Try writing modes 3, 9, 13
   with IDENTICAL statement sequences (modulo constants) to maximize crossjumping.
   The `p[0x469c] = g8` discovery suggests other per-site variable-vs-constant
   differences may exist.

2. **Table index via GetPtr idiom:** Write mode 2/4 as:
   ```c
   u8 b = sub_08024384(0x1000) - 50;
   u32 x = (u32)b << 24;
   u32 *table = (u32 *)0x08232128;
   // intervening memory op that can't fuse?
   x >>= 22;
   u32 fn = *(u32 *)((u8 *)table + x);
   ```
   Need an intervening op that the compiler won't fuse across but emits no code.
   (Empty asm doesn't work; maybe a volatile read of a dummy?)

3. **Try main agbcc for the whole function:** Wave7 found old_agbcc best (661 vs
   664 diffs), but the tail-placement heuristics may differ. Worth one full run.

4. **Decompile the callees first:** sub_0800BEE0, sub_080241F8, sub_08024384,
   sub_0800B148 are still BLOCKED. Their true signatures (esp. B148's s16 param
   discovered here) affect caller codegen. Matching them may unlock 3AFFC.

## Files

- `staging/wave11_C/w11c_3affc_v18.c` — best attempt (363 diffs)
- `staging/wave11_C/w11c_3affc_v12.c` — best natural-C (491 diffs, correct layout)
- `staging/wave11_C/mk.sh` — improved harness (928B, JT-in-text)
- `staging/wave11_C/probe_*.c` — s16, table-index, asm-barrier, tail probes
- `docs/wave11_C_results.tsv` — results table
- `docs/match_notes_wave11_C.md` — this file
