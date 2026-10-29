# Wave 10 Worker T (TAG=T) — Task_3AFFC Unblock Path — Match Notes

Worker: Wave 10 specialist (TAG=T). Date: 2026-10-21.
Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` before start.
Toolchain: `mmbcc/tools/agbcc/bin/old_agbcc`; `arm-none-eabi` 2.42 (vanished
mid-session ~22:00 EDT, recovered on its own ~22:08 — the known VM quirk).
Harness: `staging/wave10_T/mk.sh` (adapted from wave9_F: hardened, non-empty
assertions, file offset = addr − 0x08000000, full extent incl pools/pads,
`cmp -l` zero diffs). Staging: `~/workspace/mmbcc-decomp/staging/wave10_T/`.
Results: `docs/wave10_T_results.tsv`.

**Result: 1 MATCHED, 5 BLOCKED (4 fully RE'd + 3AFFC re-attack).**
Landing: `mmbcc/src/wave10_T_old.c` + Makefile + ldscript; `make` green;
B368 byte-identical in full build (verified by dd+cmp).

## MATCHED (1)

### sub_0800B368 @ 0x0800B368 (72 B, old_agbcc, 0 diffs)

Gate controller for the 0x02004E40 state block. ROM:
```
push {r4,r5,r6,lr}; r4=a; r5=b; r1=pool(0x02004E40)
r0 = 128 & base[4]; if ((base[4]&128)==0) goto else
  base[0]=0; base[3]=0; base[2]=0; base[1]=0;  (order 0,3,2,1)
  base[5]=3; *(u32*)(base+32)=a
  sub_0800B520(b,c,d); sub_0800B4E4(); sub_0800B4C8()
  return 1
else:
  base[5]=1; return 0
```

Idioms:
- **Inverted if** (`if ((x & 128) == 0) { else } else { work }`) gives ROM's
  `beq`-to-else layout (the natural `!=` form generates `bne`-to-if).
- **Store order 0,3,2,1** written explicitly matches ROM's scheduling.
- Callees via `.set` (B520=0x0800B520, B4E4=0x0800B4E4, B4C8=0x0800B4C8).

Staging: `staging/wave10_T/w10t_0800b368_v2.c` (verified MATCH).
Landed: `mmbcc/src/wave10_T_old.c` (`.text.w10t_0x0800b368`).

## FULLY RE'd (not matched) — Callee Signatures for 3AFFC

### sub_0800BEE0 @ 0x0800BEE0 (100 B) — W8-L blocker, RE complete

**CRITICAL CORRECTION:** The W8-L worker used base `0x0200404f` — WRONG.
The pool at 0x800bf14 is `40 4f 00 02` = **0x02004F40**. Their attempt could
never match (pool word mismatch). The correct base is 0x02004F40.

Signature: `void sub_0800BEE0(u16 a, u8 b)`
- r0 = a (u16, via `lsls r0,#16` then `lsrs r4,r0,#16`)
- r1 = b (u8, via `lsls r1,#24; lsrs r3,r1,#24`, duplicated to r5)

Behavior (fully decoded):
```
u8 *base = 0x02004F40;
if (*(u16*)(base+20) == a) return;   // via (v<<16)==(a<<16) shifted compare
*(u16*)(base+6) = a;
if (b == 128) {
    base[9] = (base[9] & 3) | 128;
    base[10] &= -7;                  // via movs+negs, NOT mov #249
} else {
    if (b > 128) base[10] |= 8;
    else         base[10] &= -9;     // via movs+negs
    base[10] = (base[10] & -7) | 4;  // via movs+negs
}
```

Call-site register behavior (for 3AFFC):
- `sub_0800BEE0(0x40, 0x80)`: r0=0x40, r1=0x80
- `sub_0800BEE0(0x40, 0x00)`: r0=0x40, r1=0x00
- Return: void (no return value)

Matching attempts (8 versions, best v6: 47 diffs, 104 vs 100 B):
- v6 achieved `push {r4,r5,r6,lr}`, r3=b, r5=b (`adds r5,r3,#0`), r4=a,
  r6=v via explicit register pinning.
