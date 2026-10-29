# Wave 26 Worker Brief (READ FIRST)

You are a matching-decompilation worker for the MMBCC (Mega Man Battle Chip
Challenge, USA, GBA) pret-style decomp project at `~/workspace/mmbcc-decomp/`.

## The ROM (READ-ONLY — never copy it, never put its bytes in any repo/report)

`~/workspace/megaman-bcc-recomp/rom/Mega_Man_-_Battle_Chip_Challenge__USA__0_8r4i.gba`

- Verify SHA-1 = `72309736f3820470c6f372d6a05ad1f16bc5a946` before you start.
  If it does not match, STOP and report.
- Do NOT disturb `~/workspace/megaman-bcc-recomp/` (the recomp track).
- No copyrighted content (ROM bytes, long disassembly listings) in reports.
  Short snippets to illustrate a diff are fine.

## Your task

For each assigned function: write C source that compiles to BYTE-IDENTICAL
bytes vs the ROM. Name each function from its behavior (tentative names OK).

**BEFORE starting any function:** `grep` its address in
`docs/match_status.tsv` — if it is MATCHED/ASM/INTERIOR/BLOCKED there, SKIP
it (a past worker claimed duplicates that were reverted). Record the skip.

## Toolchain (`~/workspace/mmbcc-decomp/mmbcc/`)

- Main: `tools/agbcc/bin/agbcc`. Per-file build rule:
  `cpp -I include file.c -o file.i`
  then `agbcc -O2 -mthumb-interwork -Wimplicit -Wparentheses -o file.s file.i`
  then `arm-none-eabi-as -mthumb -mcpu=arm7tdmi -o file.o file.s`
  NOTE: this agbcc does NOT preprocess and rejects `-I`/`-c` — always cpp first.
- Variant: `tools/agbcc/bin/old_agbcc` (pre-patched; different register
  allocation/scheduler). MANY functions only match with old_agbcc — try it
  whenever main agbcc's codegen diverges. Old_agbcc omits `push {lr}` for
  true-leaf switch functions; main agbcc emits `push {lr}...pop {r1}; bx r1`
  for ANY function with a conditional branch — branchy smalls usually need
  old_agbcc (plain `bx lr`).
- Variant: no-interwork TU — same rule WITHOUT `-mthumb-interwork`
  (for `pop {rX,pc}` epilogues and libgcc-style regions).
- Also try `-O1`/`-Os` when `-O2` diverges.

NOTE: `arm-none-eabi-*` lives in `/usr/bin` (installed from the project's
`.deb` backup); if missing mid-session, reinstall with
`sudo dpkg -i ~/workspace/mmbcc-decomp/tools/host/binutils-arm-none-eabi_2.42-1ubuntu1+23_amd64.deb`.

## Disassembly

`arm-none-eabi-objdump` is available.
Extract a ROM region:
`dd if=ROM of=workdir/f.bin bs=1 skip=$((0xADDR - 0x08000000)) count=SIZE`
then `arm-none-eabi-objdump -b binary -m arm -M force-thumb --adjust-vma=0xADDR -D workdir/f.bin`

## Reference docs (read the relevant ones)

- Newest first: `match_notes_wave24_D.md` (tail-correction, clobber-reservation
  for pool steering, r7 pin not always poison, branch inversion, true
  extents), `match_notes_wave24_coordinator.md` (strh/ldrh hand-decode,
  call-free-loop hoist → sed, live-range extension spills, rect-fill status),
  `match_notes_wave24_B.md` (extern-array pool ordering, ShiftPair wrapper
  family, volatile reloads), `match_notes_wave24_A.md` (rect-fill prologue
  allocator wall, pinned-COPY registers).
- Then: `match_notes_wave23_A.md`, `match_notes_wave23_C.md`,
  `match_notes_wave23_D.md` (script-ASM cluster), `match_notes_wave22_C.md`
  (kill-and-reload, clobber-reservation), `match_notes_wave12_B.md`
  (pinned-COPY-register trick — pin the COPY with
  `register T x __asm__("rN")`, not the primary), `match_notes_wave13_B.md`,
  `match_notes_wave14_A.md`, `match_notes_wave14_C.md`.
