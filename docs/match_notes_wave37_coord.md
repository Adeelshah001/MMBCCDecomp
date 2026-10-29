# Wave 37 Coordinator Notes (in progress)

## Worker A — DONE (landed 0x08009238; 0x08030ad4 structure)
- 0x08009238 MATCHED, 144 B, old_agbcc, no patch. TRUE extent 144 confirmed
  (code ends bx r0 0x0929c, 10-word pool 0x092a0–0x092c7, next prologue
  0x092c8; "128" rejected — would cut 4 loaded pool words). New idiom:
  empty volatile asm barriers (__asm__ volatile("" : "+r"(x))) defeat gcc
  constant folding with zero emitted instructions (base/offset stay
  separate pool loads + adds; negs mask preserved). Main agbcc: 10 diffs.
- 0x08030ad4 structural map staged (no claim): jump table 0x30c6c–0x31067
  (255 entries, 94 distinct targets, 162 entries -> default latch
  0x08033874); regions mapped; handlers 90 case blocks + tails; plan in
  staging/w37a_30ad4/structure_08030ad4.md + handler_inventory.json.
  Main risk for full-unit C match: bl-to-loop-head layout.
- Landing: src/w37a_08009238_MATCHED.c + old_agbcc rule + slot after
  0x08007798. Verified 0-diff clean-room AND in-built-ROM.

## Worker B — DONE (12 landed, 2 reverted as duplicates)
- Landed: 08000eb8, 08000ed4, 08007c04, 08007f24, 08011530, 080174f4,
  0801aa50, 0801b96c, 0801cd30, 0801e970, 080402e0, 0804044c (all old_agbcc,
  8 with .s patches in mmbcc/tools/fix_w37b_*_patch.py).
- Gap run 0x08000eb8+ is exactly 3 functions (eb8/ed4/ef8); Slot_FetchWord4
  twin family (1b96c/1cd30/1aa50/1e970, 32 B each, tbl 0x082243d8).
  Near-variant 0x08021054 is NOT a twin (not claimed).
