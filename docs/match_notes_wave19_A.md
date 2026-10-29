# Wave 19 Worker A notes — Task_3AFFC @ 0x0803AFFC (2026-10-22/23)

## Task_3AFFC @ 0x0803AFFC: BLOCKED, best 28 diffs (was 70), 932/928 B, old_agbcc

Best source: `staging/wave19_A/w19a_11_best28.c` (also `w19a_13_final.c` with
`.text.3affc` section; landed candidate at `mmbcc/src/w19a_3affc.c`).
Harness: `staging/wave19_A/build_3affc.sh` (copy of w18a harness, paths updated).

### Progress: 70 → 28 diffs (60% reduction)

**Size**: 932 B (was 932). The 928-byte comparison window truncates; extra 4 B
are in the final pool region beyond the window. All 16 JT entries match.
Epilogue at correct 0x3B38E.

### Key idioms discovered / applied

1. **`goto c13_else` with label AFTER the shared tail (NEW, big win — 40 B):**
   ROM's case-13 layout is `cmp r2,#1; bne else` with the else (Text) block
   placed AFTER the shared `tail_c`, not inline. Previous attempts
   (`if (g8 != 1)`, `else if (g8 == 1)`) all produced `beq` with the else
   inline because the compiler's block-ordering heuristic prefers the
   smaller/fallthrough layout.
   C idiom:
   ```c
   } else if (g8 == 1) {
       u8 *q = p + 0x469c;
       z = 0;
       *q = 7;
       goto tail_c;
   } else {
       goto c13_else;
   }
   break;
   tail_c:
       p[0x469d] = z;
       ret = 1;
       goto epi;
   c13_else:
       Text_SelectBlobIdx(0x68);
       goto store6;
   ```
   The explicit forward `goto` to a label defined after `tail_c` forces the
   compiler to emit `bne` over the g8==1 block AND the shared tail, placing
   the Text block at the end — byte-exact ROM layout. This also fixed the
   case-3 `b` target (0x3B142: our tail_c moved to 0x3B33C, matching ROM's
   cross-case branch into case 13's `strb`).
   **Lesson: when the compiler's block-ordering heuristic resists, use an
   explicit `goto` to a label placed where you want the block, not if/else.**

2. **Local `u8 w` instead of function-scope `z` in case-9 else (NEW, 2 B):**
   ```c
   } else {
       u8 *q = p + 0x469c;
       u8 w = 0;   // was: z = 0 (function-scope)
       *q = 2;
       p[0x469d] = w;
   }
   ```
   The function-scope `z` (used in cases 3, 9-else, 13) caused interference;
   a fresh local lets the allocator pick better registers. Fixed 2 of the 4
   else bytes (`movs r2,#0; movs r0,#2; strb r0,[r1]` now match; only the
   `ldr` dest reg differs: ours `r2`, ROM `r0`).

3. **Confirmed: `register u32 g8 __asm__("r2")` avoids zero-extend overhead
   (but still too disruptive):**
   `register u8 g8 __asm__("r2")` generates `ldrb r2` + `lsls/lsrs` (4 B
   overhead) because the compiler doesn't track zero-extension through
   explicit registers. `register u32` gives clean `ldrb r2; cmp r2` with no
   overhead. HOWEVER, even the u32 pin disrupts the g8==1 stores (40 diffs
   vs 28) — the compiler reuses r2 for the 0x469d literal in a different
   order than ROM (`movs` late vs early). Explicit register pins remain
   non-viable for this function.

### What did NOT work

- **Function/block-scope `register __asm__("r2")` for g8**: 375 diffs (u8,
  with lsls/lsrs overhead) or 40 diffs (u32, clean load but store order
  differs). The pin reserves r2 and changes allocation globally (u8) or
  the store scheduling (u32). NOT viable.
- **Case-9 g8 in r2 via C tweaks**: Brute-forced 5+ variants (int g8, tmp,
  direct init, etc.) in isolation probe — compiler consistently picks r1
  for the `adds r?,r0,#0` copy. The allocator has a strong r1 preference
  for this pattern. BLOCKED.
- **Interleave via -O1/-O2/-O3/-Os**: All produce non-hoisted
  `subs;lsls;lsrs;ldr`. The load-hoist (`ldr` between `lsls` and `lsrs`)
  is a scheduling optimization old_agbcc never performs. BLOCKED (needs
  different compiler version).
- **Local `w2` in g8==1 block**: 194 diffs (disruptive). The g8==1 stores
  are tightly coupled to g8's register; locals interfere.
- **`u8 *q;` separate decl in else**: 34 diffs (worse than `u8 *q = ...`).
- **`w = 0` before `q` in else**: 32 diffs (worse).

### Remaining diffs (28 bytes)

By ROM address:
- 0x3B0C8-0x3B0CB (4B): case 2 interleave (`ldr r1` after `lsrs` vs ROM's
  hoisted `ldr` before `lsrs`). BLOCKED: scheduler limitation.
- 0x3B154-0x3B157 (4B): case 4 interleave (same). BLOCKED.
- 0x3B222, 0x3B225, 0x3B239 (3B): case 9 g8 `adds r1`/`cmp r1` vs ROM
  `adds r2`/`cmp r2`. BLOCKED: allocator r1 preference; pin too disruptive.
- 0x3B23D-0x3B248 (11B): case 9 g8==1 stores. Depends on g8 in r2;
  ROM does early `movs r1,#0`, ours does late `movs r0,#0`. BLOCKED.
- 0x3B259-0x3B25A (2B): case 9 else `ldr r2` vs ROM `ldr r0`. HARD:
  allocator prefers r2 for literal.
- 0x3B36B-0x3B36C (2B): case 14 `ldr r2`/`adds r1,r4,r2` vs ROM
  `ldr r0`/`adds r1,r4,r0`. HARD: contextual (isolated probe uses r0;
  full-function context picks r2).
- 0x3B387-0x3B388 (2B): store6 `ldr r0` vs ROM `ldr r2`. HARD: shared
  label with two predecessors; allocator picks r0.

### Recommendations for next worker

1. **Interleave (8B)**: Requires a different agbcc version with load-hoist
   scheduling. Check if any other compiler builds exist, or if the ROM was
   built with a patched agbcc. This is likely unfixable with old_agbcc.
2. **g8 in r2 (14B: load/cmp + stores)**: The fundamental blocker. Options:
   (a) Find a C formulation that naturally yields r2 (brute-force more
   variants, esp. around the g8==1 store order); (b) Accept as blocked.
   The `register u32` pin gets the load right but breaks stores — maybe a
   hybrid (pin + store C tweak) could work.
3. **Else/case-14/store6 (6B)**: All "r0 vs r2" allocator preferences.
   Try making the preferred register "busy" at those points via dummy
   locals, or accept as blocked.
4. **The `goto`-to-late-label idiom** (breakthrough #1) may apply to other
   functions with similar "cold block at end" layouts.

### Files

- `staging/wave19_A/w19a_11_best28.c` — best source (28 diffs, old_agbcc)
- `staging/wave19_A/w19a_13_final.c` — same with `.text.3affc` section
- `staging/wave19_A/build_3affc.sh` — build harness
- `staging/wave19_A/bld_11_best28.*`, `bld_13_final.*` — build artifacts
- `staging/wave19_A/diff_11_best28*.txt` — diffs
- `staging/wave19_A/LANDING.md` — landing instructions (NOT READY: 28 diffs remain)
- `staging/wave19_A/match_notes_wave19_A.md` — this file
- Probes: `probe_g8*.c`, `probe_else.c`, `probe_c14.c`, `probe_il.c`,
  `brute_g8.py`
- Intermediate: `w19a_00_baseline.c` (70), `w19a_01_c13layout.c` (70),
  `w19a_02_c13else.c` (30), `w19a_03_g8r2.c` (375), `w19a_04_g8r2b.c` (375),
  `w19a_05_best30.c` (30), `w19a_06_g8u32.c` (40), `w19a_07_g8z.c` (369),
  `w19a_08_else.c` (34), `w19a_09_else2.c` (28), `w19a_10_else3.c` (32),
  `w19a_12_g81.c` (194)

LANDING.md exists with instructions but is marked NOT READY (28 diffs remain, not 0).
