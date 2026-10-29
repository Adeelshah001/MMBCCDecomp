# Wave 38 Coordinator Notes (partial — Worker D landed; A/B/C pending)

## Landed: F_08030AD4 (12,276 B giant dispatcher)
- Worker D staged sanctioned ASM transcription (gen_30ad4.py from W37-A
  structural map) in staging/w38d_30ad4/ (RESULTS.md, MAP.md,
  SHA256SUMS.txt — all hashes verified).
- Coordinator independent verification: standalone .s assembled + linked at
  0x08030ad4 → 12,276 B, 0 diffs vs baserom slice at file offset 0x30ad4.
- Landing: mmbcc/src/w38d_08030ad4_MATCHED.c (leading .text replaced with
  .section .text.w38d_08030ad4_asm,"ax" — note the staged file's first asm
  line uses a REAL TAB character, not backslash-t; line-number edit used).
  Makefile SRC + build rule added (AGBCC path, w37d precedent); ldscript
  entry appended before /DISCARD/ (no reorder, no overlap in the region).
- .set audit: all 28 externs use Ext_0800XXXX local aliases (no .globl),
  none collide with build globals — all kept (Wave 36 precedent: unique
  local aliases stay).
- In-built-ROM extraction: 12,276 B at offset 0x30ad4, 0 diffs. ELF section
  .text.w38d_08030ad4_asm at 0x08030ad4, size exactly 0x2ff4; symbol
  F_08030AD4 global T.
- Registry: MATCHED row appended (append-only). Distinct headline now
  1114 (was 1113). All 13 duplicate addresses carry REVERTED rows —
  verified, no genuine double-claims.
- Build green at 8,388,608 bytes after landing (sha1 of full ROM still
  differs — expected, ~563 functions remain).
- INTERIOR rows for 0x08033874/0x080338f4/0x08033962 left as history;
  they are labels inside this unit, not functions.

## Toolchain
- arm-none-eabi binutils missing at wave start (VM churn) — reinstalled
  from tools/host/binutils-arm-none-eabi_2.42-1ubuntu1+23_amd64.deb before
  delegating.

## Landed: Worker C (7 matched, 5 blocked revisits)
- All 7 independently verified 0-diff by coordinator (own pipeline:
  cpp -> old_agbcc -> [worker patch.py] -> as -> ld at true address ->
  objcopy -> cmp over TRUE extent) BEFORE landing.
- Pure C: 0x08017600 (32 B gap), 0x08023264 (20 B gap, trailing .hword 0).
- C+patch: 0x08023a7c (112 B TRUE, TSV 174 wrong), 0x0801bde4 (188 B,
  r7-save), 0x0801c6b0 (196 B, 2-register-field), 0x080234c8 (208 B,
  clamp-copy insert), 0x0800e144 (172 B, 2-site, net -4 B).
- Patch scripts copied verbatim to mmbcc/tools/fix_w38c_*_patch.py
  (two-arg IN.s OUT.s form; Makefile rule passes the .s twice — reads
  fully before writing, so in-place is safe). Patch docs are tab-accurate
  (Wave 37 lesson already applied by this worker).
- Section attributes added before each function definition
  (.text.w38c_<addr>); ldscript entries appended (no reorder); overlap
  check: no existing section starts inside any new range.
- .set audit (nm on mmbcc.elf): STRIPPED only uppercase-global names
  (T): Sub_08023BC4, Xor_23CE4, F_23D10, Sub_08023D68, F_23B64, SetBit16,
  MaxAssign_17, GetField17_U8 (has T), ChipSlot_IncUse, ChipSlot_Tick
  (has T). KEPT: Sub_08023C38, F_0801B98C, F_0801EBF0, F_0800D6E0,
  F_080042B8, F_0804DB28 (absent from build).
