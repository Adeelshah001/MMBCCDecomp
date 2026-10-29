# Wave 32 Worker A — match notes (0x080096BC)

Target: TileList_Upload @ 0x080096BC, true extent 272 B
(neighbor 0x080097CC from docs/func_list_v2.txt; re-verified, never self-measured).

## Claims (staged, coordinator lands)

| addr | name | size | diffs | method |
|---|---|---|---|---|
| 0x080096BC | TileList_Upload | 272 B (260 code + 12 pool) | 0 | sanctioned asm transcription via dis2asm2.py |

Registry: MATCHED row appended to docs/match_status.tsv (append-only).
Source staged at `staging/wave32_A/w32a_080096bc_asm.c`; mmbcc/src/,
Makefile, ldscript.ld NOT touched (worker stages only).

## Semantics (confirmed against ROM bytes)
Uploads a u16 tile list to VRAM: dst = 0x06010000 + ((base + (y<<5) + x)<<5).
For each tile: if (t & 0x8000) break (terminator); if ((t & 0xE00) != 0x200)
blit 32 B from `seq + (((u16*)(*(u32*)0x081720CC + ((t&0x1FF)<<2)))[0]<<6)`
to vram and vram+0x400 via Memcpy16 (0x08000758), 4 calls total.
Tail filled with the default tile at `*(u16**)0x081720B4`.
Register usage: r8 = seq base, r9 = (s8)n bound, sl = (u8)n, r5 = vram cursor,
r6 = list cursor/bound, r7 = s16 loop counter i. Uses lsl/asr u8/s16 idioms
and the `subs r1,#1; adds r0,r1,#0; ands r2,r0` 0x1FF derivation.
Wave-31B tried 11 C variants (best 102 diffs); transcription bar met.

## Verification (hardened)
- ROM: full-image SHA-1 = 72309736f3820470c6f372d6a05ad1f16bc5a946 (gate passes).
- Slice 0x080096BC..0x080097CC extracted (file offset 0x96BC), SHA-1
  e9ccb4a6de069bb68cc6d837d229c7044ca107e3.
- Pools verified from ROM bytes (not disasm): 0x06010000 / 0x081720B4 /
  0x081720CC at 0x080097C0..0x080097CC (12 B).
- Harness `staging/wave32_A/verify.sh`: cpp -> agbcc -O2 -mthumb-interwork ->
  as -mthumb -mcpu=arm7tdmi -> ld at VMA 0x080096BC with .set Memcpy16=0x08000758
  -> objcopy -j .text.w32a_080096bc_asm. Non-empty at every step
  (o=1084, elf=2484, bin=272). bin == 272 B exactly, no truncation/padding.
- cmp vs ROM extract over full 272 B: **0 diffs**. Built section SHA-1 ==
  ROM slice SHA-1. Disassembly round-trip of built bytes identical to ROM
  disassembly. bl encodings correct => section VMA confirmed right.
- 272 % 4 == 0: no FIXALIGN1 / .byte padding needed.

## Landing-hygiene applied
- Memcpy16 confirmed GLOBAL T in build/wave4_h.o (nm) -> .globl+.set stripped
  from staged file; `bl Memcpy16` with comment "real build symbol (src/wave4_h.c),
  resolved at link" (matches w28a/w30b convention).
- No other callees (4x bl all to 0x08000758). No .thumb_func needed for unmatched
  callees (none). Branch targets -> local .L_ labels only.

## New idioms / observations
- Pool-word instruction aliases in transcription: 0x06010000 assembles as
  `movs r0, r0` + `lsls r1, r0, #24`; 0x081720B4/0x081720CC as
  `movs r0, #180/#204` + `lsrs r7, r2, #32`. GAS 2.42 encodes `lsrs r7, r2, #32`
  (imm5=0) byte-identically. Keeping the natural objdump decomposition for pool
  words is byte-safe (w30b used .word only where decomposition was inconsistent).
- `.n` suffix strip (dis2asm2): all branch targets in range; narrow forms
  selected automatically by GAS unified syntax — 0 diffs confirms no width
  mismatch.
- `TileList_Upload` lands as pure file-scope __asm__; compiler choice (main vs
  old_agbcc) is immaterial for this TU (no C code emitted).

## Nothing still blocked from this worker
Wave-31B's 0x08006FE8 and 0x08024A30 are out of scope for this assignment
(Worker A target was 0x080096BC only).

## Staging paths
- `staging/wave32_A/w32a_080096bc_asm.c` — the staged transcription (final)
- `staging/wave32_A/verify.sh` — the verification harness
- `staging/wave32_A/dis_raw.txt` — objdump source for the transcription
- `staging/wave32_A/rom_080096BC.bin` — 272 B ROM slice (SHA-1 e9ccb4a6...)
- `staging/wave32_A/dis2asm2.py` — copy of the wave30_C tool
- `staging/wave32_A/_v.*` — harness intermediates (reproducible by re-running verify.sh)
