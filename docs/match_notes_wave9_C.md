# Wave 9 Batch C Notes (Worker C)

Division-block boundary resolution + ARM math region map + 2 C matches.

## Part 1: T_0804DE70 Boundary Resolution — RESOLVED (boundary CORRECT)

### Question
Worker L flagged T_0804DE70 (0x0804DE70, 110B): `push {r4}` appears AFTER
`movs r3,#1; movs r2,#0` (mid-prologue), and `beq 0x804dede` jumps PAST the
claimed end. Is it a shared epilogue, or a generator mis-split?

### Method
Disassembled ROM bytes 0x0804DD80–0x0804E020 (Thumb, via objdump before the
binutils outage; verified with a Python Thumb decoder after). Checked
xrefs.tsv for incoming edges to 0x0804DEDE.

### Findings
1. **The beq target 0x0804DEDE is a distinct, already-MATCHED function**
   (DivZeroStub_4DEDE, 10B: `push {lr}; bl 0x0804DD9C; movs r0,#0; pop {pc}`).
   xrefs.tsv shows EXACTLY ONE incoming edge: `sub_0804DE70 @04DE72 bcond
   sub_0804DEDE @04DEDE beq`. It is not a shared epilogue (no other callers)
   and not a mis-split (it returns directly to T_0804DE70's caller via
   `pop {pc}`, preserving lr — a deliberate div-by-zero guard).
2. **True extent is 0x0804DE70–0x0804DEDE = 110 bytes**, exactly as claimed.
   The function ends `adds r0,r2,#0; pop {r4}; mov pc,lr` at 0x0804DED8–DC.
3. The mid-prologue `push {r4}` is genuine: this whole division family
   (0x0804DD08, 0x0804DDA0, 0x0804DE70, 0x0804DEE8) places pushes after
   initial cmp/beq/movs — consistent with hand-written asm or a foreign TU
   (cf. docs/match_notes_wave3_d.md conclusion for this region).

**Conclusion: boundary was CORRECT. No registry correction needed for the
extent; notes updated to record the resolution.**

### C-match impossibility (proven empirically)
Attempted faithful C with divzero guard via leading volatile asm
(`cmp r1,#0; beq DivZeroStub_4DEDE`). Hard blockers, tested on both
agbcc and old_agbcc across -O2/-O1/-Os, ±mthumb-interwork, ±frame-pointer:
- Both compilers ALWAYS emit `push {r4,lr}` (or `{r4,r5,lr}`) at function
  START for any function with control flow using callee-saved regs. ROM has
  `push {r4}` 4th, no lr. (Even a trivial loop with no saved regs gets
  `push {lr}` — a quirk of this gcc snapshot.)
- Epilogue: compilers emit `pop {r4,pc}` / `pop {r4}; pop {r1}; bx r1`.
  ROM has `pop {r4}; mov pc,lr`.
- The volatile-asm guard is reordered (compiler hoists `movs r3,#1` above it).

These are prologue/epilogue codegen differences, not circumventable from C.
**Recommendation: match the division family via `.s` transcription**
(wave3_d precedent; cf. asm/thunks.s, Audio_MixFragment naked+asm).
Staged C attempt: `staging/wave9_C/divfaith.c` (+ 4 flag variants).

### Full division-block map (0x0804DCCC–0x0804DFA8)
| Address | Size | Name (behavior) | Status |
|---|---|---|---|
| 0x0804DCCC | 32 | _call_via_r0..r7 (8× `bx rN; mov r8,r8`) | MATCHED (asm/thunks.s) |
| 0x0804DCEC | 28 | DupThunks: 7× `bx r0-r6; mov r8,r8` (duplicates!) | UNREGISTERED, .s-trivial |
| 0x0804DD08 | 136 | **SDiv_0804DD08** (signed __divsi3) | BLOCKED (C impossible) |
| 0x0804DD90 | 12 | **DivZeroStub_4DD90** (10B+pad) | **MATCHED** (this wave) |
| 0x0804DD9C | 4 | Trap: `mov pc,lr` + pad | BLOCKED (not a function) |
| 0x0804DDA0 | 196 | **SMod_0804DDA0** (signed __modsi3) | BLOCKED (C impossible) |
| 0x0804DE64 | 12 | DivZeroStub (10B+pad) | MATCHED (wave3_d_noiw.c) |
| 0x0804DE70 | 110 | **UDiv_0804DE70** (unsigned __udivsi3) | BLOCKED (C impossible) |
| 0x0804DEDE | 10 | DivZeroStub_4DEDE | MATCHED (ldscript BYTE) |
| 0x0804DEE8 | 182 | **UMod_0804DEE8** (unsigned __umodsi3) | BLOCKED (C impossible) |
| 0x0804DF9E | 10 | Wrap_0804DF9E | MATCHED (noiw TU) |
| 0x0804DFA8 | 94 | **Memcpy_4DFA8** | **MATCHED** (this wave) |

