# Wave 28 Coordinator Notes (coordinator, 2026-10-23)

## Headline
**800 / 1674 C-matched** (was 793 → +7); 13 ASM; **813 byte-identical total**; 245 blocked.
Build green at 8,388,608 bytes.

## Worker results
- **A (BlendCopy twins):** BLOCKED at best C 94 diffs (from 104). New clobber-reservation
  idiom for low-reg steering cracked the r3↔r4 swap: `__asm__ volatile("" : : "r"(av) : "r3")`
  denies r3 to av's live range without removing r3 from gcc's pool. RTL dumps prove the 3
  remaining mismatched copies are reload-generated (C-unavoidable). Twins identical except
  2 bytes (bl Memcpy16 encoding). → **Coordinator decision: sanctioned asm transcription**
  (dis2asm2.py), justified by exhaustive C attempts + RTL proof + wave-27 rect-fill precedent.
  Transcribed + verified both by coordinator: 0 diffs each.
- **B (near-miss closers):** 1 MATCHED — ChipSetup_0801B0DC (220 B incl pool, old_agbcc).
  New idioms: int-vs-u8 clamp signedness rule; GAS 2.42 Thumb-16 `adds` mnemonic quirk
  (`add` no-'s' = identical 0x1c08 encoding); single-instruction asm assist for coalesced copies;
  size-mismatch invalidates diff counts (0x0803643c: v3 C is 380 B vs ROM 444 B — 64 B
  structural deficit, ROM has extra `sp4 != r6` compare block; sed patch moot until size matches).
  0x0801C428 BLOCKED at 174 diffs (ldrsh dest r2 vs ROM r3; s16-extern-params idiom already in
  base — wall is purely dest-register choice).
- **C (0x0801F254 family):** 3/3 MATCHED via sanctioned asm transcription — Reset_0801F254
  (164 B), sub_0802375C (198 B; pools in middle → manual .word + .align 1), sub_0802298C
  (236 B incl pools; size correction, not 220). v/c allocation wall proven C-unreachable
  (~20 variants). New idioms: block-scoped constant flips s[10] to ROM's movs-before-ldrb
  order; `!!(x)` → ROM's negs/orrs/lsrs #31 boolean conversion; middle/end pools: exclude +
  manual .word (transcribed-as-instructions reassembles identically by accident but is fragile).
- **D (bulk + revisits):** 1 MATCHED — MenuTick_0802D6E0 (192 B, old_agbcc; main agbcc
  misallocates v6→r2 vs ROM's r1). New idioms: volatile-store DSE defeat
  (`*(volatile u16 *)&local = 0`, ZERO bytes overhead vs +48 B volatile var); old_agbcc
  decisive on allocation (confirms w27c); memory barrier pins constant-materialization
  before loads; u32 temp forces `ands` dest=r0; nested scope orders pool loads; p-reuse
  reuses dead parameter register. 0x0801C030: vv-reuse idiom confirmed working
  (114 diffs, prologue r6 wall remains). 0x08049560: prologue now matches via volatile-store
  idiom (44 diffs, 48 B bloat elsewhere). 7 bulk rows triaged.

## Coordinator verification (independent, clean-room)
All 7 claims: recompile from scratch (exact compiler+flags) → custom .ld link at true ROM
address → objcopy → cmp vs baserom at file offset (addr − 0x08000000), exact byte counts,
full extents incl. pools, non-empty assertions at every step, neighbor check — **7/7 at 0 diffs**.
In-built-ROM extraction of all 7 landed sections: **0 diffs each**.
Registry: append-only, 801 MATCHED rows / 800 distinct — only duplicate is the known
0x08011e20 reverted pair. Zero new duplicates.

## Landing hygiene applied
- Stripped `.globl`+`.set` for 7 real build T symbols across the 3 w28c files
  (F_20230, Wrapper_D728, Load4Tiles, F_0D6E0, F_0D9EC); renamed `bl F_0D6E0`/`bl F_0D9EC`
  to the real build names `ChipSlot_Setup`/`ChipSlot_IncUse` (nm-verified T).
- Stripped Memcpy16 `.set` in blend files (real build symbol, src/wave4_h.c).
- Kept data-address `.set`s (g_020031E4, g_081705B0, g_08227174, g_08227192, g_0817386C) — no conflicts.
- Makefile: SRCS_C + per-file rules (old_agbcc for w28b/w28d). ldscript: 7 slots appended
  after the Wave 27 block (no reorders).
- dis2asm2.py label bug found: objdump renders branch targets as FILE offsets (0x22510);
  they must be rebased to ROM addresses before transcription or labels are silently dropped
  (0 labels on first pass). Fixed in staging/wave28_coord_verify/dis_*.txt generation.

## Regression
mmbcc/tools/regression_check.py: **792 sections — 736 clean (+5), 53 accepted 2B c046
tail artifacts (+2: the BlendCopy twins carry a 2-byte linker pad after their 206 B bodies;
bodies 0-diff), 3 pre-existing dirty (sram VerifyCompare, mainloop, text_open) — zero regressions.**

## What's next (Wave 29 candidates)
1. 0x0803643c C rework — find the missing `sp4 != r6` 64 B compare block first (size first, diffs later).
2. 0x0801C030 prologue r6/vv allocation (114 diffs).
3. 0x08049560 48 B bloat (44 diffs, volatile-store idiom in hand).
4. 0x0801C428 ldrsh dest (174 diffs).
5. 7 triaged bulk rows: 0x08002a1c (ldrsb → inline asm), 0x080046b0 (gfx, high-reg pressure),
   0x0803ac4c, 0x0801e77c, 0x080096bc, 0x08006fe8, 0x08024a30.