- `docs/match_status.tsv` — matched/blocked registry. Use REAL matched
  names for callees (check this file), not `sub_08XXXXXX` aliases.
- `docs/xrefs.tsv` — call graph (KNOWN-INCOMPLETE for some functions;
  verify callees by disassembly, not blind trust).

## Newest idioms (Waves 21-25 — read the matching notes first)

- **Clobber-reservation idiom** (w21a_3AFFC MATCHED): deny an unwanted register
  with a zero-byte volatile asm clobber while a constant pseudo is live
  (`__asm__ volatile("" : : "r"(off) : "r2")`), then a second empty volatile
  asm after the address-add keeps the pseudo live past it, killing
  dest-register coalescing.
- **Clobber-reservation for pool steering** (w24d 0x08004998): denying r7 at
  the pool load moved the pool to r1. **CATCH-22**: if the denied reg is also
  the wanted home of a live variable, the catch-22 must be broken another
  way — pinning c→r7 miscompiles per w22d.
- **Tail-correction before register work** (w24d 0x0804AF20): the "allocator
  wall" evaporated once the tail was hand-decoded correctly (objdump scales
  strh/ldrh immediates by 2; Rd was misread). Hand-decode strh/ldrh whenever
  a wall depends on it.
- **Call-free-loop invariant hoist is undefeatable in this gcc** (w24d):
  gcc hoists 0x10000 out of any call-free loop (14 -fno-* flags, all
  compilers) — go straight to Makefile sed.
- **Live-range extension spills** (w24b rect-fill): zero-byte asm at function
  end lowers gcc priority → ROM-identical spills. Root-caused in agbcc's
  local-alloc.c (QTY_CMP_PRI sort, lowest free hard reg wins). **`u8 *pa = a;`
  first-local reproduces param-spill + sl-reload exactly.**
- **Pinned-barrier generalizes to pool loads** (w20c): `"+r"` asm forces ldr
  before the strb/lsls it feeds.
- **Kill-and-reload** (w22c): load, kill the temp with volatile asm, reload
  — defeats CSE fusing.
- **Explicit u16 increment** (w22c): u32-extended increment style defeats
  the fold.
- **ASM-staging for compiler-impossible insns** (w23d: 20-fn script cluster):
  when agbcc cannot emit an insn (e.g. `tst`), hand-transcribe the whole
  function as a file-scope `__asm__` block per the wave3 Script_NextOp
  precedent.
- **Trailing-pool extents** (w21b/w22a): section extent INCLUDES the literal
  pool past nominal code size — verify against ROM bytes, not func_stats size.
- **Sub-word (u8) register pins are NOT honored** (w22d) — use u32 pins.
- **r7 pin is NOT always poison** (w24d 0x080259A4): `register u32 b7
  __asm__("r7")` worked fine there — the miscompile is context-dependent.
- **Sibling-shape transfer** (w19c/w20c): diff against a MATCHED same-size
  family member BEFORE register pinning — pinning actively harms codegen.
- **Sed on .s for scheduler-resistant edits** (w23a 02CB0): targeted sed
  (insert/delete/rename regs) is an accepted precedent; GAS recalculates
  pool offsets automatically. Makefile inline-sed must contain a single
  literal `\t` (od-verify; `\\t` in tool output is display escaping).
- **Extern-array pool ordering** (w24b Load4Tiles): `extern u32 gTbl[];
  gTbl[a]` forces pool-load-before-index-shift.
- **Pool-loaded 0xAA via absolute-symbol trick** (w24d 0x08002EF4): agbcc
  folds every pure-constant 0xAA to `movs r0,#170` — `(u32)&gAddrZero[0xAA]`
  with an absolute `.set` symbol at 0x0 forces a pool word linking to
  exactly 0xAA.
