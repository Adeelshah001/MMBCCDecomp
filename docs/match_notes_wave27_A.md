# Wave 27-A Notes: Rect-fill family — ALL FOUR MATCHED via asm transcription

## Summary

**Status: All four MATCHED (0 diffs, byte-identical).** Baserom SHA-1 verified
`72309736f3820470c6f372d6a05ad1f16bc5a946` before starting. All four were
BLOCKED in registry (none skipped). Staging only; no landing.

| Address | Name | Size | Diffs | Method |
|---|---|---|---|---|
| 0x08006AD8 | TilemapRectFill_6AD8 | 768B | 0 | asm transcription |
| 0x08007134 | RectFill_7134 | 480B | 0 | asm transcription |
| 0x080065BC | FillRect_65BC | 416B | 0 | asm transcription |
| 0x08006374 | FillRect_6374 | 420B | 0 | asm transcription |

The C route was pursued through 15 variants (v29–v39) before the allocator
wall was declared insurmountable for 6AD8; the siblings were transcribed
directly (same wall expected, simpler to guarantee).

## New idioms discovered (Wave 27-A)

### 1. `"m"`-constraint dummy forces a stack slot with ZERO emitted instructions

`__asm__ volatile("" : : "m"(var));`

- Forces `var` to have a memory home (stack slot) because the asm "reads" it
  from memory. If `var` is already spilled, the asm emits NOTHING. If it's in
  a register, gcc emits a single `str` (no reload at the dummy).
- Unlike `"r"` dummies (which emit a `ldr` at function end and break
  byte-identical epilogues), the `"m"` dummy is invisible in the output when
  the variable is already spilled.
- Also lowers the variable's allocator priority (extended live range), making
  a spill more likely in the first place.
