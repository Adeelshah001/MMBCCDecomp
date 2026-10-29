# Wave 37 Worker Brief (MMBCCDecomp)

You are a Wave 37 worker for the MMBCC matching-decomp project at
~/workspace/mmbcc-decomp/. Read this whole brief before starting.

## Project layout
- Project root: ~/workspace/mmbcc-decomp/
- Pret-style project: mmbcc/ (Makefile, ldscript.ld, src/, tools/)
- Docs: docs/func_list_v2.txt (+ addenda), docs/xrefs.tsv, docs/symbols_phase2.md,
  docs/match_status.tsv (registry), docs/match_notes_wave*.md, PROGRESS.md
- Baserom (READ-ONLY, user's own legal dump): ~/workspace/megaman-bcc-recomp/rom/
  Mega_Man_-_Battle_Chip_Challenge__USA__0_8r4i.gba — 8,388,608 bytes,
  SHA-1 72309736f3820470c6f372d6a05ad1f16bc5a946. NEVER copy it into any
  repo, never download ROMs, never put copyrighted content in reports.
  Do NOT disturb ~/workspace/megaman-bcc-recomp/ (the recomp track).

## Toolchain
- agbcc @da598c1 + old_agbcc variant live in the project tools dir
  (mmbcc/tools/agbcc, old_agbcc). Build rule: cpp -> agbcc/old_agbcc -O2
  -mthumb-interwork -> as -> link at true ROM address -> objcopy -> cmp.
- arm-none-eabi binutils 2.42. If arm-none-eabi-* vanish from /usr/bin
  (VM churn), reinstall from the persistent backup:
  sudo dpkg -i ~/workspace/mmbcc-decomp/tools/host/binutils-arm-none-eabi_2.42-1ubuntu1+23_amd64.deb

## Hard verification rules (no exceptions)
- MATCHED means byte-identical, verified by build+diff. Near-matches are
  UNMATCHED and are NEVER counted.
- Every claim: non-empty assertions at every step (.o, .elf, .bin, ROM
  extract all non-empty), correct file offset (addr - 0x08000000), exact
  byte counts, FULL section extents including pools.
- Verify against the TRUE extent (neighbor address), NEVER a self-measured
  window. Trailing-pool false matches have burned us: a 0-diff on a short
  window is not a match.
- Check docs/match_status.tsv BEFORE claiming anything: scan ALL rows for
  the address, do not stop at the first hit. Duplicates get reverted.
- Registry updates are append-only (REVERTED rows for retractions).
- Verify pools from ROM bytes in LITTLE-ENDIAN (disasm misleads).
- Verify post-build section sizes for FIXALIGN1 functions.
- Order-preserving dedupe only (never sort -u on relocs).
- Isolated-link stubs need .global before .thumb_func+.set.
- nm hygiene: confirm GLOBAL (A/T), not just present.
- --section-start alone fails: custom .ld with explicit SECTIONS is the
  verified method. Thunks linked at ROM address. Makefile sed needs $$
  escaping. Never reorder ldscript without rebuilding and re-verifying.
- Never batch a script edit and its execution in one tool block.
- C-preference rule when adjudicating: pure C > C+patch > transcription.
  Sanctioned asm transcription via dis2asm2.py ONLY after 5+ C variants
  exhausted.

## Staging rules (MANDATORY after Overlap Incident 3)
- Stage ONLY under your assigned UNIQUE per-run directory (given in your
  assignment message, e.g. staging/w37a_<unique>/). Never reuse a shared
  waveNN_* name. Never write into another worker's directory.
- At worker completion, write a file-hash manifest (sha256sum of every
  staged source) in your staging dir so the coordinator can detect any
  later overwrite.
- Workers STAGE; only the coordinator lands into mmbcc/src/.
- Staged files must link standalone OR declare symdef needs explicitly
  (list every extern callee + its address in your results note).
- Never delete staging.

## Leave alone
Vec2_CopyMirrored (permanently blocked), Sram_VerifyCompare, MainLoop
(no new angles); B3 parked as likely second-vintage. 0x08030ad4: never
reassign at 68 B — true extent is 12,276 B (see below).

## Idiom catalog (recent, high-value)
dual-pin trunc chains; inline-asm copy-shift; mask-first split;
file-scope pad asm; twin transfer; reuse-the-pinned-base; integer-order
index; volatile reload defeats CSE-copy; stepwise-orr; statement-split
defeats pool folding; barrier on idx itself with pinned base; goto block
order = label definition order; split shift around pool loads; loop-top
zero var -> r6; inline-asm tst is structurally incapable of byte-identity
— .s patch is the correct tst mechanism; main agbcc pushes lr for
multi-block leaves while old_agbcc doesn't; =r barrier defeats pp+0x18B
CSE fold; goto-form switch forces ROM block layout; s32 temps for signed
ble; pool-load order follows first use, not declaration; LE halfword
misread trap; copy-shift for ldrh; constant-first AND via pinned fresh
variable; s16 loop counters need no asm; recursive loop form; single-return
ret-in-r1; unsigned shift matters; two-step ORR; declaration order drives
callee-saved allocation; never pin two live-overlapping vars to the same
register; dead reloads are real and hard; pool folding for small offsets;
pool-const pin; pool-barrier mechanism (gcc thumb_reorg dumps the literal
pool at the first BARRIER after the first constant load); clobber-reservation;
clobber-only asms defeat folds without recoloring; volatile-store DSE defeat;
s32 laundering; bl-target discipline for multiply-instantiated functions
(decode the ROM's bl target and stub the right copy); trailing-pool extent
correction (TRUE extent = max(code_end, max_pool_target+4)); do NOT clobber
a pinned reg; never pin r7 (context-dependent); pin-the-thief (pin ONLY the
variable stealing the wrong high reg); sanctioned asm transcription;
pin + post-process for fixed regs; "m"-constraint dummy forces a stack slot
with zero emitted instructions; explicit u32 stk[N] frame array guarantees
slot order; naked-asm idiom for compiler-impossible prologues; natural ldrsh
from C works for s16 v = tbl[i] (ldrsb never emits from C — use inline asm);
old_agbcc before fighting allocator rotation; single-expression
v=(*p&m)|k; try old_agbcc first on 2-reg allocator rotations.

## Your assignment
Your specific targets are in your assignment message. For each function:
name it from behavior, write C, compile with agbcc (try old_agbcc and
no-interwork variants when codegen diverges), diff against baserom bytes,
iterate until byte-identical. If blocked, write a precise blocker note
(diffs, wall description, next angle) — do NOT claim it.
Final report to the coordinator: matched list (address, name, size, compiler,
patch if any), blocked list with precise walls, new idioms found, staging
dir + hash manifest path. Do NOT land into mmbcc/src/ yourself.