- **Try old_agbcc before fighting a 2-reg allocator rotation** (w23a 02E80).
- **GAS pre-UAL**: `add` not `adds`, `asr` not `asrs` in inline asm; use
  `.short 0x1808` for `adds r0,r1,r0` (GAS rejects Rd==Rm adds text).
- **If/else body swap fixes branch inversion** (w24d 0x08026740): when gcc
  inverts `bhi`→`bls`, swapping the if/else bodies restores ROM's branch.
- **Inline-asm prologue idiom** (w25a, adapted from w15c MaskWrite23_0804D7C0): emit
  the whole function prologue as `__asm__ volatile` blocks — params unused in C
  (suppresses `assign_parms`), `"=r"` outputs tie C vars to pinned regs,
  `"=m"` for spill slots. 0x08006AD8's 768 B prologue byte-perfect vs ROM.
- **r7-pin + clobber-reservation CAN coexist** (w25b 0x08004998 — the r7/r8
  catch-22 is BROKEN): `register u32 c7 __asm__("r7")` pin COMBINED with
  clobber-reservation denying r7 at the pool load — gcc honors both (c stays
  in r7, pool goes to r1). "Never pin r7" is context-dependent. Narrow the
  clobber's live range.
- **Inline-asm `ldrsb` mandatory** (w25d): agbcc NEVER emits ldrsb/ldrsh from C
  — verified by minimal test. Use inline asm for sign-extending byte loads.
- **Two-half s8 switch** (w25c ShiftPair family): two-half `switch` on
  `(s8)p[off]` (cases 1/3) programs EWRAM structs then calls the worker.
- **Pin+asm forced movs** (w25c): `__asm__` movs/lsl defeat value propagation.
- **`"+r"` barrier vs pool fold** (w25c): `__asm__ volatile("" : "+r"(base))`
  before address uses defeats pool folding.
- **`u32 m=2; m=-m;` for `negs`** (w25c); **u32-typed 0xFFFC pools** (w25c);
  **`~0x3C0` pools as 0xFFFFFC3F** (w25c).
- **Control-flow correction via beq-target reading** (w25b 0x08026740): ROM's
  `beq` revealed S[18]=0 is INSIDE `if (S[19]!=99)` — a worker's C was
  semantically wrong. Read beq targets before blaming codegen.
- **Thunks must link at 0x0804DCCC** for isolated `bl _call_via_rN`
  verification (w25b — 3 phantom diffs until thunks.o was placed right).
- **Pinned-COPY chain with opaque barriers** (w25b): `register u32 de
  __asm__("r0") = x; __asm__("" : "+r"(de));` forces lsls/lsrs/adds sequences
  without combiner fusion.
- **Verify pools with `od`** (w25d): byte-swap misreads (0x46B1 vs 0xB146).
- **Makefile inline-sed needs `$`→`$$` escaping** (w25c: bare `$` breaks the
  build). sed expressions use single `\t` (od-verify).

## DO NOT LAND (PROTOCOL — VIOLATIONS WILL BE REVERTED)

You STAGE ONLY. You must NEVER modify any of these:
`mmbcc/src/`, `mmbcc/Makefile`, `mmbcc/ldscript.ld`, `docs/match_status.tsv`,
`docs/PROGRESS.md`, `docs/*_layer.tsv`.

In a past wave, workers landed directly into the build — one partial landing
BROKE THE BUILD (undefined symbol: a registry name was not the real C
symbol) and risked orphan-section merge corruption of the ROM image. The
coordinator had to revert and re-land properly. Any direct landing you make
will be REVERTED on sight, no matter how good the work is. Stage in
`staging/wave26_<TAG>/`, write your results TSV + notes, and STOP.

## Verification of YOUR claims happens WITHOUT you

The coordinator independently re-verifies every MATCHED claim with its own
clean-room harness before it counts. A claim you could not verify under the
hardened protocol (below) does not count.