- Remaining blockers: (1) prologue order (`lsl r1` before `lsl r0`, ROM does
  r0 first); (2) cross-register shift (`lsl r1,r6,#16` vs `lsl r6,r6,#16`);
  (3) body allocation for the `&-7` sequences (ROM: `movs r0,#7; negs r0;
  ldrb r6; ands r0,r6`).
- The `negs` idiom: `int t = base[10]; base[10] = t & -7;` forces
  `mov #7; neg` (vs `mov #249` for narrow u8). The `|128` must stay narrow.

### sub_080241F8 @ 0x080241F8 (176 B) — RE complete

Signature: `u8 sub_080241F8(u16 a)`
- r0 = a (u16, via `lsls/lsrs #16` in place)
- Returns u8 (via `lsls/lsrs #24` at join, or `movs r0,#200`)

Behavior (fully decoded): switch on `(a >> 12)` with u16 arg.
```
if (a == 0) return 200;
switch (a >> 12) {
case 1: {
    u8 *p = *(u8**)0x020070A4;
    return (u8)sub_08025A08(p + p[432]*144);  // r0=ptr, bl 0x08025A08
}
case 2:
    if ((a & 0xFFF) == 0) {
        u8 *p = *(u8**)0x020070A4;
        sub_08025A08(p + p[432]*144);          // bl 0x08025A08
    }
    return (u8)sub_08026554((void*)0x020070A8); // r0=0x020070A8, bl 0x08026554
case 3:
    return *(u8*)(0x082298F0 + (a & 0xFFF)*20 + 1);
case 4:
    return *(u8*)(0x020070CC + 1);
default:
    return 200;
}
```

Pools: 0x020070A4 (×2), 0x00000FFF (×2), 0x020070A8, 0x082298F0, 0x020070CC.
Callees: sub_08025A08=GetByte1_25A08 (MATCHED, returns u8), sub_08026554
(NOT in registry, unattempted).

Call-site register behavior (for 3AFFC mode 1):
- `sub_080241F8(0x1000)`: r0=0x1000, returns u8 in r0 (zero-extended)
- The `(u8)` cast in `sub_08024514((u8)sub_080241F8(0x1000))` — the return
  is already u8, so the cast is a no-op (or the compiler keeps it).

Matching attempts (3 versions, best v1: 102 diffs, 172 vs 176 B):
- Switch comparison chain matches structurally.
- Blocker: prologue zero-extend (`lsr r1,r0,#16` vs ROM's in-place
  `lsrs r0,r0,#16`); case-body register allocation (ROM keeps base in r0,
  mine moves to r2).

### sub_08024384 @ 0x08024384 (174 B) — RE complete (twin of 241F8)

Signature: `u8 sub_08024384(u16 a)`
Identical structure to 241F8 with different callees/offsets/default:
- case 1: `bl 0x08025A0C` (GetU8_0, MATCHED) instead of 0x08025A08
- case 2: `bl 0x080265B0` (NOT in registry) instead of 0x08026554
- case 3: `ldrb [r0,#0]` (offset 0) instead of `[r0,#1]`
- case 4: `ldrb [r0,#0]` (offset 0) instead of `[r0,#1]`
- default: `movs r0,#50` instead of `#200`

Pools: 0x020070A4 (×2), 0x00000FFF (×2), 0x020070A8, 0x082298F0, 0x020070CC.

Call-site register behavior (for 3AFFC modes 2/4):
- `sub_08024384(0x1000)`: r0=0x1000, returns u8 in r0
- Mode 2: `b = sub_08024384(0x1000) - 50` (u8 result minus 50)
- Mode 4: same pattern

### sub_0800B148 @ 0x0800B148 (340 B) — RE complete (complex)

Signature: `u8 sub_0800B148(u8 a, u16 b, u8 c)` (returns 0 or 1)
- r0 = a (u8, via `lsls/lsrs #24`, saved to ip)
- r1 = b (u16, via `lsls/lsrs #16` to r6)
- r2 = c (u8, via `lsls/lsrs #24` to r8)
- Returns u8 (0 or 1 via `movs r0,#0/#1`)

