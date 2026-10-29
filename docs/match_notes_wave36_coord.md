# Wave 36 Coordinator Notes — 2026-10-24

## Headline
**1033 / 1677 C-matched (+103)**, 13 ASM (unchanged), **1046 byte-identical total**
(was 930/1674, 943). Full regression: 1024 sections, 965 clean, 57 accepted
2B c046 tail artifacts, 2 pre-existing dirty (mainloop, text_open). Zero
regressions. Build green: mmbcc.gba exactly 8,388,608 bytes.

## Count decision (1674 → 1677) — ADJUDICATED, see below
- W35 gaps 0x0800c5a4/0x0800cbdc: ACCEPTED as distinct functions (+2).
  Each is a 20 B leaf with its own bx lr terminator, tiled with no gaps
  between distinct neighbors (28 B predecessors 0x0800c588/0x0800cbc0 and
  BLOCKED FillPairs successors 0x0800c5b8/0x0800cbf0). Not interiors, not
  duplicates: this project counts functions by address, and twin code at
  distinct addresses counts separately throughout (cf. the many twin
  families). They were already inside the 930 numerator (landed W35); only
  the denominator was stale.
- 0x08027d48 leaf: ACCEPTED as a distinct function (+1). Predecessor
  0x08027d18 ends exactly at 0x08027d48 (48 B incl. pools); successor starts
  0x08027d4c with push {r4,r5,r6,r7,lr}; the 4 bytes (ldrb r0,[r0,#2]; bx lr)
  decode as a coherent leaf, not pool/interior. Landed as C-matched this wave.
- Total: 1674 + 2 + 1 = **1677**. The 930 numerator already included the two
  W35 gaps; this wave's numerator adds 103 (110 landed − 7 demoted, see below).

## Landed (103, all independently re-verified 0-diff from clean-room builds AND in-built-ROM extraction)
- E (8): 0x0802873c (60 B, main, inline-asm `add` spelling), 0x08001c08 (68 B,
  main, volatile reload), 0x0802fbf0 (56 B, old only, ppc reuse + `+r`
  barrier), 0x080272e0 (148 B, old only, case-0 load order native to old),
  0x0801a9ac/0x0801b8d0/0x0801cc94 (76 B each, main, split-orr twin family
  fully closed), 0x08027d48 (4 B, main, leaf getter).
- A (16 of 23 claimed; 7 demoted, see below): 0x08007c8c, 0x08007e9c,
  0x08007eec (56 B, not TSV 80), 0x08007324, 0x0800dea4, 0x080008c0, 0x0800b470,
  0x0801054c, 0x080429e0, 0x0801db40, 0x08023110, 0x0802f550, 0x080060c4,
  0x0800675c (landing fix: missing `typedef unsigned char u8;` added),
  0x08015a60, 0x08046904 — all main agbcc.
- C (17): 0x0801e0d0 (old), 0x08026a84 (main), 0x08019f38/0x0801a81c/
  0x0801cac4/0x08021628/0x08018f34/0x08019c94/0x0801a19c/0x0801ae70/
  0x08011f88 (old), 0x08012108 (main), 0x0801a2bc/0x0801a568/0x0801c108/
  0x0801c628 (old), 0x08038520 (main).
- D (28, all old): pure C 15 (0x080054d0, 0x080188f4, 0x08018c84, 0x08018ea4,
  0x08019248, 0x08019374, 0x080194b4, 0x0801a3f0, 0x0801b1b8, 0x0801b244,
  0x0801c254, 0x0801c774, 0x0801c91c, 0x08024b3c, 0x08024e2c); C + .s patch 13
  (0x0801af58, 0x0801b04c, 0x08022700, 0x080227dc, 0x08027374, 0x0802daf8,
  0x0802fc70, 0x08046960, 0x080053a0, 0x0800cde8, 0x0800ce7c, 0x08020f70
  (144 B incl. unlisted 16 B helper at 0x08020ff0 — reproduced inside the
  section, NOT claimed separately), 0x08022290). Patch scripts copied to
  mmbcc/tools/fix_w36d_*.py with per-file Makefile rules.
- B/B2 (34, all old): inherited 5 (0x0801aacc pure C, 0x08021ed4 +
  0x0802329c C + patch, 0x0800419c, 0x0804b5cc pure C) + 29 new (0x080098c4,
  0x0800cc94, 0x0800ed44, 0x0800eed4, 0x0802142c, 0x08025e5c, 0x080280e8,
  0x0802e9f8 pure C, 0x08045fcc pure C, 0x08007cf4, 0x0800c41c, 0x08010b30,
  0x0801b91c (80 B true, not 112), 0x0801cce0 (80 B true), 0x08023d68 pure C,
  0x08028900, 0x0802d670, 0x0800e994, 0x08011eb0, 0x08023bc4, 0x08034eb8,
  0x0803ff0c, 0x08000e80 (56 B true), 0x080114e8 (72 B true), 0x0801a9f8
  (88 B true), 0x0804c630, 0x0800a0d4, 0x08010750, 0x0801bfb4).
  Patch scripts copied to mmbcc/tools/fix_w36b_*.py with per-file rules.
  Data symdefs (Base/B/Table/Table2/Struct2/Val/Arg2/Cnt) live in a
  SEPARATE file mmbcc/asm/w36b_syms.s — NOT in the C files, because an
  in-file .set lets GAS fold e.g. Table+143 into one pool word and change
  the code shape (0x0800c41c worker note, honored).

## Coordinator actions / catches
- **7 Worker A claims DEMOTED to BLOCKED + REVERTED (not landed):**
  0x0801b428 (4 diffs), 0x0801b520 (4), 0x0801b880 (4), 0x0801e93c (9),
  0x080248c4 (9), 0x0803449c (8), 0x0804c72c (5). The on-disk staged files
  lack the worker's claimed final idioms (e.g. 1b428's pinned-r0 AND
  accumulator, 248c4's pinned r6/r3, 3449c's pinned r5/r0) and fail both
  clean-room re-verification and the full-build regression. Their
  mtimes (15:54–16:23 UTC) postdate Worker A's completion (15:08 UTC) and
  the coordinator's first verification pass — the staged files were
  overwritten after Worker A finished, by an unidentified concurrent
  writer (see "Workspace collision" below). The 7 were removed from
  src/Makefile/ldscript, rebuilt, and the regression returned to zero
  regressions. Their MATCHED rows stand with REVERTED rows appended
  (append-only convention) + BLOCKED rows carrying the current diffs.
- **A 0x0800675c staging defect fixed at landing:** staged file missed
  `typedef unsigned char u8;` and did not compile as staged; adding only
  that typedef yields 0 diffs over 96 B. The worker's "re-verified from
  finalized form" claim was not true for this file.
- **B2 0x0801aacc landing fix:** the matched callee at 0x0801ab34 is
  defined in the build as `Sub_1AB34`, not `Sub_0801AB34` — the worker's
  extern-only reference would not link. Added a local
  `.set Sub_0801AB34, 0x0801ab34` at landing (unique name, byte-safe).
- **.set hygiene:** stripped .set lines ONLY where the name is a current
  build global at the identical address (verified via nm: EntryMgr_*,
  _call_via_r1, Vec2_AddMirrored, ChipSlot_Tick, Sub_080241D0, etc. —
  25 strips). Unique local aliases (Sub_0800D9FC, Sub_08004E44, Worker_*,
  etc.) were KEPT: stripping them would break the link (no global by
  that name), despite one worker note suggesting otherwise.
- **Registry format fix (transparent, same run):** the first append wrote
  MATCHED addresses via Python %#x, dropping the leading zero
  (0x801b428 instead of 0x0801b428). All 110 were canonicalized to
  0x%08x in place before any other consumer ran; a future canonical scan
  would otherwise have missed them (Wave-31 duplicate hazard).
- **Registry counting method:** headline C-matched counts distinct
  functions whose MATCHED claim stands: pre-wave 930 + 103 new = 1033.
  The 6 historical REVERTED rows cancel duplicate claims only (each of
  those addresses retains a standing MATCHED row), so they do not reduce
  the count; the 7 new REVERTED rows cancel single claims, so they do.
  Row counts: MATCHED rows 1046, BLOCKED rows 350 (+45), INTERIOR 32 (+2),
  UNMATCHED 16, ASM 13, REVERTED rows 13.
- **Pre-existing quirk noted, not touched:** two Wave 9-D rows
  (0x0800800c, 0x08010508) carry wave field "36" in the registry though
  their notes say W9-D — a stale labeling quirk, not Wave 36 work.

## Workspace collision — FLAG FOR PARENT (needs investigation)
- staging/wave36_A files were rewritten between Worker A's completion
  (15:08 UTC) and landing (16:23 UTC): mtimes 15:54–16:23 across many A
  files, during workers C/D/B2 runs. Content proves overwrite, not
  worker error alone: current files lack the final idioms Worker A's
  results note describes, and 7 fail verification that the worker's
  claimed versions passed. The other 16 rewritten A files still match
  (confirmed by the build regression), and no E/C/D/B file was affected
  (all confirmed clean in the final regression).
- Possible causes: another coordinator/worker sharing the workspace or
  staging dir names, or a re-run of Worker A. The parent should check
  whether any other agent was writing to staging/wave36_A in that window.
  Mitigation for Wave 37: workers stage under unique per-run dirs and the
  coordinator snapshots (hashes) staged files at worker completion before
  any landing work.

## 0x08030ad4 TRUE EXTENT — PINNED (no match staged)
**0x08030ad4 – 0x08033ac8 = 12,276 bytes (0x2FF4).** Coordinator
spot-confirmed: no bx lr / pop {…,pc} in range; shared epilogue at
0x08033ab2 ending bx r1 at 0x08033ac2; trailing pool 0x02005168 at
0x08033ac4 loaded by ldr at 0x08033a7e; next prologue at 0x08033ac8.
Interior labels 0x08033874, 0x080338f4, 0x08033962, 0x08033ab2 are NOT
separate functions (INTERIOR rows added for the two newly encountered).
Any future match attempt must compare over the full 12,276 B.

## Blocked / parked (registry-logged this wave)
- A (19 incl. 7 demoted), C (19), D (6), B (1: 0x08010fdc). E: none.
- Confirmed compiler walls: base-first table loads (0x080174f4/0x080178fc),
  ldrsb for s8 args (0x08043890/0x08046038/0x0804380c/0x0804044c),
  pool factoring (0x08034c1c), nested s16 loops (0x0800c7e8/0x08027f80).
- Gap candidates NOT claimed (future targets): 0x08007f24, 0x0801e970
  (A hidden siblings), 0x0801b96c, 0x0801cd30, 0x08000eb8+, 0x08011530,
  0x0801aa50 (B gaps), 0x08020ff0 helper (inside landed 0x08020f70 section).

## Next (Wave 37)
- The 7 demoted A functions, re-derived from the worker's described
  idioms (pinned-r0 AND accumulator for 1b428/1b520/1b880; pinned r6/r3
  for 248c4; pinned r5/r0 for 3449c; pool-load order for 4c72c; 1e93c
  from its 9-diff profile).
- 0x08030ad4 as a unit (12,276 B dispatcher) — or its handler blocks via
  transcription if C proves infeasible.
- Gap functions: 0x08007f24, 0x0801e970, 0x0801b96c, 0x0801cd30,
  0x08000eb8+, 0x08011530, 0x0801aa50.
- Bulk continuation: docs/wave34_unattempted.tsv lines 251+ (lines
  109–250 are now fully accounted: 95 bulk matched + 45 blocked +
  2 interior = 142; plus E's 8 closers = 103 wave matches total).
- Blocked revisits with Wave-36 idioms (19f38 clamp-copy family template,
  data-symdef separate-file pattern, strip-only-on-global-collision rule).

## Wave 36 reconciliation (chat-spawned coordinator, 2026-10-24)

Overlap Incident 3 follow-up: the chat-spawned Wave 36 (workers A/B/C/D) ran in parallel with the cron's Wave 36. The cron completed first and demoted 7 worker-A claims after finding overwritten staged files. This section records the reconciliation.

### Verification method
Coordinator script `staging/wave36_coord_verify/verify_w36coord.sh` (clean-room: cpp → agbcc/old_agbcc -O2 -mthumb-interwork → as → link at true ROM address with sym stubs → objcopy → cmp vs baserom, non-empty assertions at every step, exact section sizes, full extents incl. pools). All 27 landed claims passed clean-room verification AND in-built-ROM extraction (26 clean + 1 TAIL2B).

### Landing notes
- Chat B files used harness symdefs, not in-file .sets: landed copies gained file-scope local `.set` stubs (no .globl) for all 21 extern callees. Build linked clean after this fix.
- No .globl in any of the 27 landed files — local .sets cannot cause multiple-definition conflicts.
- Patch scripts copied to mmbcc/tools/: fix_0800cb70.py, fix_08028970.py, fix_0801e93c.py (no collisions).
- Headline counting rule clarified: distinct addresses with a MATCHED row (1060) is the headline. Latest-status counting (1056) undercounts by 4 because the old duplicate-reverted addresses (0x08011e20, 0x080173d4, 0x0801787c, 0x0801e14c) ARE in the build — their REVERTED rows revert duplicates, not the claims. The 7 demoted claims were different: their REVERTED rows reverted the claims themselves (removed from build), which is why the cron's headline excluded them until restoration.
- My own tool-block race: a verify-script edit and its execution batched in one tool block raced (all-ld-fail from the pre-edit script). Re-ran after edits: all passed. Lesson: never batch a script edit and its execution in one tool block.

### New idioms (from chat workers, for Wave 37 briefs)
- Dual-pin a trunc chain (pin temp AND result with a barrier on the temp).
- Same-register pinned vars must be assigned at use point, not initialized at declaration (gcc 2.95 coalesces).
- Inline-asm copy-shift (`lsl %0,%1,#n`) for ldrh-then-shift / index-shift cases.
- Mask-first split for `& ~k` (compute mask into result register first, then AND).
- Barrier defeats constant folding of base+offset (`dst = CONST; barrier(dst); dst += 43;`).
- File-scope pad asm (`.short 0x0000` after the closing brace; after-return asm is dropped; GAS default pad is `c0 46`, not `00 00`).
- Reuse-the-pinned-base (reuse `ppc` itself for slot 2 instead of a fresh `p2` var).
- Integer-order index (`*(u8 *)(s[1] + tbl)` gives ROM's `adds r1,r2,r1`).
- Volatile reload defeats CSE-copy (plain reload collapses to an `adds` copy).
- Stepwise-orr for movs-first order (`f = 2; f |= s[10]; f |= 1;`).
- Twin transfer (19f38 family): clone a matched source, change only setup-call choice + constants.
- Else-adds block order (orr-first/adds-after, not `if (t == 0)` order).
- Fall-off zero return (omit trailing `return`; void epilogue gives `pop {r0}` + `bx r0`).
- Temp-split for movs-between-stores order.
- gcc commutes `adds` operands regardless of source order (34c1c counterexample to addend-order idiom).
- gcc folds `base + offset` into a single pool even in array-index form (402e0).
- gcc loads the second byte first in a two-byte sum regardless of source form (4044c scheduling wall).
