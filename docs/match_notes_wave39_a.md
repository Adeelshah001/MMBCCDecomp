# Wave 39 Worker A — match notes

Baserom SHA-1 verified: `72309736f3820470c6f372d6a05ad1f16bc5a946`.
Staging dir: `staging/w39a_bulk/` (never cleaned; coordinator verifies).
All matched files use `old_agbcc -O2 -mthumb-interwork`, `.set` blocks at
END of file, no section attributes in staged files.

## Idioms learned (new or reinforced)

1. **Stack-slot reuse = arity signal.** In `0x080285c4`, ROM stores the
   stack argument once (before the 5-arg `0x08006a54` call) and does NOT
   re-store it for the following `0x080070f0` call — because 70f0 takes
   only 4 args and the leftover 0 is harmless. Declaring 70f0 with 5 args
   cost exactly +2 B per call site (380 vs 376 B). Lesson: when a call
   site lacks a `str [sp,0]` that its neighbours have, suspect the callee
   takes one fewer argument than assumed, not a missing store.
2. **Trailing `.hword 0` pad.** GAS pads a `.text` section end to 4-byte
   alignment with a `mov r8, r8` nop (`0x46c0`); ROM has `0x0000` there.
   A file-scope `__asm__(".hword 0")` after the function (as in
   `w39a_080285c4.c`) supplies the pad bytes exactly. Same idiom as the
   Wave 38 `17a94` family.
3. **73d4 (CondRectFill) arg order is (code, flag, …).** First attempt
   passed (flag, code, …) and cost an extra register move per call site
   plus a 12 B shortfall. ROM order: `r0` = code (27/28/29/30, or `i+27`
   in 35c5c), `r1` = flag (0/3), `r2` = coordinate, `r3` = mode,
   stack = extra. The 35c5c loop-1 calls pass (i+27, 3/0, i*2+30, 4, flag)
   in the same order.
4. **Kept-pointer scope is observable.** In `0x0803895c`, ROM keeps the
   `0x08230174` pointer in r6 for blocks A/B only; blocks C/D reload the
   pool literal. Replicating the exact use pattern (variable for A/B,
   literal for C/D) is what closed the function — a kept variable used
   everywhere compiles differently (r6 reuse in C/D instead of pool
   loads). Lesson: when a function mixes variable reuse and pool reloads
   of the same constant, mirror the use sites, don't unify them.
5. **If-form vs ternary-form flag computation differ by one instruction
   position.** `u8 f = 0; if (s[k]) f = 3;` emits `movs r1,#0` BEFORE the
   pool load; `s[k] ? 3 : 0` as an argument emits it AFTER the load.
   Block A of 3895c uses the former, blocks B–D the latter.
6. **Register pin to fix callee-saved assignment.** In `0x080118a4`,
   both compilers assigned the task pointer to r4; ROM uses r5 (with the
   temp in r4). `register u8 t __asm__("r4")` for the temp pushed the
   pointer to r5. Caveat: the same pin perturbed another block in
   `0x08035c5c` (r3 pin on the loop flag fixed its load but broke
   path-2 allocation) — pins are local fixes, verify the whole function
   after applying one.
7. **Cross-jumping merges duplicated call sites — and cannot be disabled
   in these agbcc builds.** `-fno-crossjumping` is rejected by both
   `agbcc` and `old_agbcc`; an empty-asm barrier inside the second block
   did NOT defeat the merge either (19904 `IncUse(s,7)` sharing,
   118a4 duplicated `Inc4_Clear5_7` sharing). This is the open problem
   for the whole move-task switch family: ROM keeps both call sites.
   A future angle: make the two call sites differ at RTL level (e.g.
   different argument pseudos that allocate to the same register) —
   not yet found; `s+0` folds too early, and a copy variable gets
   copy-propagated back to identical RTL.
8. **Double-`&` does not fold in ROM but does in these compilers.**
   ROM keeps `s[10] &= 0xfd` then `& 0xfe` as two separate ands (19904
   case 4); both agbcc builds fold a single expression to `& 0xfc`.
   Two-statement form adds a load/store pair instead — also wrong.
   Unresolved; likely needs the exact original expression shape.
9. **Unused CopyMirrored output still loads.** In 19904, ROM loads both
   `buf[0]`→r2 and `buf[1]`→r3 although only `buf[1]` is used in the
   cases. A C version that drops the unused variable loads only `buf[1]`
   (into r2). Keeping a dead variable alive across a switch is an open
   idiom — a dummy live-range asm may be needed, not yet tried here.

## Per-function notes for the coordinator

### Matched — landing info

- `0x080285c4` (376 B) / `0x08048084` (376 B): identical twins.
  Section: plain `.text` at the respective address; extent includes the
  trailing `.hword 0` (bytes `00 00` after `bx`). Callees (all via
  `.set`): `0x0804e008` MemsetAligned (MATCHED), `0x0802518c` Copy4
  (MATCHED), `0x08006a54` Blit (gap), `0x080251d8` (MATCHED),
  `0x080070f0` CondRectFill (MATCHED, **4 args**),
  `0x08006dd8` (gap). Pools: 6832, 5959/5958/5957, 12772,
  11899/11898/11897 — all as immediates/pool literals in the staged
  file's code; no separate `.rodata` beyond the mid-function pools.
  Compiler: `old_agbcc -O2 -mthumb-interwork`.
