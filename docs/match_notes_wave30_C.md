# Wave 30-C Match Notes (Worker C)

Worker C, 2026-10-24. Staging: `staging/wave30_C/` (C sources v1-v11, v30.sh harness).
Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` before starting.

Registry check: 0x080046B0 NOT-IN-REGISTRY (confirmed via grep, count 0). No skips.

## MATCHED (1, via sanctioned transcription)

### 0x080046B0 — SpriteTileUpload_080046B0 (244 B, 0 diffs) ✅

**Method: sanctioned asm transcription** (dis2asm2.py + hand-fixed pools).
Staged: `staging/wave30_C/c_080046b0_final.c`.

**True extent:** 244 B (0x080046B0–0x080047A4): 130 B code + 2 pad + 20 B mid-pool
(0x02003250, 0x0804E33C, 0x00007FFF, 0x020031E4, 0x0000FFF0) + 86 B code
(alt path + loop bottom + epilogue) + 2 pad + 4 B end pool (0x00007FF0).

**Evidence:** `./v30.sh 0x080046B0 244 .text.w30c_080046b0 c_080046b0_final.c main
"..."` → `sizes: o=1096 elf=2500 bin=244`, `rom extract: 244 bytes`, `diffs: 0`.
Re-ran → deterministic 0 diffs. Bl targets: 2× 0x0804DB24 (CpuFastSet veneer).

**Behavior:** Walks sprite-node linked list at `*(Tbl8**)0x02003250[129]`
(node = {next+0, f4+4, f6+6}). For nodes with `f6 & 0x8000`: clears the flag
(`f6 &= 0x7FFF`), computes VRAM page base from `(*(u16*)0x020031E4 & 12) << 12`
plus `0x06000000` (via `192<<19`), then:
- If `f4 <= 0x8000`: two `CpuFastSet(src, dst, 8)` calls (src from
  `0x0804E33C`-based tile table, dst to VRAM).
- If `f4 > 0x8000`: manual ldm/stm copy loops (8 words ×2, `v<<2` pixel scaling,
  `src+=480` between rows).

Named `SpriteTileUpload_080046B0` from behavior.

## REWRITE-vs-TRANSCRIPTION DECISION

**Tried 11 C rewrite variants (v1-v11), best reached 14 diffs (v10).**
The remaining walls are fundamental register-allocation mismatches that
agbcc/old_agbcc will not produce from C constructs:

1. **vram block (5 bytes):** ROM `ldr r1,[pc]; movs r0,#12; ldrh r1,[r1]` —
   requires pool-load to r1 AND movs to r0 with ldr emitted first. gcc
   allocates first-defined→r0, and scheduler preserves C order. Tried:
   p-first/k-second (ldr-first ✓, p→r0 ✗), k-first/p-second (movs-first ✗),
   u16 k (broke size), inline asm (r3 allocation + clobber toxicity).
   **Wall holds.**

2. **alt src/dst (9 bytes):** ROM `adds r1,r0,r7` (src→r1), `adds r3,r6,r0`
   (dst→r3), `ldmia r1!`, `stmia r3!`. gcc gives src→r3, dst→r1. Tried:
   declaration swap, assignment swap, asm shifts (fixed dst computation but
   not regs). **Wall holds.**

3. **r7-pin miscompile:** `register u8 *r7v __asm__("r7")` causes gcc to SKIP
   saving r7 in prologue (confirmed: v4 prologue missed r7). Fix: leave r7v
   unpinned; gcc allocates it to r7 naturally AND saves it correctly.
   (Matches "explicit register variables excluded from GCC 2.9 save-set"
   finding.)

**Decision:** Sanctioned transcription justified. The 230/244 bytes matched via
C prove the structure is understood; the 14 bytes are allocator walls.

## C REWRITE PROGRESS (for the record)

