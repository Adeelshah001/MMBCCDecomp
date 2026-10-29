# Wave 6 batch L1 match notes (worker, 2026-10-20)

Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` (read in
place, never copied). Toolchain: `mmbcc/tools/agbcc/bin/agbcc` (main) /
`old_agbcc`. Build rule (exact): `cpp -I mmbcc/include <src>.c -o <x>.i &&
agbcc -O2 -mthumb-interwork -Wimplicit -Wparentheses -o <x>.s <x>.i &&
arm-none-eabi-as -mthumb -mcpu=arm7tdmi -o <x>.o <x>.s`.
Verification: link section at ROM address, objcopy --only-section, byte-diff
vs baserom; Thumb `bl` to absolute `.set` symbols patched post-link (the
minimal harness linker inserts ARM veneers for absolute symbols — harness
artifact, not a source problem; coordinator must verify bls in full build).
Scratch: `/tmp/wave6_l1/` (formulations saved as `*_MATCHED.c`).

Result: 1 MATCHED, 10 BLOCKED (with structural analysis).

## MATCHED (1)

### Task_38AD4 @ 0x08038AD4 — MATCHED (0 diffs, old_agbcc, 316 B footprint)

**Formulation** (`/tmp/wave6_l1/Task_38AD4_08038AD4_MATCHED.c`):
- **Compiler: old_agbcc**. Main agbcc swaps r1/r3 in the ladder.
- **Register pinning for ladder**: `register u16 *g __asm__("r1")` and
  `register u16 w1 __asm__("r3")` force ROM's allocation (g=r1, w1=r3).
  Without pinning, compiler uses r3/r1 (swapped).
- **Branchless bit-select**: `v = (w2 & 0x40) ? 0x40 : 0;` (u8 v) emits
  `lsls#16; lsrs#16; negs; asrs#31; ands` (exact ROM sequence). The
  `(u16)` truncation via the ternary is load-bearing; the `!= 0` form
  gives lsl/lsr instead.
- **Operand order**: `(0x40 & w1)` (constant first) emits
  `adds r0, r2, #0; ands r0, r3` (ROM); `(w1 & 0x40)` gives
  `add r0, r1, #0; and r0, r0, r2` (swapped).
- **Explicit w1 reloads**: `w1 = g[0];` before the 1-test and 2-test
  reproduces ROM's 3 loads of g[0] (compiler CSEs the 0x80-test reuse
  but respects the explicit re-assignments).
- **Case layout order**: switch cases in source order 0x40, 0x80, 1, 2
  (compiler emits in source order; ROM has 0x40@0x8038b5e, 0x80@0x8038b78,
  1@0x8038bb0, 2@0x8038be4).
- **Mid-block zero**: `u8 z; ... { u8 *addr = p + 0x469c; z = 0; *addr = v; }`
  gets `movs r1,#0` between `adds` and `strb` (ROM scheduling).
- **Source-first evaluation**: `{ u8 t = p[0x4698]; p[0x4699] = t; }`
  forces the load before the store (compiler otherwise does dest-first).
- **Goto-form lim**: explicit gotos force the `bls` chain for the
  clamp (`if (x <= 8) goto t1; lim=3; ...`).
- **Epilogue base is 0x02004CE0** (not 0x02002F50): the ladder uses
  0x02002F50, the epilogue writes to 0x02004CE0+0x28/0x2A. Pool at
  0x08038c08 has 0x02004CE0.
- **Footprint**: 306 B code + 2 B `00 00` pad + 8 B pool (0x02004CE0,
  0x4698) = 316 B to next function at 0x08038C10. The wave6_layer.tsv
  size (306) is code-only.

**Behavior**: Bit-test priority ladder on `*(u16*)0x02002F50` /
`*(u16*)0x02002F56` / `*(u16*)0x02002F54` (r4 = 0/0x40/0x80/1/2, last
match wins); dispatches via Text_SelectBlobIdx(0x66/0x67/0x68);
manipulates `p[0x4698]` (counter) and `p[0x469C..0x469D]`; sets up
EWRAM 0x02004CE0 (`*(u16*)(+0x28)=0x14`, `*(u16*)(+0x2A)=(p[0x4698]<<4)+8`);
returns 0-3 in r0.

**Landing notes**:
- Needs old_agbcc Makefile override.
- Section is 316 B (code+pad+pool); next function at 0x08038C10.
- The `bl Text_SelectBlobIdx` must be verified in the full build
  (harness patched the veneer-artifact bl).
