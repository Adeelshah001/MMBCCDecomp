# MMBCC Decomp — Central Memory

Central, durable log for the Mega Man Battle Chip Challenge (GBA) matching
decompilation. Created 2026-10-29 in response to the user's 2026-10-28/29
question about a centralized `memory.md` that survives VM cleanup.

## Snapshot — 2026-11-08 (latest verified state; sections below are history)

- **C-matched: 1293 / 1677 (77.1%)**, 13 ASM, **1306 byte-identical total**.
  Registry `docs/match_status.tsv`: 3924 lines. Build green, reproducible:
  8,388,608 bytes, SHA-1 `5c17f049ba76a8b457e4a0663a8a2e04b0d04978`
  (in-progress build; `make compare` against the baserom SHA-1
  `72309736f3820470c6f372d6a05ad1f16bc5a946` is still the completion gate).
- Last verified wave: **Wave 388** (2026-11-07, +0). Waves 195–388 were
  re-verification under the manual method; the remaining hard functions
  and their per-wave bests / mechanism closures are in `DECOMP_MEMORY.md`
  (the detailed coordinator handoff file — read it first) and
  `PROGRESS.md`.
- **Work is halted as of 2026-11-08 at the owner's direction.** This
  repository snapshot is the fork-and-continue point: everything needed
  to build and to resume matching work is here except the baserom
  (supply your own legally obtained dump; see README/INSTALL) and the
  agbcc toolchain binaries (build agbcc @da598c1, see README).
- Sanctioned-exception landings are tagged in their sources (Wave 194:
  0x08012B80, 0x08042F44, 0x08037DE0, 0x080158DC). Invented-logic tricks
  remain banned. Open ruling questions are listed in `DECOMP_MEMORY.md`.

Honest history: before this file, decomp work was logged in `PROGRESS.md`
(the 1.3 MB running wave log), `docs/match_status.tsv` (the match registry),
Muse's curated `~/MEMORY.md` and daily `~/memory/*.md` notes — not in a file
named `memory.md`. This file does not replace those sources; it is the single
pointer + verified headline so the state can be recovered without digging
through wave notes.

## Retention — why this file survives cleanup

- Lives at `~/workspace/mmbcc-decomp/memory.md` — the project root, in the
  persistent workspace, alongside `PROGRESS.md`, `ANALYSIS.md`, and `PLAN.md`.
- It is NOT in `/tmp` (wiped by VM churn — Wave 15 lost claims that way),
  NOT in `staging/` (per-wave scratch, routinely superseded), and NOT in
  `mmbcc/build/` (build output).
- Update rule: updated on the daily 9:00 AM summary and on milestones only,
  not per wave — matching the user's reporting rule (daily summary +
  70%-then-+5% milestones only, no per-wave chat updates). From 2026-10-30,
  also updated at each manual-phase handoff (see below), per the user's
  explicit direction that this file be logged into and drawn from.

## Handoff — manual phase, 2026-10-30 (user direction, MMBCCDecomp chat)

- **Direction (2026-10-30, 11:54 EDT / 15:54 UTC):** decompile the remaining
  functions by hand, manually; use GBA emulator source (VBA / mGBA) as a
  reference for resolving functions that do not match; keep a handoff and
  this core memory file, logging into it and drawing from it.
- **What this changes:** the automated wave chain is HELD — no Wave 122
  was spawned by Wave 121's coordinator, and no new wave starts until the
  manual phase (or a fresh parent decision) says so. This respects the
  standing no-parallel-coordinator rule: one line of work at a time.
- **Starting state (verified 2026-10-30):** 1280 / 1677 C-matched (76.3%),
  1293 byte-identical total, registry 3374 lines after Wave 121 appended
  32 BLOCKED rows and landed 0. Remaining: 397 C functions. Next
  milestone 80% at 1342 / 1677 — 62 short. Build baseline unchanged:
  8,388,608 bytes, SHA-1 03970057b4a502a5ce77b804d9120bc7db034484;
  baserom SHA-1 72309736f3820470c6f372d6a05ad1f16bc5a946.
- **Manual-phase queue (in order):** (1) the flagged 0-diff forms awaiting
  parent rulings — 0x08012B80 v10 alias (gates 1281), 0x08037DE0 P8
  (sanctioned ldrsb + pins), 0x080158DC bppinr0 pin — plus the other
  open rulings (0x08041D0C B6, 0x08020C00 membar, 0x0803A2E8 -O1,
  0x08023E34 4-diff floor, 0x08020A14, 0x0801DE84 sin-pin); (2) the Wave 121
  target-list bases — FD50 jeq3 (56/56, shared65 +150–+163 live region),
  088C4 a4b (349/377), 1FD8C 6934swap (173/197, 24 B short),
  1CEAC v11 (45/45). Full detail: PROGRESS.md Wave 121 section.
  Nothing in this queue is landed until it is a clean, unflagged 0-diff
  verified against the true function extent.
- **How emulator reference is to be used:** VBA / mGBA source is a
  behavioural reference only — ARM7TDMI CPU, PPU, DMA, timer, interrupt
  and BIOS (SWI) behaviour — to explain what hardware-affected code must
  do, so a hand-written C form can be judged semantically, not just by
  diff count. It does NOT change the completion gate: a function counts
  only when agbcc output is byte-identical in the rebuilt ROM.