v1 (unpinned, main): 230 diffs, 252 B. Pool split worked!
v2 (+r8/r7/r9 pins): prologue fixed, 229 diffs.
v3 (k-reuse): vram→r6 fixed, but r7 miscompile.
v4 (t0 asm, k-first): t0 fixed, vram order wrong.
v5 (r7v unpinned): **38 diffs, 244 B** — prologue correct!
v6 (vram asm): 39 diffs — asm clobbers toxic.
v7 (dst temps): 20 diffs.
v8 (swaps): 29 diffs — regressed.
v9 (asm shifts): 16 diffs — dst1/dst2 fixed!
v10 (alt dst asm): **14 diffs** — best C.
v11 (u16 k): broke size (236 B).

## KEY FINDING: Pool-barrier mechanism (major!)

**gcc's `thumb_reorg` dumps the constant pool at the first BARRIER after the
first "broken move"** (see `tools/agbcc/gcc/thumb.c`: `find_barrier()`).
Barriers occur after unconditional jumps and returns.

This EXPLAINS the ROM's mid-pool + end-pool layout:
- First broken move: `ldr r0,[pc]` (0x02003250) at 0x80046B0.
- First barrier: after `b.n` at 0x8004730 (end of main path).
- → Mid-pool dumped here with 5 literals (in first-use order).
- Next broken move: `ldr r0,[pc]` (0x7FF0) at 0x8004748 (alt path).
- Next barrier: after `bx r0` (return).
- → End pool with 0x7FF0.

**Implication:** The pool split is DETERMINISTIC given the block structure
(main path → `b.n` → alt path). My C rewrite reproduced it exactly via the
goto-structure. This is a powerful predictor for other functions with
mid-pools!

## New idioms discovered

1. **Pool-barrier dump:** `thumb_reorg`/`find_barrier` — pool dumped at first
   barrier (unconditional jump/return) after first constant load. Predicts
   mid-pool placement from CFG.
2. **r7-pin save bug:** Pinned `__asm__("r7")` locals are NOT saved/restored
   by gcc 2.9 (excluded from save-set). Leave r7 unpinned; gcc allocates
   naturally and saves correctly.
3. **Real-copy asm:** `__asm__ volatile("movs %0,%1" : "=r"(dst) : "r"(src))`
   emits `adds Rd,Rs,#0` (0x1Cxx). Empty template is a MISCOMPILE.
4. **k-reuse:** Reusing a u32 variable for 12 then 192 steers regs
   (k→r0, p→r1, tv→r0 via dead-value reuse).
5. **`+r` barrier for copies:** `__asm__ volatile("" : "+r"(t))` after `t=f4`
   prevents gcc from folding `t=f4; t&=mc` into `t=f4&mc`, forcing the
   `adds r4,r2,#0` copy.
6. **Opaque vram:** `__asm__ volatile("" : "+r"(vram))` prevents reassociation
   (`vram+(f6<<5)+32` → `tv+(f6<<5)+0x06000020` folding).
7. **t0 via asm:** `__asm__ volatile("mov %0, r8" : "=r"(t0))` gives
   `mov r0,r8` for pinned-r8 source (plain C canonicalizes oddly).
8. **u16 loop counter:** `for (u16 i=0; i<=7; i++)` gives
   `adds/lsls#16/lsrs#16/cmp#7/bls` (not `cmp#8/blt`).

## Tooling
- `staging/wave30_C/v30.sh` — verify harness (wave29_C adapted; added
  sysroot binutils to PATH after PATH outage).
- `staging/wave30_C/c_080046b0_w30v1.c` … `v11.c` — C rewrite iterations.
- `staging/wave30_C/c_080046b0_final.c` — MATCHED transcription (0 diffs).
- `staging/wave30_C/dis2asm2.py` — copied from wave30_B.
- `staging/wave30_C/c_080046b0_trans.c` — raw dis2asm2 output (pool as code,
  superseded by _fixed).
- `staging/wave30_C/c_080046b0_w30v8.c` — v8 base for v9/v10.

## Summary for coordinator
- **MATCHED:** 0x080046B0 (SpriteTileUpload_080046B0, 244 B, transcription,
  0 diffs). Staged at `staging/wave30_C/c_080046b0_final.c`.
  **Not in registry — needs claim.**
- **BLOCKED (C rewrite):** 11 variants tried, best 14 diffs. Walls documented.
- **Progress:** 1/1 target matched (via transcription).
- **New idiom:** Pool-barrier mechanism (major predictor for mid-pools).
