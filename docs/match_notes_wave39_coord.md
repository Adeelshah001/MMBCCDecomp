# Wave 39 Coordinator Report (daily-cron-owned wave, 2026-10-25)

Coordinator only: workers staged, coordinator verified + landed. No chat
message sent; PROGRESS.md and docs/progress_history.tsv NOT touched
(parent owns those).

## Headline

- **1154 / 1677 distinct MATCHED addresses = 68.8%** (was 1140 / 1677 = 68.0%, +14)
- ASM extras unchanged: 13; **byte-identical total 1167** (was 1153)
- BLOCKED rows: 420 → 427 (7 appended); distinct still-blocked addresses: 276 → 272
- **70% MILESTONE NOT CROSSED**: 70% of 1677 = 1174 matched; shortfall = 20.

## Baseline-first finding (rule 17) — build was NOT green

A clean `make clean && make -j1` failed at link time, twice:
1. `ld: cannot find build/w33c_080221cc.o` — ChipInit_080221CC (Wave 33
   MATCHED, ldscript slot + build rule present) was missing from SRCS_C.
2. Then `build/w33d_0804c8a4.o` — LoopSet_0804C8A4 (Wave 33 MATCHED),
   same omission.
Both had been masked by stale `build/` objects; `make clean` exposed them.
Fix (coordinator repair, not a new claim): added both files to SRCS_C.
Full audit after the fix (SRCS_C block vs all 645 ldscript objects vs
MATCHED registry sources): no other gaps, no MATCHED source missing from
disk. Clean `make -j1` then succeeded (8,388,608 B); both repaired
regions 0-diff (0x080221cc/196 B, 0x0804c8a4/72 B).

## Landed (14) — every claim verified standalone AND in-built-ROM, 0 diffs

All C landings use old_agbcc -O2 -mthumb-interwork. Section attributes
added at landing; T-global `.set` lines stripped (see catches).

| Address | Size | Worker | Form |
|---|---|---|---|
| 0x08009140 | 248 B | D | old_agbcc |
| 0x0803b898 | 256 B | D | old_agbcc |
| 0x080285c4 | 376 B | A | old_agbcc (twin) |
| 0x08048084 | 376 B | A | old_agbcc (twin) |
| 0x0803895c | 376 B | A | old_agbcc |
| 0x0802f5ac | 896 B | B | old_agbcc |
| 0x08015278 | 256 B | C | old_agbcc + .s patch (bhi→bgt) |
| 0x0801a72c | 240 B | C | old_agbcc + .s patch (bhi→bgt) |
| 0x08013708 | 220 B | C | old_agbcc |
| 0x0801519c | 220 B | C | old_agbcc |
| 0x08042b60 | 164 B | C | old_agbcc |
| 0x08023f28 | 168 B | C | old_agbcc |
| 0x08037700 | 148 B | C | sanctioned asm transcription |
| 0x0800c964 | 172 B | C | sanctioned asm transcription |

Landed files: mmbcc/src/w39{*d,a,b,c}_MATCHED.{c,s} (14), patch tools
mmbcc/tools/fix_w39c_08015278_patch.py + fix_w39c_0801a72c_patch.py,
Makefile SRCS_C + per-file rules, ldscript slots (14, before /DISCARD/).
Registry: 14 MATCHED rows + 7 BLOCKED update rows appended (append-only;
old BLOCKED rows left intact). Staging preserved under staging/w39{*}/.
Coordinator verification scripts: staging/w39coord_verify/verify_d.py,
verify_asm.py, verify_patch.py, land_w39.py, append_registry.py.
Pre-landing registry backup: staging/w39coord_verify/match_status_before_w39.tsv.

Staged-file SHA-256 (at worker completion, re-checked at landing):
- D: 9b26d038… (09140), 28051afd… (3b898)
- A: c0688b90… (285c4), 0566337e… (48084), edafa840… (3895c)
- B: 9781abcb… (2f5ac)
- C: c51954dd… (15278), 77a6f840… (1a72c), f322a6d4… (13708),
  b9e2744d… (1519c), c8bc8c72… (42b60), b535e9cb… (23f28),
  4b2ec742… (37700.s), 05354ffd… (0c964.s)

