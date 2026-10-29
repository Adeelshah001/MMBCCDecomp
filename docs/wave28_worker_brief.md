# Wave 28 Worker Brief (read this FIRST, in full)

You are a Wave 28 worker for the MMBCC matching-decomp project at `~/workspace/mmbcc-decomp/`.
Read `docs/match_notes_wave27_{A,B,C,D}.md` relevant to your assignment, plus this whole brief, before touching anything.

## Legal / hard lines
- Baserom: `~/workspace/megaman-bcc-recomp/rom/Mega_Man_-_Battle_Chip_Challenge__USA__0_8r4i.gba`
  (SHA-1 `72309736f3820470c6f372d6a05ad1f16bc5a946`, 8,388,608 bytes). **Read-only.**
  Never copy it into any repo. Never put ROM bytes or copyrighted assets in any repo or report.
- **Do not disturb `~/workspace/megaman-bcc-recomp/`** (the recomp track) in any way.
- Leave alone, no new angles: `Vec2_CopyMirrored` (permanently blocked — lone `pop {r2}`
  anomaly, proven), `Sram_VerifyCompare`, `MainLoop`, `ChipSlot_Tick`. B3 @0x080244B0 is parked
  as likely second-vintage — do not touch.

## Toolchain
- Compilers: `agbcc` (da598c1) at the project toolchain path; `old_agbcc` variant.
  **Always try old_agbcc on near-misses, even when main agbcc is close** (decisive on 0x0801b0dc: 16 vs 25 diffs).
- If `arm-none-eabi-*` vanishes from /usr/bin (recurring VM churn): reinstall immediately with
  `sudo dpkg -i ~/workspace/mmbcc-decomp/tools/host/binutils-arm-none-eabi_2.42-1ubuntu1+23_amd64.deb`
  (exact GAS 2.42 match). Do not debug "missing tool" errors — just reinstall.
- Build rules: cpp → agbcc/old_agbcc → as; per-file compiler overrides supported; no-interwork
  TU overrides for functions ending in interworking `pop {pc}` (then the stub must use `.thumb_func`).
- Makefile sed rules: escape `$` as `$$` (make eats bare `$`). Verify with `od` when in doubt.