- **Handoff rule for every manual session:** start by reading this file,
  the PROGRESS.md Wave 121 target list, and docs/match_status.tsv; end
  by appending the session's outcome here (functions landed, functions
  ruled on, functions still blocked and why). Do not re-attempt
  0x08001800 (permanently blocked, Wave 48). Legal line holds throughout:
  user supplies the baserom; no ROM in any repo, no ROM downloads.
- **Correction to the 2026-10-29 section below:** the GitHub push it
  records as "underway, NOT yet verified" is recorded as COMPLETE in
  curated memory on 2026-10-29 (two commits, b99a2a65 + 0aeaa01f, after a
  single bulk commit hit HTTP 413; no content dropped). This run did not
  re-verify the push live on GitHub; the delivery agent should re-check
  the repo HEAD before repeating the hashes as live fact.

## Verified headline — 2026-10-29 daily summary (09:05 EDT / 13:05 UTC)

- **C-matched: 1280 / 1677 (76.3%)**, +10 since the 2026-10-28 daily (1270).
  Waves 72–120 contributed: W72 +1, W73 +2, W74 +2, W78 +1, W83 +3, W84 +1;
  all other waves in that stretch landed +0.
- **Byte-identical total: 1293** (1280 C + 13 ASM-verified).
- Build: 8,388,608 bytes; Wave 120 preflight SHA-1
  `03970057b4a502a5ce77b804d9120bc7db034484` (in-progress build).
- Completion gate (unchanged): rebuilt ROM must be byte-identical to the
  baserom — `make compare` on SHA-1
  `72309736f3820470c6f372d6a05ad1f16bc5a946` (header title `BATTLECHIPGP`,
  game code `A89E`). "Matched" always means byte-verified by build + diff.
- **Next milestone: 80% at 1342 / 1677 — 62 short.** 70% and 75% already
  crossed and notified; no milestone was crossed on 2026-10-29.
- Chain status at the daily: Wave 121 in progress (registry still at the
  Wave 120 level, 3342 lines); no Wave 122 until Wave 121 is verified, per
  the no-parallel-coordinator rule. The 2026-10-28 daily run had timed out
  during an earlier Wave 121 attempt — that attempt is unresolved, with only
  Worker A partial staging (19 files), nothing landed.

## GitHub push — status at creation of this file

- User directive (2026-10-28): push current decomp progress to the
  MMBCCDecomp repo as one bulk commit, Petari-style page
  (https://github.com/SMGCommunity/Petari), then continue decompiling.
- Push coordinator spawned 2026-10-29, working in a separate staging copy
  (`~/workspace/mmbcc-decomp-push/`, Petari-style README + `docs/STATUS.md`
  verified 2026-10-29, ROM/build/staging/recomp excluded, live tree
  read-only). As of the 2026-10-29 morning check that staging copy had no
  `.git` commit yet — push is underway, NOT yet verified live. Do not treat
  it as complete until a commit hash is verified on the repo.

## Durable facts (do not re-litigate without new evidence)

- Toolchain: agbcc @da598c1, binutils-arm-none-eabi 2.42 (backed-up .deb in
  the project; the toolchain has vanished from /usr/bin repeatedly on VM
  churn and been reinstalled from backup).
- Scope correction: ~1,677 functions (not 14,102 — the recomp count included
  data regions); code is ~320 KB of the 8 MB ROM. Denominator 1677
  confirmed in Wave 46; three denominator candidates are pending parent
  decision and NOT applied: 0x0801bb94, 0x08001bf8, 0x0801ebd0.
- Hardest Phase 4 sub-task: text is a custom Capcom `BE 66 BC 00`
  container, codec unknown. Audio is a proprietary Capcom driver (stretch
  goal). Save driver fully mapped.
- Factory quirk reproduced by the build: header checksum byte 0x7B vs
  computed 0x94.
- Permanently blocked: 0x08001800 (Wave 48 coordinator-level decision —
  do not re-attempt).
- Staged 0-diff forms awaiting parent rulings (NOT landed): 0x08012B80 v10
  alias, 0x08037DE0 P8 (sanctioned ldrsb + pins), 0x080158DC bppinr0 pin;
  plus rulings on 0x08041D0C B6, 0x08020C00 membar, 0x0803A2E8 -O1,
  0x0801DE84 sin-pin, 0x08023E34 4-diff floor, 0x08020A14 (4 diffs).
  Waves 103–120 all landed +0 — the remainder are the hard functions.
- Standing ops lessons: never run two coordinators in parallel; worker
  briefs require a registry check before any claim; registry updates are
  append-only; workers use workspace workdirs, never /tmp; verify every
  match against the true function extent, never a self-measured window; a
  byte-match does not guarantee semantic correctness — re-read the
  disassembly even after a match.
- Legal line (holds throughout): pret-style, user supplies the baserom,
  no ROM in any repo, no ROM downloads or distribution.

## Authoritative sources (this file summarizes, it does not supersede)

- `PROGRESS.md` — running wave-by-wave log (Wave 120 section is the last
  fully verified wave at the 2026-10-29 daily).
- `docs/match_status.tsv` — match registry (recount: 1293 MATCHED rows,
  1280 distinct C addresses, 13 ASM).
- `ANALYSIS.md`, `PLAN.md` — ROM research and multiphase plan.
- Goal workspace: `~/workspace/goals/decompile-mega-man-battle-chip-challenge-gba/GOAL.md`
  and the 9:00 AM `mmbcc-decomp-daily` cron summary.
- Muse memory: `~/MEMORY.md` and `~/memory/YYYY-MM-DD.md` daily notes.