- Externs: `Text_SelectBlobIdx` (0x0804A378), `gEwram_02002F50`
  (0x02002F50), `gEwram_02004CE0` (0x02004CE0).

## BLOCKED (with analysis)

### sub_08002300 @ 0x08002300 — Decompression dispatcher (BLOCKED, regalloc)

330 B. Decompresses graphics chunks to VRAM based on flags in `p[10]` /
`p[11]`. Three loops (LZ77, RL, CpuFastSet) + single-call tail.

**Blocker**: Whole-function register allocation.
- ROM: p=r5, dst=r6, t=r4, rem=r7, cnt=r2 (path-sensitive, survives
  on noflag1 path).
- Best attempt: p=r5, dst=r7, t=r4, rem=r6, cnt=r2 (pinned).
- The dst/rem swap (r6/r7) could not be fixed; pinning breaks the
  prologue. The cnt-in-r2 requires path-sensitive liveness the
  compiler won't do.
- 202 diffs in best attempt (`/tmp/wave6_l1/t2300_d.c`).

**Structure** (for future work):
- `cnt = (*(u32*)(p+4) << 10) >> 10`; if 0 return.
- `dst += ((0x7F8 & *(u16*)(p+10)) * (*(u16*)(p+6) >> 6))`.
- If `p[10] & 1`: `t = p + *(u32*)p`, `rem = cnt`; dispatch on
  `p[10] & 2` (LZ77 loop) vs `p[11] & 16` (RL loop) vs copy loop.
- Loops: if `*(s32*)t < 0` decompress via LZ77/RL (`t+4` to
  `dst+0x06000000`), else CpuFastSet (`t+4`, size `*(u16*)(p+8)>>2`);
  `dst += (((*(u16*)(p+10) << 21) >> 24) << 8)`; `step = *t & 0x7FFF7FFF`
  (pool); `rem -= step; t += step`.
- Single-call tail: LZ77/RL with `t` (not `t+4`), or CpuFastSet with
  `cnt >> 2`.

### sub_08002070 @ 0x08002070 — SRAM read state machine (BLOCKED)

340 B. Chunked SRAM read with magic check and checksum verification.

**Blocker**: Switch case-body scheduling diverges (208 diffs best attempt).
The retry-countdown `(u16)` wraparound and pool layout need work.

**Structure**:
- Switch on `p[3]` (0-3, compare tree).
- Case 0: `*(p+4)=3; *(p+6)=p[3]; p[3]=1` → fallthrough.
- Case 1: SRAM addr = `0x0E000000 + ((p[1] + 2*(*(u16*)(p+6))) << 13)`;
  `Sram_WaitcntInit(0x02000808, 0x02000808, 16)` (WAITCNT setup);
  if `*(0x02000808) != *(0x0804E314)`: retry countdown; else
  `*(p+16) += 16; p[3] = 2`.
- Case 2: chunked read via `Sram_WaitcntInit(*(p+16), *(p+12), len)`;
  `len = min(rem, 0x820)`; advance pointers.
- Case 3: checksum loop (subtract bytes from `*(0x0200080C)`);
  on failure retry or set error flag at `0x02002F80+30`.

### sub_08001F1C @ 0x08001F1C — SRAM write state machine (BLOCKED, not attempted)

340 B (334 code + 2 pad + 4 pool). SRAM write with header + checksum.

**Structure** (decoded, not attempted):
- Switch on `p[3]` (0-3).
- Case 1: builds 16-byte header on stack (magic, checksum, count,
  flags), writes via `Sram_RetryWrapper(sp, sram_addr, 16)`.
- Case 2: chunked write via `Sram_RetryWrapper`.
- Case 3: completion/error handling.
- Pool at 0x080206C (0x02002F80) after `00 00` pad.

### sub_0803AAA8 @ 0x0803AAA8 — Bit-ladder variant (BLOCKED, not attempted)

412 B. Similar family to Task_38AD4 but more complex:
- Prologue uses r7 (push {r4-r7,lr}).
- Ladder uses `*(g+4)` for 1/2 tests (clobbers g).
- 6-case dispatch with bne/b (not beq).
- case_80 has `ldrsb` and multi-pool logic (~100 B).

### EntryMgr dispatchers — BLOCKED (batch-F class, xref DB incomplete)

All four are task mode-dispatchers calling EntryMgr_Teardown/Setup around
a switch. **Critical finding**: the xref DB (`docs/xrefs.tsv`) is
incomplete — it lists only 2 bls for 0x08036A14, but the disassembly shows
8+ bls to unmatched helpers. The wave6_layer.tsv "all bl-callees matched"
claim is based on this incomplete data.