- COORDINATOR CATCH (nm-case trap): I initially stripped
  Vec2_CopyMirrored and F_0804A378 because nm showed them in the ELF —
  but they were lowercase 'a' (LOCAL absolute, from other objects' local
  .set stubs), NOT linkable globals. The link failed with undefined
  references; both .set lines were restored and the build went green.
  LESSON: nm hygiene must confirm UPPERCASE (A/T), never just presence —
  lowercase 'a'/'t' are local and do not resolve cross-object references.
  (Vec2_AddMirrored in vec2.o IS global T, so it needed no restore.)
- In-built-ROM extraction: all 7 sections 0-diff; full regression
  1112 sections — 1052 clean (+8), 58 accepted 2B c046 tail artifacts
  (unchanged), 2 pre-existing dirty (mainloop, text_open) — zero
  regressions.
- Registry: 7 MATCHED + 5 BLOCKED rows appended (append-only).
  Distinct headline now 1121 (was 1113).
- Worker C corrections recorded: 0x0801c6b0 case-1-true falls through
  into c2 (W37-C2 decode corrected); agbcc DOES emit ldrsb from C
  (gates 3/4 of 234c8) — "never emits ldrsb" rule narrowed to gate1-style
  patterns; 0x08023a7c TRUE extent 112 B (TSV 174 wrong).
- Blocked (W38-C revisits): 0x0801e890 (52 diffs, v2 NOT recovered),
  0x08037700 (126), 0x08042b60 (112), 0x08023f28 (78), 0x0800c964 (143).

## Landed: Worker B (5 matched, 3 blocked revisits)
- All 5 independently verified 0-diff by coordinator (own pipeline:
  transcriptions via main agbcc + named-section link; patch claims via
  old_agbcc + worker patch.py + symdef stubs) BEFORE landing. Extents
  structurally confirmed (next prologues at 0x0800aefc, 0x08036318
  [func_list entry], 0x0800c3a0).
- Transcriptions (sanctioned): 0x0800adc8 (308 B, 5+ C variants),
  0x080361e8 (304 B, 9 variants), 0x0800c268 (312 B, loop nest fully
  decoded; C-impractical: gcc hoisting + 72 B frame vs ROM 32 B).
- C+patch: 0x08004e60 (128 B, 25 diffs unpatched), 0x08034c1c (132 B,
  16 diffs unpatched; callee 34BD4 BLOCKED — landed with .set stub).
- .set audit (UPPERCASE = global): STRIPPED Sub_0800B470, Wrap_07818,
  ChangedBitsInit_080363EC, TblGetByte_241F8, SDiv_0804DD08. CONVERTED
  kept .globl+.set pairs to local .set only (drop .globl): Sub_0800B5C8,
  Clamp48, Sub200, Sub_08004F80, Sub_0800B148, Sub_0800B2D8, Sub_0800B368
  (Sub_0800B148/Sub_08004F80 are lowercase-'a' locals — kept per the
  nm-case lesson, not stripped).
- Coordinator catches: (1) Stripping SDiv left an EMPTY __asm__() block
  in the landed 0c268 file — agbcc syntax error; empty block removed.
  (2) Staged C files carried STALE Wave 37-B section attributes
  (.text.w37b_*) — my added .text.w38b_* attributes conflicted
  (agbcc "section conflicts with previous declaration"); stale
  attributes removed from 04e60 + 34c1c. LESSON: check staged files
  for pre-existing section attributes before adding landing ones.
  (3) Worker's standalone verification used harness symdefs for ALL
  callees — the landed 04e60 file needed .set stubs for the 3 absent
  externs (04EE0/052DC/0B8D0); 34c1c needed 34BD4 stub. 053A0/04EF4
  resolve from build globals.
- In-built-ROM extraction: all 5 sections 0-diff; full regression
  1117 sections — 1057 clean (+5), 58 accepted 2B c046 tail artifacts
  (unchanged), 2 pre-existing dirty (mainloop, text_open) — zero
  regressions.
- Registry: 5 MATCHED + 3 BLOCKED rows appended (append-only).
  Distinct headline now 1126 (was 1121).
- Blocked (W38-B revisits): 0x08003874 (272 diffs, gcc 2.9 never emits
  register-offset ldrsh from C — probes f1-f5), 0x08007d64 (64 diffs,
  pool misread corrected), 0x080400f8 (v2 128 B, missing 0x46a8 pool;
  v1 deeply broken, do not reuse).