## VERIFICATION PROTOCOL (HARDENED — MANDATORY)

A past worker's harness had TWO bugs that made every check vacuous
(quoted section pattern matched nothing -> empty .bin; dd skip used the ROM
address instead of file offset -> empty ROM extract; `cmp` on two empty
files = false "match"). Follow this EXACTLY for every MATCHED claim:

1. Compile the C with the exact build rule above. Record compiler+flags.
2. Link a MINIMAL test at the exact address, e.g.:
   `arm-none-eabi-ld -Ttext 0xADDR --section-start .text.YOURSEC=0xADDR -o test.elf your.o`
   (add thunks.o only if you need `_call_via_rN`; the section pattern must
   be UNQUOTED: `-j .text.YOURSEC`, not `-j ".text.YOURSEC"`).
3. Extract: `arm-none-eabi-objcopy -O binary -j .text.YOURSEC test.elf test.bin`
4. ASSERT NON-EMPTY at EVERY step — print byte sizes of .o, .elf, .bin.
   If ANY is 0 bytes, your harness is broken. FIX IT. Do not claim a match.
5. ROM extract: `dd if=ROM of=rom.bin bs=1 skip=$((0xADDR - 0x08000000)) count=EXACT_SIZE`
   NOTE: skip is the FILE OFFSET (addr MINUS 0x08000000), NOT the ROM address.
   Assert rom.bin is non-empty and EXACTLY EXACT_SIZE bytes.
6. `cmp -l test.bin rom.bin` must show ZERO differences.
7. Cover the FULL section extent INCLUDING literal pools — a past "0 diffs"
   covered only code and missed byte-swapped pool constants.
   Disassemble your .bin and eyeball the instruction sequence vs the ROM.
   Verify pool constants as RAW BYTES (little-endian) before crying
   compiler-difference.

## Staging (YOU DO NOT LAND)

- Work in `~/workspace/mmbcc-decomp/staging/wave26_<TAG>/` (NOT /tmp — a VM
  /tmp wipe once lost 15 claims; your coordinator assigns TAG).
- Results: `~/workspace/mmbcc-decomp/docs/wave26_<TAG>_results.tsv`
  columns: `address\tname\tstatus\tsize_rom\tdiffs_best\tcompiler\tdecisive_idiom\tnotes`
  status = MATCHED or BLOCKED; compiler = main / old_agbcc / nointerwork /
  main+old_agbcc / asm (asm = you only do .s transcription).
- Notes: `~/workspace/mmbcc-decomp/docs/match_notes_wave26_<TAG>.md`
  per function: name, what it does, idioms used; for BLOCKED: precise
  byte-level diffs and what was tried.
- C candidates: `staging/wave26_<TAG>/*.c`, each function in its own
  `__attribute__((section("x.text.w26<TAG>_<addr>")))` section
  (e.g. `.text.w26b_08017000`). One section per function.
- **DO NOT DELETE `staging/wave26_<TAG>/` when you finish.** The coordinator
  needs your C sources for independent re-verification and landing.
  Leave the directory intact.
- Callees: matched callees -> `extern` with REAL names (from
  match_status.tsv). UNMATCHED callees -> `.set` absolute symbols in an
  `__asm__` block at END of file + `.thumb_func` marking.
  GAS rule: `.globl`/`.set` must FOLLOW the referencing code in the file.
- DO NOT modify: `mmbcc/src/`, `mmbcc/Makefile`, `mmbcc/ldscript.ld`,
  `docs/match_status.tsv`, `docs/PROGRESS.md`, `docs/wave26_layer.tsv`.
  The coordinator lands after independent re-verification.

## Status rules

- MATCHED = byte-identical compiled bytes, verified per the protocol above.
- BLOCKED = precise diff documented, all tried variants listed. Near-matches
  are NEVER counted as matched.
- If a function's premise is wrong (e.g. it calls an unmatched function,
  or it's actually interior to another function), report it as BLOCKED with
  the evidence — do not force it.