Behavior: Complex bitfield state machine on 0x02004E40 block.
- If (base[4] & 15) != 0: return 0.
- If (base[4] & 128) == 0:
  - base[19] = (base[19] & -2) | (c & 1); base[5] = 1
  - ... (continues with mode-dependent logic)
- Else (base[4] & 128 != 0):
  - Complex branching based on (base[21] & 15) vs a, etc.
  - Calls sub_0800B470 and sub_0800800C (need registry check)
- Full decode in staging disassembly; the function manipulates bits in
  base[5], base[19], base[20], base[21], base[24], base[30], base[31].

Call-site register behavior (for 3AFFC mode 1):
- `sub_0800B148(1, (s16)w, 4)`: r0=1, r1=w (s16), r2=4
- Return cast to `(s8)`: `if ((s8)sub_0800B148(...) != 0)`
- The s8 cast suggests the return is treated as signed (but values are 0/1).

## Task_3AFFC Re-attack — Outcome

**Status: BLOCKED (fundamental blocker persists; reconstruction incomplete).**

A from-scratch reconstruction was attempted (`staging/wave10_T/w10t_3affc_v1.c`)
using the RE'd callee signatures and the Wave 7 mode descriptions. Result:
684 vs 926 bytes, 590 diffs. The reconstruction is incomplete because:

1. **Missing Wave 7 v2 baseline**: The /tmp/wave7_a/ staging expired. The v2
   (661/864, off-variable idiom) is the baseline to beat, but it was not
   available for iterative improvement.
2. **JT section harness**: The compiler emits the jump table to .rodata,
   not .text.w10t_0803affc. The mk.sh harness only extracts the .text
   section, so the 64-byte JT + pools are missing from the comparison.
   The Wave 7 harness handled this; without it, verification is incomplete.
3. **Fundamental blocker**: Even with RE'd signatures, old_agbcc's
   cross-case if-check merging and tail over-merging persist. The callee
   signatures affect per-site register allocation but not the control-flow
   merging identified in Wave 7.

With the RE'd callee signatures in place:
- sub_080241F8: `u8 (u16)` — r0=0x1000 in, u8 out
- sub_0800B148: `u8 (u8,u16,u8)` — r0=1,r1=w,r2=4 in, s8-cast out
- sub_08024384: `u8 (u16)` — r0=0x1000 in, u8 out
- sub_0800B368: `u8 (u32,u32,u32,u32)` — MATCHED
- sub_0800BEE0: `void (u16,u8)` — r0=0x40,r1=0x80/0x00 in
- sub_0800B308: Check_B308 (MATCHED)
- sub_08024514: Sub200 (MATCHED)

New angles for future work:
1. **Per-case opaque asm barriers**: Insert `__asm__ volatile("" ::: "memory")`
   in each of the 16 cases to defeat cross-case merging. Requires the v2
   baseline.
2. **Macro with per-site differences**: The ROM's per-mode `ldr rX` register
   variation (r0 at modes 1,7,12,15; r2 at modes 2,4,8) suggests the original
   used a macro with subtle per-site differences. Proving this requires
   exact source reconstruction.
3. **JT-in-section harness**: Modify mk.sh to include .rodata JT in the
   comparison, or use a custom ld script that places the JT inline.

## New Idioms Discovered

- **Inverted-if for beq layout**: `if ((x & MASK) == 0) { else } else { work }`
  generates `beq`-to-else; the natural `!=` form generates `bne`-to-if.
  (Used in B368 match.)
- **Pool base correction**: Always verify pool words from the baserom;
  the W8-L 0x0200404f was a transcription error for 0x02004F40.
- **negs via int temp**: `int t = base[i]; base[i] = t & -7;` forces
  `movs rX,#7; negs rX` (vs `mov #249` for u8). Keep `|128` narrow.
- **Register pinning for allocation**: Explicit `register ... __asm__("rN")`
  can force ROM's r4/r5/r6 usage, but the compiler may still reorder
  prologue instructions.

## Environment

arm-none-eabi toolchain vanished from /usr/bin mid-session (~22:00 EDT),
recovered on its own ~22:08. This is the known VM quirk (Waves 8/9).
The `which` command failed earlier even when binaries existed — use
direct `/usr/bin/` paths or `command -v` for reliability.
