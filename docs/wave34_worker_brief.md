# Wave 34 Worker Brief (read first)

## Project
`~/workspace/mmbcc-decomp/` — pret-style matching decomp of Mega Man Battle Chip Challenge (USA, GBA). Baserom: `~/workspace/megaman-bcc-recomp/rom/` (READ-ONLY, never copy into repos). Target SHA-1: `72309736f3820470c6f372d6a05ad1f16bc5a946`.

## Toolchain
- C compiler: `agbcc` + `old_agbcc` (project-built; see Makefile for exact flags). NEVER `arm-none-eabi-gcc` for codegen (it's only for objdump/readelf/objcopy/nm/as/ld in the verify harness).
- `arm-none-eabi-*` tools must exist in /usr/bin. If missing, reinstall: `sudo dpkg -i ~/workspace/mmbcc-decomp/tools/host/binutils-arm-none-eabi_2.42-1ubuntu1+23_amd64.deb` (exact GAS 2.42).
- You CANNOT spawn subagents (depth 2/2). Do all your work yourself, sequentially.

## Verification protocol (hardened — follow exactly for every match claim)
1. Non-empty assertions at every step: `.o`, `.elf`, `.bin`, ROM extract all non-empty.
2. Correct file offset: `addr - 0x08000000`.
3. Exact byte counts; full section extents INCLUDING pools.
4. Verify against the TRUE extent = neighbor function's start address (from func_list/registry), NEVER a self-measured window. A "0-diff" on a short window is a false match (Wave 31 lesson).
5. Isolated clean-room build: compile the single file with the exact compiler+flags, link at the TRUE ROM address with a custom `.ld` (never rely on `--section-start` alone — ld merges `.text.*`; use explicit SECTIONS), thunks linked at ROM address 0x0804DCCC, objcopy, `cmp` vs baserom bytes.
6. Verify pools from ROM bytes, not the disassembly (disasm misleads).
7. For multiply-instantiated callees, decode the ROM's `bl` target and stub the right copy (Byte12_Gt1 exists at 6 addresses).

## Registry (append-only)
- `docs/match_status.tsv` — BEFORE any claim, scan ALL rows for the address (not just the first hit; duplicates get REVERTED). Check for MATCHED/BLOCKED/INTERIOR/ASM/UNMATCHED.
- Append your own rows; never edit or delete existing rows. A retraction is a REVERTED row, never a deletion.
- Landings are the coordinator's job. You STAGE your verified sources in `staging/wave34_<letter>/` and never touch `mmbcc/src/`, the Makefile, or ldscript.ld.

## Writing matched C
- Try `old_agbcc` before fighting a 2-register allocator rotation. Try no-interwork variants when codegen diverges.
- Sanctioned asm transcription (dis2asm2.py: objdump Thumb → GAS file-scope `__asm__`, branch targets → local labels, `bl` → symbols via `.set`) is sanctioned ONLY after 5+ C variants exhausted — document the attempts.
- If you land a `.s` sed / python post-process step, stage the script in staging/ and document the Makefile rule text exactly.

## Idiom catalog (latest, apply first)
`docs/match_notes_wave33_*.md`, `match_notes_wave32_*.md`, `match_notes_wave31_*.md` — read the ones relevant to your task. Key recent ones:
- pool-const pin: block-scoped `register T v __asm__("rN") = CONST;` forces the literal-pool destination register (must initialize at declaration).
- pin-the-thief: pin ONLY the variable stealing the wrong register.
- block-scoped pin defeats the "thief"; triple block-scoped pin for temp rotation; block-scoped r3/r4/r6 pins safe; do NOT clobber a pinned reg; never pin r7 (context-dependent — verify prologue bytes).
- clobber-reservation: `__asm__ volatile("" : : "r"(v) : "rN")` denies rN without recoloring; clobber-only asms defeat folds.
- volatile-store DSE defeat: `*(volatile u16 *)&local = 0`; volatile `"+r"` barrier defeats combiner mask-folding and forces explicit truncation.
- pool-barrier mechanism: gcc dumps the literal pool at the first BARRIER after the first constant load — predicts mid/end-pool layout.
- trailing-pool extent correction: TRUE extent = max(code_end, max_pool_target+4) with fixpoint-drop of phantom refs.
- `"m"`-constraint dummy forces a stack slot with ZERO emitted instructions; explicit `u32 stk[N]` frame array guarantees slot order.
- `"r10"` and `"sl"` BOTH map to reg 10 (use `"ip"` for r12).
- pin-activation via `__asm__ volatile("" : "=r"(var))`; pin initializer rule (memory-load honored, const/arg ignored); u32 for pool constants (u16 sign-extends).
- s32 laundering for sign-extension-sensitive params/asm outputs; `s32 v=(u8)a0` for signed branches on masked values.
- inline-asm ldrsb (agbcc never emits ldrsb/ldrsh from C).
- tail-inside-if (re-read the beq target); declaration order = emission order; `&gAddrZero[const]` vs raw `(u32)const` scheduling.
- Sanctioned asm transcription: only after C variants exhausted (5+ variant bar); rebase dis2asm2.py labels to ROM addresses.

## Landing hygiene (for your staged files, so the coordinator can land them clean)
- `.thumb_func` for unmatched absolute callees; `.set` data-address symbols OK; never `.globl` a symbol that is a real build T/A symbol (nm-check GLOBAL).
- No empty `__asm__()` externals blocks (agbcc syntax error).
- File content must be drop-in ready: section name convention `.text.<name>` handled by coordinator.

## Deliverable
Your final report: verified list (address, name, bytes, compiler, diffs=0), blocked list with precise diffs + next angle, new idioms, staging paths, registry rows appended. Write `docs/match_notes_wave34_<letter>.md` with the full log.
