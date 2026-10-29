# Match notes — H-blank raster engine (Wave 1)

Date: 2026-10-20. Worker: Phase-3 Wave-1 (hblank). All four functions in
`mmbcc/src/hblank.c` are MATCHED (byte-identical code+pool vs baserom
SHA-1 `72309736…`, verified via `make` + region `cmp`). Flags: agbcc
`-O2 -mthumb-interwork` (Makefile defaults); no flag variation needed.

## Results

| Function | Address | Section | Status |
|---|---|---|---|
| HBlank_RasterSetup | 0x08000AD4 | .text.hblank_setup | MATCHED |
| HBlank_Raster0 | 0x08000B54 | .text.hblank0 | MATCHED |
| HBlank_Raster1 | 0x08000BAC | .text.hblank1 | MATCHED |
| HBlank_Raster01 | 0x08000C04 | .text.hblank01 | MATCHED |

## C idioms that worked

- ISRs snapshot `REG_VCOUNT` (0x04000006) into a **`volatile unsigned short`
  stack local**, re-read before each compare. A plain local gets register-
  promoted and breaks the match; volatile forces the `mov rX,sp`/`ldrh` pairs.
- `REG_DISPSTAT` (0x04000004) / `REG_IE` (0x04000200) updates are written as
  `REG |= / &= mask;` followed by a **dummy `(void)REG;` re-read**. This is a
  write-posting read in the original; omitting it drops the trailing `ldrh`
  and breaks the match. Same idiom in RasterSetup's `|=`.
- `HBlank_Raster01` keeps the descriptor pointer in r4 across both
  `StridedCopy` calls. agbcc only does this if `desc` is declared
  **uninitialized at function top** (or block-scoped after the first `if`);
  initializing it in the declaration at function top makes the compiler
  reload the constant per call.
- `HBlank_RasterSetup`:
  - `sel` is a **`short`** local (r5). `sel=1` via `movs`, `sel+=2` via the
    lsl/add/lsr 16-bit dance, `if (sel!=0)` via lsl/asr/cmp/beq.
  - Corrected behavior (from re-reading branch targets): `sel += 2` sits
    **inside** the desc1-active block, not after it. So sel=1→Raster0
    (desc0 only), sel=2→Raster1 (desc1 only), sel=3→Raster01 (both),
    sel=0→ISR not armed. Table at 0x0816E22C = {NULL, Raster0, Raster1,
    Raster01} — matches the "1→B54, 2→BAC, 3→C04" mapping.
  - Desc fields accessed as `unsigned int *` words: `desc[2]`=count/flag,
    `desc[3]=desc[0]` primes, desc1 at `desc2 = desc; desc2 += 7;`
    with `desc2[3] = desc[7]` (compiler addresses desc1 word0 via r4+28).
  - ISR vector store: `((unsigned int *)desc - 0x60)[1] = table[sel]`
    must be split so the `-0x180` is not folded with the `[1]`; use a
    named `vec` and assign before storing.
  - **Empty `asm volatile("" : "+r" (t))` barrier** on the table pointer:
    without it, CSE forwards the `0x0816E22C` constant into `t[sel]` and
    GCC's commutative-operand swap emits `lsls r0,r3,#2` *before*
    `ldr r1,=table`; the ROM has load-before-shift. The barrier pins the
    load first and generates zero instructions (verified in .s).

## Behavior notes for the recomp track

- ISR gating: `if (VCOUNT > 159) return;` then copy; `if (VCOUNT != 159)
  return;` then teardown. At VCOUNT==159 (last visible scanline) the ISR
  clears DISPSTAT bit 4 (H-blank IRQ enable) and IE bit 1, i.e. it
  **self-disarms at end of frame**. A recompiler can treat each ISR as a
  per-scanline callback that runs only for VCOUNT 0–159.
- `HBlank_RasterSetup` runs the pending `StridedCopy`(ies) **immediately**
  (priming the first scanline's data) before arming DISPSTAT/IE and
  installing the vector at `[0x03000404]`.
- `StridedCopy` updates the descriptor's src word in place (`desc[3]`
  primed from `desc[0]` on setup, then advanced per scanline by the ISR
  calls) — the descriptor at 0x03000580 / 0x0300059C is stateful across
  the frame.
- Raster0's table slot (index 1) is never selected by `HBlank_RasterSetup`
  (sel∈{2,3} when arming); it may be installed by another path or be
  vestigial.