## Verification protocol (HARDENED — no exceptions)
A function is MATCHED **only** when compiled bytes are byte-identical to baserom, verified by:
1. Recompile from scratch (exact compiler + flags) in a clean room.
2. Link the object at its TRUE ROM address. Custom `.ld` with explicit SECTIONS —
   `--section-start` alone fails (ld's default script merges `.text.*` into `.text`, producing empty extracts).
3. `objcopy` the section; assert .o/.elf/.bin/extract are ALL non-empty.
4. Extract baserom bytes at file offset = address − 0x08000000, with the EXACT byte count.
5. `cmp` your extract vs baserom extract — must be 0 diffs, including the FULL section extent
   **including trailing pools** (TRUE extent = max(code_end, max_pool_target+4); pools verified
   from ROM bytes, disasm misleads).
6. Neighbor check: confirm you didn't disturb adjacent sections.

**Sanctioned asm transcription** (dis2asm2.py: objdump Thumb → GAS file-scope `__asm__`,
branch targets → local labels, `bl` → symbols via `.set`) is allowed ONLY after C variants are
exhausted and documented, and must be noted as such.

## Registry rules
- `docs/match_status.tsv` is **append-only**. Check it BEFORE claiming anything (duplicates get reverted).
- Report claims to the coordinator with: address, function name, size, compiler variant,
  0-diff evidence. The coordinator writes registry rows and lands; you do not.
- Blocked attempts get `docs/match_notes_wave28_<worker>.md` entries with precise diffs/walls.

## Landing rule
**DO NOT LAND.** Stage all matched sources + build evidence in `staging/wave28_<X>/`.
NEVER write into `mmbcc/src/`, never edit `ldscript.ld`, never touch the Makefile.
Never delete staging. Workdir must be workspace-based (`staging/wave28_<X>/`), never `/tmp` (VM wipes it).

## Idiom catalog (abbreviated — full details in match notes)
- Pin-the-thief: to fix a high-reg rotation, pin ONLY the variable stealing the wrong reg
  (`register int mask __asm__("r9")`), not the ones you want placed. But do NOT clobber a pinned
  reg (miscompile). Any `register __asm__("r7")` pin — even block-scoped — marks r7 fixed
  function-wide and breaks gcc's prologue.
- Clobber-reservation: deny an unwanted register with a zero-byte volatile asm clobber
  instead of pinning (`__asm__ volatile("" : : "r"(off) : "r2")`).
- Scoped register-denial, early-zero materialization, split-shift interleave via dual empty-asm
  barriers, deferred-zero variable, goto-to-late-label, goto store6 tail-sharing, two-step ldrh.
- Pool-control: agbcc dumps the literal pool after the first unconditional jump past the last
  literal use — steer placement by restructuring branches. Pure constants always fold;
  pool-loaded 0xAA needs `(u32)&gAddrZero[0xAA]` with absolute symbol at 0x0. gcc's call-free-loop
  invariant hoist is undefeatable → sed.
- Sibling-shape transfer: diff against a matched family member before pinning (pinning often harms).
- `"m"`-constraint dummy forces a stack slot with ZERO emitted instructions;
  explicit `u32 stk[N]` frame array guarantees slot order.
- `s16` extern params force `ldrsh` for s16 locals passed to it (same ABI; coordinator restores
  u16 signature at landing). Natural `ldrsh` from C works for `s16 v = tbl[i]`; agbcc never
  emits `ldrsb` from C — inline-asm it.
- Bl-target discipline: for multiply-instantiated helpers (Byte12_Gt1 exists at 6 addresses),
  decode the ROM's `bl` target and stub THAT copy.
- try old_agbcc before fighting 2-reg allocator rotation; single-expression `v=(*p&m)|k`
  for load order; kill-and-reload; explicit u16 increment; `((u32)s[35]<<28)>>28` shift-mask
  for &15; split-&= anti-fold; opaque `+r` barrier forces runtime negs; `u8 *pa = a;` first-local;
  live-range extension spills; non-void-no-return → `pop {r1}` epilogue; mid-function pool via
  `.short` nop; never `sort -u` on relocs (destroys order); nm hygiene must confirm GLOBAL (A/T).

## Your assignments
- **Worker A — BlendCopy twins** 0x080224E4 / 0x08021B3C (206 B, 104 diffs, BLOCKED).
  Wave 27-C solved the high-reg rotation via pin-the-thief (`register int mask __asm__("r9")` →
  srcA→r8, srcB→ip, ROM-exact). Best source staged in `staging/wave27_C/`.
  Remaining wall: systematic LOW-reg r3↔r4 swap in the loop body. Read the wall section of
  `docs/match_notes_wave27_C.md` carefully (r3↔r4: av→r3 vs ROM r4; mask-copy rematerialization;
  loop-top copy `mov r7,ip` vs `mov r2,ip`; mask init temp `movs r2,#31` vs `movs r0,#31`;
  c0 finalize placement; prologue `adds r1,r0,r1` vs `adds r0,r0,r1`).
  Attack the r3↔r4 swap with the idiom catalog (pin-the-thief on the low-reg thief, scoped
  register-denial, dead-register reuse via pin + reassign). Twins are identical except the
  `bl Memcpy16` encoding — match one, transfer.
- **Worker B — near-miss closers:** 0x0801b0dc (208 B, 16 diffs — old_agbcc decisive per
  wave27-C notes; switch cases 0-2 match ROM), 0x0803643c (444 B, 60 diffs — 3 hoisted 0x10000
  constants; `.s` sed patch staged at `staging/wave27_B/w27b_0803643c_patch.py`; needs C-level
  pin work for cnt→r5 per wave27-B notes), 0x0801c428 (278 B, 177 diffs — call-1 `ldrsh` dest
  r2 vs ROM r3; try the s16-extern-params adjudication idiom).
- **Worker C — 0x0801f254 sibling family:** 0x0801f254 (164 B, 8 size diffs, v/c allocation wall
  per wave27-B notes; staging in `staging/wave27_B/v_0801f254/`), 0x0802375c (198 B, UNTRIED),
  0x0802298c (220 B, UNTRIED). One shared allocation wall — crack 0x0801f254, transfer to the
  siblings via sibling-shape transfer.
- **Worker D — bulk + revisits:** the 10 UNTRIED rows in `docs/wave27_layer.tsv`
  (0x0802d6e0 192 B jump-table switch; 0x08002a1c 210 B contains ldrsb → inline asm;
  0x080046b0 238 B complex gfx/CpuFastSet/high-reg pressure; 0x0803ac4c 238 B multiple branches;
  0x0801e77c 254 B switch on p[14]/stack args; 0x080096bc 260 B tile-copy loop 5 params;
  0x08006fe8 264 B 6 params GetPtr family; 0x08024a30 268 B 11 callees) plus blocked revisits
  with fresh idioms: 0x0801c030 (214 B, 60 diffs — try `vv = sp[19]` reuse idiom from wave27-C),
  0x08049560 (278 B — gcc DSE kills `local=0` before pool-constant overwrite; `volatile` forces
  it but adds 48 B — find a cheaper way).

Report to the coordinator when done: matched list with evidence, blocked with precise walls,
new idioms, what you staged. Do not land. Do not ask the user for anything — if you hit a
decision needing the user, state it in your report and pause that part.