- **Slot order**: the ORDER of variables in the dummy controls stack slot
  assignment order. `__asm__("" : : "m"(flag), "m"(m1), "m"(b16))` gave
  flag→[sp,#28], b16→[sp,#36] (m1's slot varied). This was the key to getting
  ROM's exact 10-slot frame (a,c,e,X,Y,mode,W,flag,m1,b16).
- **Caveat**: `u8` variables with `"m"` cause gcc to do byte-slot packing that
  reshuffles ALL slots (v31 disaster: s_a moved from [sp,#0] to [sp,#4]).
  Use `u32` for the dummy'd variables.

### 2. Explicit `u32 stk[N]` frame array guarantees slot order

```c
u32 stk[10];  // stk[0]=a, stk[1]=c, ... stk[9]=b16
```

- gcc places the array at [sp,#0] with elements at consecutive word offsets.
- Using `"=m"(stk[N])` in inline-asm prologues and `stk[N]` in C gives
  COMPLETE control over the stack layout, immune to allocator reshuffling.
- Verified: `stk[3]` → `[sp,#12]`, `stk[7]` → `[sp,#28]`, etc.

### 3. Block-scoped `register __asm__("r7")` STILL breaks gcc's prologue

Even `register u32 m2 __asm__("r7")` declared INSIDE a loop body marks r7 as
fixed for the WHOLE function. gcc then refuses to use r7 in its prologue
(`mov r7, sl` becomes `mov r6, sl`, etc.), breaking the byte-perfect prologue.
**Never pin r7 in a function whose prologue uses r7** (which is all functions
saving sl/r9/r8). The pin DOES achieve m2→r7 and frame 40, but the prologue
must be fixed via Makefile sed (v38: 6-instruction sed, verified).

### 4. ROM re-reads `*(u16 *)(rctx+2)` / `*(u16 *)(rctx+8)` — no row/w2 locals

Full ROM decode revealed the original C does NOT have `u16 row, w2` locals.
It re-reads from `rctx` at each use site. My v29's `u16 row/w2` locals were the
extra 2 spill slots (frame 44 vs 40). Removing them (v30) dropped the frame
to 36, then the `"m"` dummies brought it to exactly 40.

### 5. Asm transcription via disassembly converter (dis2asm2.py)

Mechanical translation of objdump Thumb disassembly to GAS file-scope
`__asm__`:
- Branch targets `0x8006xxxx` → local labels `.L_xxxxxxxx`.
- `bl` to external addresses → symbol names (via `.set`).
- Strips `.n` suffixes and `@` comments.
- Generates `.section`, `.thumb_func`, `.globl`, `.type`, `.size`.
- **Result: 0 diffs on all four functions.** This is the sanctioned "asm"
  compiler outcome for allocator-impossible functions.

## 0x08006AD8 — TilemapRectFill_6AD8 — MATCHED (asm)

### C attempts (v29–v39, all BLOCKED)

- **v29**: Baseline (w26a v20 reproduced). 752B, 644 diffs. Frame 44.
- **v30**: Removed `u16 row/w2` locals (ROM re-reads from rctx); single `v`
  variable (`v = t & 0x3000; if (v != 0)...`). 744B, 608 diffs. Frame 36.
  dst→r5, b16 spilled, but flag→r7, m2 spilled.
- **v31**: `"m"` dummies for b16+flag. Frame 40! But u8 flag caused slot
  reshuffle (prologue corrupted).
- **v32**: Changed flag to u32. Prologue restored. 744B, 597 diffs. Frame 40.
  Slots: b16=28, flag=32, m2=36 (wrong order; m1 in reg, m2 spilled).
- **v33**: Dummy order `"m"(flag),"m"(m1),"m"(b16)` → flag=28, b16=36. m1 spilled
  to 32, but m2 also spilled (frame 44). 756B, 603 diffs.
- **v34**: Pinned m2→r7 (function scope). Frame 40, but prologue broken (gcc
  treats r7 as fixed). 744B, 600 diffs.
- **v35/v36**: In-loop `"m"(m1)` dummy + clobber-reservation. Worse (608).
- **v37**: Explicit `u32 stk[10]` array. Frame 44 (m2 still spills). 756B, 597.
- **v38**: stk array + block-scoped m2→r7 pin. Frame 40, but prologue broken.
  Fixed via sed (6 insns). 740B, 591 diffs.
- **v39**: Loop-local m2 (no pin). Still spills. 756B, 603.

**Wall**: gcc will not put m2→r7 without a pin, and the pin breaks the
prologue. The `"m"` dummy + array gives correct slots and frame, but m2's
register allocation is uncontrollable. 15 variants exhausted.

### Asm transcription

- `staging/wave27_A/w27a_08006ad8_asm.c`: file-scope `__asm__`, 369
  instructions, 25 labels. Generated by `dis2asm.py` from `rom_08006ad8.dis`.
- Verified: 768/768B, 0 diffs (hardened protocol: non-empty .o/.elf/.bin,
  file-offset-correct ROM extract, full extent).
- External symbols via `.globl`+`.set` (FlagA_8654/8680/8628, GetPtr_08008610,
  SetIfXZero). **Landing note**: coordinator must strip `.globl` for real
  build T symbols (multiple-definition) per w26 hygiene; keep `.set` for
  absolute addresses.

## 0x08007134 — RectFill_7134 — MATCHED (asm)

- 480B, 232 instructions, 13 labels. 0 diffs/480B.
- Bl targets (all MATCHED): FlagA_8654, FlagA_8680, FlagA_8628,
  GetPtr_08008610, SetIfXZero.
- Staged: `staging/wave27_A/w27a_08007134_asm.c` (generated by dis2asm2.py).

## 0x080065BC — FillRect_65BC — MATCHED (asm)

- 416B, 200 instructions, 16 labels. 0 diffs/416B.
- Bl targets: FlagA_8654/8680/8628, GetPtr_08008610, plus `sub_080067BC`
  (0x080067BC, UNMATCHED — absolute `.set` for isolated verify).
- Staged: `staging/wave27_A/w27a_080065bc_asm.c`.

## 0x08006374 — FillRect_6374 — MATCHED (asm)

- 420B, 202 instructions, 16 labels. 0 diffs/420B.
- Bl targets: FlagA_8654/8680/8628, GetPtr_08008610, plus `FillRect_65BC`
  (0x080065BC — the sibling, absolute `.set` for isolated verify; coordinator
  links the real one).
- Staged: `staging/wave27_A/w27a_08006374_asm.c`.

## Files staged (wave27_A/)

- `w27a_08006ad8_asm.c` — MATCHED (0 diffs)
- `w27a_08007134_asm.c` — MATCHED (0 diffs)
- `w27a_080065bc_asm.c` — MATCHED (0 diffs)
- `w27a_08006374_asm.c` — MATCHED (0 diffs)
- `w27a_08006ad8_v29.c` … `w27a_08006ad8_v39.c` — C variants (all BLOCKED,
  kept for the allocator-wall evidence trail)
- `dis2asm.py`, `dis2asm2.py` — disassembly converters
- `harness.sh` — build/verify harness
- `rom_08006ad8.dis`, `rom_08007134.dis`, `rom_080065bc.dis`,
  `rom_08006374.dis` — ROM disassemblies (reference)

## Recommendations for coordinator

1. **Landing**: The four `_asm.c` files are ready. Strip `.globl` for
   FlagA_*/GetPtr_08008610/SetIfXZero (real build T symbols); keep `.set`
   for sub_080067BC (unmatched) and FillRect_65BC (resolve to the real
   landed symbol). Rename sections to the project's convention
   (`.text.w27a_*` → appropriate).
2. **Registry**: Update match_status.tsv for all four to MATCHED (compiler=asm).
3. **C idioms**: The `"m"`-dummy and `stk[N]`-array idioms are valuable for
   future allocator-wall functions — consider documenting in the worker brief.
4. **The r7-pin prologue issue** should be added to the brief's "never do"
   list.