## Worker A landing (bulk lines 347–450) — coordinator notes
- All 104 lines processed; 14 MATCHED, 90 BLOCKED, 0 transcribed.
  Staging: staging/w38a_bulk/ (RESULTS.md + SHA256SUMS.txt + WORKLOG.md
  + 105 staged .c files); hashes verified OK at coordinator intake.
- Coordinator verification (own pipeline, old_agbcc): all 14 0-diff over
  TRUE extents; every claimed end lands exactly on a next-function
  prologue (incl. 05130 → 0x08005208 NullCallback, already MATCHED).
- nm-case trap, second occurrence: `head -1` hid second nm lines.
  ChipSlot_Tick, GetField17_U8, MaxAssign_17, Text_SelectBlobIdx and
  Vec2_AddMirrored DO have T globals (stripped); ONLY Vec2_CopyMirrored
  is local-only (25 'a' entries, kept). RULE: grep ALL nm lines for a
  name, never the first line.
- SetBit16 adjudication: real callee is `void SetBit16(u8 *s, u8 bit)
  { s[16] |= (1 << bit); }` (wave7_g2_old.c) — takes a POINTER. Bulk
  callers pass the pointer LOADED FROM s+44 (`*(u8 **)(s + 44)`), not
  s+44 itself. Matched files already use the load form; no landing
  change needed. Same VALUE-from-s[44] pattern recorded for ChipInit /
  GetField / 1aa70 / 1cd50 / Dec 5th/6th args (revisit idiom).
- Landing tooling catch: heredoc python landing scripts failed
  reproducibly at the write step (FileNotFoundError on a valid path);
  the same logic as a FILE (staging/w38coord_verify/land_w38a.py)
  worked. LESSON: write landing scripts to files, do not heredoc them.
- Build catch: `make clean && make -j4` dropped targets (first
  w33c_080221cc, then w33d_0804c8a4 — a different file each run, no
  duplicate rules). Serial `make -j1` built green. LESSON: full
  rebuilds MUST use -j1; -j4 is only safe incrementally.
- No stale section attributes in any of the 14 staged files (unlike
  Wave 38-B). Kept .set stubs: Vec2_CopyMirrored (local-only),
  F_08024F88, Sub_080059A8, Sub_08006DD8, Sub_08017B6C, Sub_0801AA70,
  Sub_0801CD50, Sub_0802129C (all absent from build).
- In-built-ROM extraction: all 14 sections 0-diff; full regression
  1131 sections — 1071 clean (+14), 58 accepted 2B c046 tail artifacts
  (unchanged), 2 pre-existing dirty (mainloop, text_open) — zero
  regressions. Build green, 8,388,608 bytes.
- Registry: 14 MATCHED + 5 priority BLOCKED rows appended (append-only).
  Bulk convention confirmed: the 90-line blocked table lives in
  staging/w38a_bulk/RESULTS.md, NOT as individual registry rows —
  future bulk workers must check RESULTS.md as well as the registry.
  Distinct headline now 1140 (was 1126).
- Blocked priority revisits: 0x08015278 (256/17, size matches, 4
  sub-walls), 0x0801a72c (240/1, single bgt/bhi byte), 0x08013708 +
  0x0801519c (220/2, pool/shift swap — revisit TOGETHER), 0x0800ca98
  (177 diffs, only 2 variants — NOT at transcription threshold).
  Wall families for the 90: switch jump-table + shared inc (20),
  hi-reg prologue (17), 1823c walls (10+), goto-dispatch (8+),
  straight-line (4), jump-table dispatch + unclear pools (6).
- Wave 38 FINAL: D 1 + C 7 + B 5 + A 14 = +27. Headline 1140/1677
  (68.0%), 1153 byte-identical total. Milestone: 68.0% vs the 66.6%
  bar from the 1033 daily baseline — CROSSED (parent decides whether
  a milestone message is owed under the 2026-10-23 rule).