- **0x08036A14** (402 B): 6-case switch on `p[5]`; calls `sub_08037600`,
  `Text_SelectBlobIdx`, `sub_0800B308`, + 5 more unmatched.
- **0x08036DAC** (386 B): 12-case switch on `p[5]`; calls `sub_080400A8`,
  `sub_0804DEE8`, `sub_0800B368`, `sub_0800B308`, `sub_080247C4`, + more.
- **0x08039058** (370 B): 5-case switch; calls `sub_08004E44`,
  `sub_08004DFC`, `sub_08005A9C`, `sub_0800BEE0`, `sub_0803A6BC`,
  `sub_0800800C`, `sub_0800B148`, `sub_0800B2D8`, `sub_0800B368`,
  `sub_0803AAA8` (itself unmatched).
- **0x080493EC** (364 B): 5-case switch; calls `sub_0800BEE0`,
  `sub_08005A9C`, `sub_08049560`, `sub_0800800C`, `sub_0804A3FC`,
  `sub_0804A40C`, + more.
- **0x0803643C** (438 B): 3-arg function with hi-reg allocation
  (r8/r9/sl/ip); calls `SelBlob_Ret` (matched) + unmatched helpers.

These need their callees matched first (per wave4_f recommendation),
plus the whole-function regalloc problem.

### sub_0803EEA8 @ 0x0803EEA8 — Large dispatcher (BLOCKED, documented)

1428 B. Task mode-dispatcher, 6-case switch on mode byte at `p+off`
(where off is pool-loaded, ~0x803EED8). Prologue: `push {r4-r7,lr}` +
push r8; `r6=p`, `r8=ret=0`, `r4=0`. Calls `GetEnt_U16_22` (matched),
`EntryMgr_Teardown`/`Setup` (matched), plus 15+ unmatched helpers
(`sub_0800BEE0`, `sub_08005A9C`, `sub_0800800C`, `sub_0803EA1C`,
`sub_080241F8`, `sub_08024514`, `sub_0800B148`, `sub_08024384`, ...).
Epilogue at 0x0803F42C: `bl EntryMgr_Setup`, restore r8, pop, bx.
Batch-F class; needs callees matched first.

## New idioms discovered

1. **old_agbcc for r1/r3 (not just r0/r1)**: When main agbcc swaps r1/r3
   in a ladder sequence, old_agbcc may have the reference allocation.
   (Task_38AD4 ladder.)

2. **Register pinning for specific regs**: `register u16 *g __asm__("r1")`
   forces g into r1. Use sparingly; pinning caller-saved regs is safe
   only if the variable is not live across calls.

3. **Branchless ternary form**: `v = (w2 & 0x40) ? 0x40 : 0;` (not
   `!= 0` form) gives the `negs; asrs#31; ands` sequence. The exact
   ternary shape matters.

4. **Constant-first operand order**: `(0x40 & w1)` vs `(w1 & 0x40)`
   swaps the `adds`/`ands` operand order. Write the constant first to
   match ROM's `adds r0, r2, #0; ands r0, r3`.

5. **Harness bl patching**: The minimal-harness linker inserts ARM
   veneers for absolute `.set` symbols. Patch the `bl` bytes post-link
   via computed Thumb-2 encoding; coordinator verifies in full build.
   (See `/tmp/wave6_l1/patchbl.py`.)

6. **True footprint vs code size**: wave6_layer.tsv sizes are code-only;
   the ROM footprint includes `00 00` pad + literal pool. Always verify
   against the full footprint to next function.

7. **xref DB incompleteness**: `docs/xrefs.tsv` misses many bl entries
   (e.g., 2/8+ for 0x08036A14). Do not trust "all callees matched"
   claims without disassembly verification.

## Files for coordinator

- `/tmp/wave6_l1/Task_38AD4_08038AD4_MATCHED.c` — 0 diffs (old_agbcc,
  316 B footprint)
- `docs/wave6_l1_results.tsv` — summary table
- `docs/match_notes_wave6_l1.md` — this file

**Landing notes**:
- Task_38AD4: needs old_agbcc Makefile override. Section is 316 B
  (`.text.w6_38ad4`); place at 0x08038AD4; next function at 0x08038C10.
  Verify the `bl Text_SelectBlobIdx` in the full build (harness used
  post-link patching). Externs: Text_SelectBlobIdx, gEwram_02002F50,
  gEwram_02004CE0 (new symbol, 0x02004CE0).
- The 10 BLOCKED functions need callee matching first (especially the
  EntryMgr dispatchers) or are blocked on whole-function regalloc.