Four identical divzero stubs (DD90, DE64, DEDE, DF9E); bl offsets differ per
site. SDiv_0804DD08 was missing from the registry (added to results.tsv).

Algorithm (all four): 4-bit alignment (`while (d < 0x10000000 && d < n)
{d<<=4;bit<<=4}`, then 1-bit to 0x80000000), then 4-unrolled subtract/OR
steps with `lsrs r4,r1,#k` / `lsrs r4,r3,#k`, loop while n!=0 && bit!=0.
Signed variants handle signs via negs + eors/ip (div) or stacked r0 (mod).

## Part 2: ARM Math Region Map (0x0804BB9C–0x0804DFA8)

### ARM audio block (0x0804BB9C–0x0804BD84, 488B ARM)
**ARM_MixSamples_0804BB9C** (true entry; was ARM_SampleMulAccum):
- Entered via Thumb trampoline at 0x0804BB96: `add r0,pc,#4; bx r0`.
- Prologue: `str r8,[sp,#0]`; loads vol L/R bytes [r4,#0xa/b], lsl #16.
- `ldrb r0,[r4,#1]; tst r0,#8; beq 0x0804BCDC` → delta-mix fragment.
- PCM path: `cmp r2,#4`; 4x-unrolled loop (0x0804BBC4, `subs r2,r2,r8`
  ... `bgt`) vs per-sample loop (0x0804BC2C, `subs r2,r2,#1`).
- Inner: `sbcs r0,r3,r1,asr r0` (delta decode), `mul r1,r10,r0`,
  `bic r1,#0xff0000`, `add r6,r1,r6,ror #8` (mix accumulate, dual channel).
- **Audio_MixFragment@0x0804BCDC** (MATCHED, mid-function entry): pushes
  r4/r12, own mix loop, `ble 0x0804BC74` exit to shared code.
- Shared epilogue 0x0804BD78: `ldr r8,[sp,#0]; add r0,pc,#1; bx r0`
  → Thumb 0x0804BD84.
- C impossible (ARM code). Full naked+asm transcription deferred (488B,
  2 entries — larger than the fragment task).

### Rest of range
0x0804BD84–0x0804DCCC: Thumb text/audio/script functions (registry has
entries; mostly BLOCKED from other waves — not re-attempted here).
0x0804DCCC–0x0804DFA8: thunks + division block (table above).

## Matches Landed (this wave)

### Memcpy_4DFA8 @0x0804DFA8 (94B) — MATCHED
Optimized memcpy. Key idioms:
- **Explicit assignment order** (`d = dst; s = src;` as statements, s
  declared first) forces prologue `adds r5,r0; adds r4,r5; adds r3,r1`.
- **sw pinned to r3** (`register const u32 *sw __asm__("r3")`): coalesces
  with s; without pinning the allocator puts sw in r1.
- **dw initialized from `dst` (not `d`)**: gives `adds r1,r5,#0`; from `d`
  the compiler reuses r4.
- `*dw++ = *sw++` ×4 gives `ldmia r3!,{r0} / stmia r1!,{r0}` pairs.
- Byte tail: `u32 n = len-1; if (n != (u32)-1) do {...} while (--n != -1)`
  reproduces `subs/movs #1/negs/cmp/beq` exactly.
- **no-interwork TU** for `pop {r4,r5,pc}` epilogue.
- Section is 96B (94 + align); ROM has `00 00` at 0x0804E006. ✓
- Verified: section extract == ROM (94/94), linked ELF == ROM.

### DivZeroStub_4DD90 @0x0804DD90 (12B) — MATCHED
`u32 F(void){ sub_0804DD9C(); return 0; }` in no-interwork TU.
`sub_0804DD9C` resolved via existing `.set` in wave3_d_noiw.c (extern decl,
no duplicate). 10B + `static const u8 pad[2]` (ROM `00 00` at 0x0804DD9A).
Linked ELF == ROM (12/12).

## Files
- `mmbcc/src/wave9_c_noiw.c` (landed)
- Makefile: SRCS_C += src/wave9_c_noiw.c; no-interwork rule
- ldscript: slots at 0x0804DD90, 0x0804DFA8
- Staging: `staging/wave9_C/` (divfaith.c + flag variants, memcpy_v1..v10,
  armdis.py, thumbdis.py, armdump.txt) — NOT deleted per rule.

## Toolchain outage note
Mid-task, /usr/bin/arm-none-eabi-{as,ld,objdump,objcopy} vanished (known VM
quirk; cf. wave 8 notes). Work continued via Python decoders; parent
restored binutils 2.42 via dpkg. All verification above used the restored
toolchain. If it recurs, reinstall from
/tmp/binutils-arm-none-eabi_2.42-1ubuntu1+23_amd64.deb.