## Extent determinations (Worker D, coordinator-confirmed)

- 0x08009140: TRUE 248 B (not 244). Next fn 0x08009238 `push {r4, lr}`;
  disputed bytes are the last pool word 0x0806b560 (referenced by the gate).
  The 244 B figure was a built-size shortfall, not an extent.
- 0x0803b898: TRUE 256 B (not 2464). Next fn 0x0803b998
  `push {r4-r7, lr}`; 2464 B skips over it and an interior label.
- 0x080171c0 (Worker B): TRUE claim extent 508 B (not TSV 532 B). Code
  ends 0x080173b8 + 2 pad bytes; unlisted 24 B function at 0x080173bc
  (20 B code + 4 B pool) follows — Wave 40 gap candidate, NOT counted.
- 0x08037700: TRUE 148 B (not W38 160 B); next fn 0x08037794 prologue.
- 0x08013708 / 0x0801519c: 220 B each; 1519c ends exactly at 15278
  (adjacent, no overlap). 13708's end 0x080137e4 is a `push {r4-r6, lr}`
  prologue; 23f28's end 0x08023fd0 is a `push {r4-r7, lr}` prologue —
  both confirmed by disassembly even though neither end address is in
  the coordinator's start-set extract.

## Blocked table (re-attempted with variants this wave)

| Address | Size | Best | Blocker |
|---|---|---|---|
| 0x08003874 | 304 B | 272 diffs | Register-offset ldrsh wall; needs .s patch (out of pure-C scope) |
| 0x080118a4 | 288 B | 241 diffs | Cross-jumping merges duplicated Inc4_Clear5_7 calls; -fno-crossjumping rejected by both compilers |
| 0x08019904 | 304 B | 210 diffs | Cross-jump sharing + missing dead buf load + double-& folding |
| 0x08035c5c | 332 B | 248 diffs | One extra `add r3, r0, #0` for loop-1 flag |
| 0x080171c0 | 508 B | 142 diffs | Allocator/expansion diffs (case-2 sc&3 temp, d-ternary lsl/negs/lsrs form, copy forwarding) |
| 0x0801e890 | 172 B | 52 diffs | W38-C baseline re-confirmed; direct-Setup angle disproven — do NOT use W39-C v3 |
| 0x08023c38 | 172 B | 101 diffs | High-register allocation wall; C variants only (transcription NOT sanctioned yet) |

Not attempted with variants (triage/disassembly only — record as
unattempted, NOT as attempted blocks): Worker A 87 triage rows, Worker B
98 range lines. Worker C unattempted: 0x08017b6c (404 B) and 0x0802129c
(400 B), characterized leaf functions needing dedicated effort.

## Full regression

`mmbcc/tools/regression_check.py` on the landed build:
**1145 sections | 1085 clean | 58 accepted 2B c046 tail artifacts |
2 dirty — ZERO regressions.**
Dirty are the same 2 pre-existing: 0x080004fc .text.mainloop (3 diffs,
len 4) and 0x0804cde8 .text.text_open (3 diffs, len 4).

## Coordinator catches (rule that caught each)

1. **Baseline-first (rule 17):** clean build failed — w33c_080221cc +
   w33d_0804c8a4 missing from SRCS_C (see above). Fixed before landing.
2. **Bulk-range label mismatch:** brief said line 550 = 0x08026880, but
   file line 550 = 0x08041b48 and 0x08026880 is line 552 (Worker B's
   range). Resolved by file-line authority: A = 451–550, B = 551–651,
   contiguous, no gap/overlap. Workers were briefed with the correction.
3. **Registry-check case trap (new instance of the nm-case trap):**
   registry addresses use UPPERCASE hex (e.g. 0x0801AA70); lowercase
   greps falsely report "no row". All 14 claims and all Worker C skips
   were re-checked case-insensitively. Worker C's 7 skips validated:
   5 chipinit functions ARE registry-MATCHED (uppercase rows), 111b4
   MATCHED (W33-D), 4db28 = CpuSet inside the .text.bios section.