- New idioms: barrier-on-base forces pool-first loads; adds-destination
  follows the base register; constant-first ORR via variable (m=4);
  compound-assignment register rule (*q &= k -> r0, *q = b & k -> b's reg);
  zero-variable in r0 gives subs-mask; separate sh/m statements give ROM
  orr order; sv must be int for asm ldrsb. Correction: 24670 takes ONE arg.
- REVERTED (worker registry-check failures — flag for future briefs):
  (1) 0x08000ef8 was already MATCHED in W11 as F_EF8 (registry line 618,
  section .text.w11a_08000ef8) — worker's 0-diff version redundant.
  (2) 0x08020ff0 is NOT separate — landed W36 section w36d_08020f70
  (144 B) already contains Sub_08020FF0 as trailing helper at +0x80.
  Both landed files/slots/rules removed; registry REVERTED rows appended.
  Worker reported "0 skipped" — the brief's registry-check rule needs
  reinforcement (check section overlaps in ldscript.ld, not just the
  registry status column).
- Landing hygiene applied: file-local .set lines added to landed copies
  for extern callees whose real build names differ (TblStride_24818,
  TblGetW_BB8C, Gfx_BlitRequest, TblGetW_BF74, TblGet_f0E, sub_08005268,
  ChipSlot_Setup, ChipSlot_IncUse, F5_080429bc, Apply_08007c8c, unmatched
  08040834/08040cc4/0801757c/08007c04); NO .set for exact-match globals
  Sub_08007CF4 (4044c) and Sub_08042998 (402e0). Coordinator verify
  lesson: isolated-link stubs need .global before .set — plain .set is
  file-local and does NOT resolve cross-object undefined refs.
- Blocked refined: 08004e60 (25 diffs), 08007d64, 08034c1c (correction:
  12 B short for 4 reasons, not just adds+tail), 080400f8 (correction:
  o[0x46b3]=1, pool reuse, b not involved). Full details in
  staging/w37b_gaps/w37b_results.md.
- Full regression after B landings: 1064 sections, 1004 clean, 58 tail2b,
  2 pre-existing dirty — zero regressions.

## Workers C / D — D DONE, C PENDING
- D: 3 sanctioned asm transcriptions landed (0801ece8 268 B, 0801d6cc
  348 B, 0801ffbc 304 B; 6–7 C variants exhausted each). Landing hygiene:
  ChipSlot_Tick .globl/.set stripped (real build global T — would
  multiple-define); Call_0800D9EC/Call_0800D6E0/AbsScale_52A0 kept (not
  globals). 1d6cc catch: stripping left an empty __asm__( ); block —
  agbcc syntax error; removed the whole empty block. Strict verify: bin
  size must EQUAL extent (no truncation — worker's verify.sh truncates).
- D blocked: 08003874, 0800adc8, 080361e8 (cross-jumping wall: agbcc
  merges identical case tails, empty-asm barriers do NOT defeat it),
  0800c268 (analysis only). New idioms: u16 counter pattern
  (i = ((i<<16)+0x10000)>>16 under old_agbcc); pool-first vs idx-first
  dispatch (systematic version difference); mask narrowing (& -61 on
  byte store folds to movs #195 vs ROM negs form); pool byte-order —
  hexdump pools, objdump halfwords mislead (0x0804e05c, not 0x08045ce0);
  transcription post-processing (branch-decoding pools -> .word; gas
  0x46c0 pads vs ROM 0x0000 -> explicit movs r0,r0 after final bx).
  Twins 0x08003b70/0x08003e80 NOT identical (12 differing bytes).
- D Part 2 (blocked revisits) NOT started — reassigned to Wave 38.
- Coordinator bonus: 0x0801edf4 gap (32 B, inside 0x0801ece8 window)
  matched first try via Slot_FetchWord4 twin transfer; landed as
  w37coord_0801edf4_MATCHED.c (section .text.w37coord_0801edf4).
- C: bulk lines 251–450 — PENDING at last check.

## Worker C landing (coordinator, 2026-10-24)
- All 24 claims independently re-verified: clean-room recompile (cpp -> old_agbcc/main -> as -> ld .text wildcard at true ROM address -> objcopy -> cmp, bin size == extent) + in-built-ROM extraction after landing. 24/24 pass both.
- Patch-claim lesson: worker .patch.txt docs use space-separated mnemonics ("ldr r3, .L4+16") while agbcc .s uses tabs ("\tldr\tr3, .L4+16") plus @cond_branch comments and add/adds spelling variants — naive exact-match of doc text against .s fails on all 4. Coordinator applied the patches with the exact generated .s text (verified unique occurrence per file) and converted them to Python patch scripts (mmbcc/tools/fix_w37c_080192dc_patch.py, fix_w37c_08018510_patch.py, fix_w37c_0801e028_patch.py, fix_w37c_080231d0_patch.py). Future briefs: patch scripts must be generated against the actual .s, not hand-written from the doc.
- Section-attribute lesson: C's staged files have NO section attribute (default .text) — the worker's harness links .text wildcard, which works standalone but NOT in the real ldscript (slots need named sections). Landed copies gained __attribute__((section(...))) before the function definition; codegen unaffected (verified in-built-ROM 24/24).
- .set audit: 44 distinct .set names across the 24 files; 33 stripped (nm-verified GLOBAL T/A at identical address in the pre-landing build), 11 kept (not globals under those names — incl. Sub_0800B148 whose real build name differs, Memset16, and the same-wave Sub_0804CB28 kept as .set since it was not yet a global at strip time).
- Registry: 24 MATCHED rows + 5 BLOCKED rows + 2 UNMATCHED gap rows (0x08017600, 0x08023264) appended; distinct MATCHED now 1101.
- Worker C coverage: lines 251–282 only (32/200 rows: 24 matched, 5 blocked, 3 skipped as already-registered). Remainder assigned to Worker C2 (staging/w37c2_bulk/): lines ~283–450 + D Part 2 (03874, 0adc8, 361e8, 0c268) + gaps 17600/23264.

## Worker C2 landing (coordinator, 2026-10-24)
- Handoff-count trap: C2's handoff said "Matched this run (2)" but RESULTS.md's Matched section lists 12 (10 from the worker's earlier phase + 2 from the latest phase). Coordinator reconciled against RESULTS.md (not the handoff summary) and verified all 12. Lesson: the handoff's "this run" count may cover only the latest phase — always enumerate RESULTS.md's Matched section.
- All 12 independently re-verified: clean-room recompile (cpp -> old_agbcc -> as -> ld .text wildcard at true ROM address -> objcopy -> cmp, bin size == extent) + in-built-ROM extraction after landing. 12/12 pass both.
- Section-attribute lesson (same as C): staged files have NO section attribute — landed copies gained __attribute__((section(...))) before the function definition; codegen unaffected.
- .set audit: 14 distinct names; 10 stripped (nm-verified globals), 4 kept — including the ChipInit/ChipInit_080178A8 pair (same address, different names: strip the _080178A8 one, keep the generic ChipInit one since it is NOT a build global under that name).
- Registry: 12 MATCHED rows + 52 BLOCKED rows appended; distinct MATCHED now 1113.
- C2 coverage: lines 283–346 (68/200 lines: 11 TSV matched + 1 gap leaf matched, 56 blocked incl. analysis-only, 1 skipped 07678). Remaining lines 347–450 + D Part 2 + gaps 17600/23264 roll to Wave 38.
- Deferred: 23c38 __modsi3->0x0804dda0 landing form (function still BLOCKED, 1 variant tried — decide at landing time, not now).
