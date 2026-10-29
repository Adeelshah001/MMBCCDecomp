# Wave 10 Batch S Notes (Worker S) — division-block .s transcription

All five C-impossible division-block targets landed as hand-written Thumb
assembly in `mmbcc/asm/div.s` (new file, auto-included via Makefile
`SRCS_S` wildcard — no Makefile edit needed), with exact-address ldscript
slots next to the existing `.text.thunks` slot.

## Landed (5/5) — all ASM (byte-identical hand assembly)

| Address | Size | Name | Section |
|---|---|---|---|
| 0x0804DCEC | 28 | DupThunks_0804DCEC | .text.dupthunks |
| 0x0804DD08 | 136 | SDiv_0804DD08 | .text.sdiv |
| 0x0804DDA0 | 196 | SMod_0804DDA0 | .text.smod |
| 0x0804DE70 | 110 | UDiv_0804DE70 (renames T_0804DE70) | .text.udiv |
| 0x0804DEE8 | 182 | UMod_0804DEE8 | .text.umod |

### Verification (hardened, all green)
`make` builds clean. For each target: extracted `file offset =
addr - 0x08000000` from `mmbcc.gba`, asserted non-empty + exact byte
count, `cmp -l` vs baserom = **0 diffs**:
- DupThunks 28/28, SDiv 136/136, SMod 196/196, UDiv 110/110, UMod 182/182.
- Neighbors confirmed untouched: thunk span @0x0804DCCC (32B),
  DivZeroStub_4DD90 @0x0804DD90 (12B), DivZeroStub @0x0804DE64 (12B),
  DivZeroStub_4DEDE @0x0804DEDE (10B), Wrap_0804DF9E @0x0804DF9E (8B).
- ELF `readelf -S`: all five sections at exact addresses, sizes
  0x1c/0x88/0xc4/0x6e/0xb6.

### Correction to wave9 notes: DupThunks are NOT bx r0–r6
`docs/match_notes_wave9_C.md` described 0x0804DCEC as "7 duplicate
bx-thunks (bx r0-r6)". Re-disassembly proves the ROM bytes are
`47 40 / 47 48 / 47 50 / 47 58 / 47 60 / 47 68 / 47 70` =
**bx r8, bx r9, bx sl, bx fp, bx ip, bx sp, bx lr** (high registers),
each followed by `nop` (mov r8,r8). It is a distinct hi-reg twin set,
not duplicates of `_call_via_r0..r7`. The .s transcribes the real bytes
(the container symbol keeps the registry name DupThunks_0804DCEC;
per-thunk globals are DupThunk_r8..DupThunk_r14).

### Transcription pitfalls found and fixed (both caught by verification)
1. **Align-loop target split.** In each function the 4-bit alignment loop's
   `bcs` exits target the 1-bit phase *entry* (`lsl r4,r4,#3`), while the
   1-bit loop's back-edge `b` targets the *next* instruction
   (`cmp r1, r4`). Two labels per loop are required
   (`.L_X_align1entry` vs `.L_X_align1`); a single shared label is off by
   one instruction (e7f7 vs e7f8).
2. **Pre-UAL mnemonics.** GAS 2.42 with `-mcpu=arm7tdmi` (no `-mthumb`
   in ASFLAGS) rejects `adds/negs/eors/rors/orrs/lsls/lsrs/subs/ands`
   — write `add/neg/eor/ror/orr/lsl/lsr/sub/and/mov`. (`cmp/bcc/bcs/
   beq/bne/bpl/b/tst/push/pop/bx/mov pc,lr/nop` are unchanged.)
3. **External branch targets.** `beq DivZeroStub_4DD90` and
   `beq DivZeroStub` resolve to globals in build/wave9_c_noiw.o and
   build/wave3_d_noiw.o. `beq DivZeroStub_4DEDE` / `beq Wrap_0804DF9E`
   use `.set …, 0x0804DEDE` / `.set …, 0x0804DF9E` in div.s (those
   addresses are ldscript BYTE blocks; their documented .c sources
   wave3_e_noiw.c / wave4_j_noiw.c are intentionally NOT in SRCS_C,
   so no duplicate symbols).
4. **2-aligned slots.** 0x0804DCEC/0x0804DDA0/0x0804DE70 use
   `SUBALIGN(2)` in ldscript (w3e_divzero_4dede precedent); sections
   carry `.balign 2`.

### Algorithm recap (all four, per wave9_C analysis)
4-bit alignment: `while (d < 0x10000000 && d < n) { d <<= 4; bit <<= 4 }`,
then 1-bit: `while (d < 0x80000000 && d < n) { d <<= 1; bit <<= 1 }`;
then 4-unrolled subtract/OR steps (`lsrs r4,r1,#k` vs `lsrs r4,r3,#k`,
`orrs` quotient bits), looping while `n != 0 && bit != 0`.
Signed variants: SDiv tracks sign via `eor r4,r1`/`mov ip,r4` and
`negs` both inputs, negating the quotient at the end; SMod stacks the
original r0 (`push {r0}`) for the trailing sign fixup and builds the
remainder with the ip/ror quotient-bit trick plus a final adjust pass
(`ands r2, #0xE0000000` mask, `tst`/`adds` back selected divisor
shifts). UMod early-returns `mov pc,lr` (no push yet) when
`divisor > dividend`.

## Mapped but deferred
- The 4B trap at 0x0804DD9C (`mov pc,lr` + pad): confirmed NOT a
  function (no incoming xrefs besides the four divzero stubs' `bl`);
  not registered, per task instructions.
- `T_0804DE70` → recommend registry rename to `UDiv_0804DE70`
  (behavior-confirmed unsigned __udivsi3); row kept as UDiv_0804DE70
  in wave10_S_results.tsv for the coordinator to merge.
- match_status.tsv rows for the 5 targets should move BLOCKED → ASM
  (coordinator merge; not edited here per instructions).

## Files
- `mmbcc/asm/div.s` (new) — the five transcriptions
- `mmbcc/ldscript.ld` — five exact-address slots + SUBALIGN(2) notes
- `docs/wave10_S_results.tsv` (new) — results table
- `docs/match_notes_wave10_S.md` (this file)
- Staging: none needed (no C attempts; objdump binaries in /tmp only)