4. **NM-case trap at landing:** stripped exact-case T-global `.set`
   lines — A: Copy4_2518C, Gfx_BlitRequest, CondRectFill_080070F0,
   CondRectFill_080073D4; C: SetBit16, Vec2_SetMirrored, ChipSlot_IncUse,
   Check119_Minus3_Le1, Text_SelectBlobIdx, DecIfNonZero_18,
   SetBytes_08011F68, ChipSlot_Tick, ChipInit_080178A8, GetField17_U8,
   Call4E60_4E44, PalModeSet_4DFC, SyncObjFlagBits_BEE0,
   ShiftPair_Copy_800C, EntryMgr_Teardown/Setup, Sub_08042D80,
   Scramble_400A8, SMod_0804DDA0; D: Memcpy16. KEPT (no T collision):
   F_080251D8 — the real global is F_080251d8 (lowercase d8), a
   different symbol; MemsetAligned_4E008 (ldscript BYTE(), no global);
   all lowercase-`a` aliases (Sub_08006DD8, Sub_0801AA70, Sub_0801CD50,
   Vec2_Add/CopyMirrored, Memset16, Sub_08002300, Sub_08007BEC);
   no-nm-line aliases (F_080253F8/2616C/2617C, F_0800DF8C, G_0800C22C,
   Sub_08017A44, Sub_0800499AC, Sub_080073D4, Sub_0802D7A0).
   Function-name collision check: none of the 14 landed function names
   exists as a build global.
5. **Patch-doc format trap:** patch claims verified against the ACTUAL
   generated .s — raw old_agbcc builds showed exactly 1 diff each
   (offsets 19 and 51); after applying the worker patch scripts
   (asserting exactly one `bhi` line) both are 0-diff. Makefile rules
   run the patch to a distinct `.patched.s` file (not in-place).
6. **Landing-script failure modes (rule 8, file not heredoc):** first
   run failed on the 0c964 transcription (its `.text` line uses spaces,
   not a tab — pattern widened) and on the SRCS_C anchor (actual name
   is `w38a_0801b728_MATCHED.c`, and the last SRCS_C line has no
   trailing backslash). Partial landed copies were removed and the
   script re-run clean; Makefile/ldscript were untouched until the
   successful run.
7. **Handoff-count trap (rule 12):** counts taken from RESULTS.md
   Matched sections, enumerated by the coordinator: D 2, A 3, B 1,
   C 8 = 14. No worker count trusted.
8. **Triage ≠ attempted:** A (87) and B (98) unattempted lines are
   disassembly triage only; they are NOT counted as blocked-with-variant.
9. **Transcription landing form:** W39-C .s files landed as src/*.s
   with explicit Makefile `as -mthumb` rules and named sections
   (`.text` renamed to the named section at landing), preserving the
   worker-verified bytes verbatim — instead of the riskier .s→__asm__
   string conversion used for some earlier transcriptions.
10. **Duplicate MATCHED rows exist** for a few addresses (e.g.
    0x08011e20) from multiple waves; headline uses DISTINCT addresses,
    so this does not inflate the count (verified: 1140 → 1154 = +14).

## What Wave 40 should target

- Priority revisits: 0x0801e890 (52), 0x08023c38 (101 — needs a
  sanction decision on transcription), 0x080171c0 (142), A blocked
  0x08003874 / 0x080118a4 / 0x08019904 / 0x08035c5c (cross-jump family:
  solving the duplicated-call-site merge likely unlocks several).
- Dedicated effort: gap callees 0x08017b6c (404 B) + 0x0802129c (400 B);
  gap function 0x080173bc (24 B, needs a registry/func-list row decision).
- Bulk lines 652+ of docs/wave34_unattempted.tsv.
- Triage follow-ups: A: 0x0804b634, 0x08026df4, 0x0804b7f0, 0x08049780
  (scripted/multi-call, no hi-reg/ldrsh); twin pair 0x08003b70 /
  0x08003e80 (ldrsh wall, same as 03874); B partial decodes 0x08015ac4
  (560 B SetMirrored jump table) + 0x0802d928 (464 B sparse switch).
- Do NOT reassign: 0x08030b1a (interior of 0x08030ad4), 0x080298fc /
  0x0803ca7c as single leaves without host/interior determination.
