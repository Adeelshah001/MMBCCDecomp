# Wave 8 Worker Brief (READ FIRST)

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

## Toolchain (`~/workspace/mmbcc-decomp/mmbcc/`)

- Main: `tools/agbcc/bin/agbcc`. Per-file build rule:
  `cpp -I include file.c -o file.i`
  then `agbcc -O2 -mthumb-interwork -Wimplicit -Wparentheses -o file.s file.i`
  then `arm-none-eabi-as -mthumb -mcpu=arm7tdmi -o file.o file.s`
  NOTE: this agbcc does NOT preprocess and rejects `-I`/`-c` — always cpp first.
- Variant: `tools/agbcc/bin/old_agbcc` (pre-patched; different register
  allocation/scheduler). MANY functions only match with old_agbcc — try it
  whenever main agbcc's codegen diverges.
- Variant: no-interwork TU — same rule WITHOUT `-mthumb-interwork`
  (for `pop {rX,pc}` epilogues and libgcc-style regions).
- Also try `-O1`/`-Os` when `-O2` diverges.

## Disassembly

`arm-none-eabi-objdump` is available (no capstone here).
Extract a ROM region:
`dd if=ROM of=~/workspace/mmbcc-decomp/staging/wave8_<TAG>/f.bin bs=1 skip=$((0xADDR - 0x08000000)) count=SIZE`
then `arm-none-eabi-objdump -b binary -m arm -M force-thumb --adjust-vma=0xADDR -D ~/workspace/mmbcc-decomp/staging/wave8_<TAG>/f.bin`

## Reference docs (read the relevant ones)

- `docs/match_notes_wave6_l4.md`, `match_notes_wave6_l3.md`,
  `match_notes_wave6_blkB.md`, `match_notes_wave6_blkA.md`,
  `match_notes_wave6_l2.md`, `match_notes_wave5_blk.md`,
  `match_notes_wave2.md` — accumulated matching idioms.
- `docs/match_status.tsv` — matched/blocked registry. Use REAL matched
  names for callees (check this file), not `sub_08XXXXXX` aliases.
- `docs/xrefs.tsv` — call graph (KNOWN-INCOMPLETE for some functions;
  verify callees by disassembly, not blind trust).

## Matching idioms (apply these; extend the notes when you find new ones)

- old_agbcc for: dispatcher shapes (index kept in r3, `bl _call_via_r1`),
  instruction ORDER differences (movs-before-ldrb), scheduler differences.
- Pinned registers: `register u32 idx __asm__("r1")` + opaque inline asm
  (`__asm__("movs %0,%1" : "=r"(c) : "r"(x))`) to defeat the allocator.
  The ObjInit `ands` dest-reg family key: pinned r1 idx + opaque movs/and
  asm + late `mask=-13` to defeat scheduler hoist.
- Opaque OR-constants: force constants via asm so the compiler can't fold
  (`movs #16` via asm; opaque movs+negate for fresh `-0x3f`; `m&=-4`, `m|=1`).
- Split-adds anti-folding: `p=base; p+=0x167;` not `p=base+0x167`.
- `(baseReg -= const)` anti-constant-folding.
- `asm volatile("" : "+r"(x))` barriers to block CSE/reordering.
- `s32 v=(s8)expr` forces lsls+asrs sign extension.
- `((u32)v<<22)>>28` for `(v>>6)&0xf`.
- Absolute-base-to-local: copy an absolute base to a local before indexing
  (the assembler folds `g+const` into the pool word, killing indexed addressing).
- Two-statement base defeats nested address folding.
- Extern absolute symbols for ROM addresses: `extern u8 gName[];` plus
  `.set gName, 0x08XXXXXX` in an `__asm__` block at the END of the file
  (GAS 2.42 `.set` ordering rule: `.set` must FOLLOW the referencing code,
  or `R_ARM_THM_CALL` mis-binds to a synthetic LOCAL `*ABS*` symbol).
- `.thumb_func` for unmatched absolute callees (direct `bl`, no ARM veneer).
- No-interwork `pop {rX,pc}` epilogues need no-interwork TUs.
- GAS 2.42 pre-UAL mnemonics in inline asm: `add` not `adds`,
  `neg Rd,Rn` for rsbs #0, no `#` on branch targets.
- Inter-function gaps are `00 00` (not `c0 46`); if the linker pads with
  `c0 46`, emit an explicit zero (`static const u16 pad = 0;`) in the section.
- Byte-match beats signature purity: wider decls (u32 not u16) when the
  ROM's codegen demands it.
- `ldscript` `BYTE()` for pad-less tiny fragments.
- `goto`-`beq` for tiny switch chains; `if (x==0) goto L0;` for cmp;beq dispatch.
- `int mask=-7` (not `~6`) for movs+rsbs negation.

## VERIFICATION PROTOCOL (HARDENED — MANDATORY)

A previous worker's harness had TWO bugs that made every check vacuous
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
7. Cover the FULL section extent INCLUDING literal pools — a previous
   "0 diffs" covered only code and missed byte-swapped pool constants.
   Disassemble your .bin and eyeball the instruction sequence vs the ROM.

## Staging (YOU DO NOT LAND)

- Work in `~/workspace/mmbcc-decomp/staging/wave8_<TAG>/` (your coordinator assigns TAG).
- Results: `~/workspace/mmbcc-decomp/docs/wave8_<TAG>_results.tsv`
  columns: `name\taddress\tsize\tstatus\tcompiler\tnotes`
  status = MATCHED or BLOCKED; compiler = main / old_agbcc / nointerwork.
- Notes: `~/workspace/mmbcc-decomp/docs/match_notes_wave8_<TAG>.md`
  per function: name, what it does, idioms used; for BLOCKED: precise
  byte-level diffs and what was tried.
- C candidates: `~/workspace/mmbcc-decomp/staging/wave8_<TAG>/*.c`, each function in its own
  `__attribute__((section(".text.w8<TAG>_<addr>")))` section
  (e.g. `.text.w8s_0803f480`). One section per function.
- **DO NOT DELETE `~/workspace/mmbcc-decomp/staging/wave8_<TAG>/` when you finish.** The coordinator
  needs your C sources for independent re-verification and landing.
  Leave the directory intact; it is cleaned up after landing.
- Callees: matched callees -> `extern` with REAL names (from
  match_status.tsv). UNMATCHED callees -> `.set` absolute symbols in an
  `__asm__` block at END of file + `.thumb_func` marking.
- DO NOT modify: `mmbcc/src/`, `mmbcc/Makefile`, `mmbcc/ldscript.ld`,
  `docs/match_status.tsv`, `docs/PROGRESS.md`. The coordinator lands
  after independent re-verification.

## Status rules

- MATCHED = byte-identical compiled bytes, verified per the protocol above.
- BLOCKED = precise diff documented, all tried variants listed. Near-matches
  are NEVER counted as matched.
- If a function's premise is wrong (e.g. it calls an unmatched function,
  or it's actually interior to another function), report it as BLOCKED with
  the evidence — do not force it.