- `0x0803895c` (376 B): section plain `.text`. Callees:
  `0x080073d4` CondRectFill (MATCHED, 5 args: code, flag, coord, mode,
  stack), `0x08006a54` Blit (gap). ROM-pointer derefs in the file:
  `0x08230174` (kept variable, blocks A/B), `0x0823012c`,
  `0x08230134`, `0x0823013c`, `0x08230144` (literals). Mid-function
  pools are part of the extent; no trailing pad beyond the 376 B
  (function ends `bx` at +370, final pool word at +372..+375 — verify at landing:
  the extent is code + pools, no extra pad bytes).
  Compiler: `old_agbcc -O2 -mthumb-interwork`.

### Blocked with variants (see RESULTS.md for counts)

- `0x08003874`: best remains w38-B v3 (328 B, 272 diffs). NOT re-staged;
  file is `staging/w38b_dpart2/w38b_08003874_v3.c`. Re-verified this
  wave with the w39a harness (same numbers).
- `0x080118a4`: staged `w39a_080118a4.c` (v5: goto-form first call +
  r4 pin on `t`). Full semantic reversal is in the file header and in
  the wave notes: two-test guard, `s[5]==0` block with Copy3/11cc4/
  10fdc, `F_11054(&flag)` gate returning 0, flag-dispatch on
  `p[24]/[26]/[28]`, TableWalk path. Remaining walls: duplicated-call
  merge + dispatch block ordering. The pin idiom (note 6) is the one
  solid gain for a retry.
- `0x08019904`: staged `w39a_08019904.c` (v1). Full case map (switch on
  `s[13]`, jump table = base literal `0x08019944` at +0x3c, entries at
  +0x40..+0x54): case 0 = `(u8)(s[119]-3)>1` gate, Text(132), `s[100]=80`,
  IncUse(7); case 1 = `buf[1]<=-1280` gate, `s[92]=-768`, IncUse(7);
  case 2 = `buf[1]<=-1280` + `s[92]<=0` gates, zero `s[92]/s[100]`,
  IncUse(`s[17]`), `s[18]=20`; case 3 = `s[18]--` countdown, SetBit16
  (`s[44]` ptr, 3), IncUse(8), `s[18]=15`; case 4 = `s[18]--` countdown,
  ChipInit(`0x59`, `s[35]&0xF`, `0x3c00`, `-2560`, `s[44]` ptr),
  `s[10]` masked `0xfd` then `0xfe`; case 5 = GetField17(`s[44]` ptr)
  `(u8)<=5` → return 0 else return 1 (no `s[13]++`); default and all
  case tails → `s[13]++`, return 0. Preamble: Vec2_AddMirrored,
  `s[88]+=s[96]`, `s[92]+=s[100]`, Vec2_CopyMirrored to stack `buf[2]`.
  Open items: cross-jump sharing (note 7), dead `buf[0]` load (note 9),
  double-`&` fold (note 8).
- `0x08035c5c`: staged `w39a_08035c5c.c` (v4, r3 pin) + v2/v3/v5
  variants. Two `u8 i<=3` loops over 12-byte entries (offsets +289/+288
  with 73d4 calls, +336 with MapTableVal) + scripted tail (35c1c call,
  6dd8/Blit calls, SDiv of `s[36]*100` by `s[38]+s[36]`). v2 is
  instruction-identical except one extra `add r3, r0, #0` for the
  loop-1 flag (plus the pool pad it forces). Retry angle: a load idiom
  that lands the flag directly in r3 without the copy and without
  perturbing path 2.

### Skipped / extent notes

- Six skips are registry+ldscript confirmed (see RESULTS.md). No other
  bulk address lies inside a landed section.
- `EXTENT UNVERIFIED` rows in RESULTS.md (next known function far beyond
  the TSV size, e.g. `0x080398f8` +720, `0x08015f90` +3008,
  `0x0802fda0` +2964): the TSV size is the terminator-consistent size
  for most (first terminator lands near TSV size), but the gap means
  unlisted functions sit between — do not assume the TSV size is the
  true extent for landing without the extent worker's confirmation.
- Twin pair in range (byte-identical streams, identical pools):
  `0x08003b70` / `0x08003e80` — both hit the register-offset `ldrsh`
  wall (4 sites); a pure-C match needs an `ldrsh` load idiom or a
  `.s` patch, same as `0x08003874`.
- Twin pair matched: `0x080285c4` / `0x08048084`.
- `0x08004a04` bl-list shows a self-target in triage output — likely a
  mis-decoded pool word, not recursion; needs a clean disassembly read
  before any attempt.

## Tooling notes

- `staging/w39a_bulk/w39a.py` is the w38-A harness with the workdir
  repointed; `build_opt.sh`/`build_flags.sh` take an arbitrary
  optimization/flag string (used for `-O1`/`-Os` probes and the rejected
  `-fno-crossjumping` probe — both compilers print `Invalid option`
  for it, so the flag route is closed for this toolchain).
- Disassembly dumps for all 100 targets are in
  `staging/w39a_bulk/dis/080*.txt` (TSV-window width; gap-suspect
  functions were NOT widened — their dumps cover only the TSV window).
