# Wave 33 Worker A Notes: 0x08006FE8 PatternRowsBlit — MATCHED (sanctioned transcription)

## Result

**MATCHED via sanctioned asm transcription. 0 diffs, 264 bytes, true extent 0x08006FE8–0x080070F0, no pool.**

Staged: `staging/wave33_A/w33a_08006fe8_asm.c` (file-scope `__asm__` via dis2asm2.py, 126 insns, 7 local labels).
Verified: clean-room recompile (agbcc main, `-O2 -mthumb-interwork`) → link at 0x08006FE8 → objcopy → `cmp` vs baserom at file offset 0x6FE8, 264 bytes, **0 diffs**. All steps non-empty (o=1216, elf=4948, bin=264).
Registry: 0x08006fe8 has 2 rows (W31 BLOCKED, W32 BLOCKED), no MATCHED row — claim is valid.
Callees (all MATCHED in real build, resolved at link — no `.set` in staged file):
FlagA_8680 (0x08008680), FlagA_8628 (0x08008628), FlagA_8654 (0x08008654),
GetPtr_08008610 (0x08008610), SetIfXZero (0x08008bb8).

## Semantics (confirmed from disassembly)

```c
void PatternRowsBlit(u8 *ctx, u16 *p1, u16 p2, u16 p3, u8 p5, u8 p6) {
    // sl=ctx, r7=(u16)p2 then W, r6=(u8)p5 then i, r9=(s16)p3, r8=(s8)p5
    // 16B frame: [sp,0]=p1, [sp,4]=(u16)p3, [sp,8]=(u8)p6, [sp,12]=y<<16
    if ((s16)p3 < 0) return;
    if ((s16)p3 >= (s8)FlagA_8680(ctx)) return;
    if ((s16)p2 < 0) { p5 = (u8)((s8)p5 + (s16)p2); p2 = 0; }
    bound = (s16)p2 + (s8)p5;              // r4, r8=(s8)p5 set here
    if (bound >= (s8)FlagA_8628(ctx))     // second call inside
        p5 = (u8)(FlagA_8628(ctx) - p2);
    if ((s8)p5 <= 0) return;
    W = 0xB000;
    if (p6 == 2 && (((p3-1)>>1)&1)) W = 0xC000;
    else if (p6 == 3) W = 0xC000;
    dst = GetPtr(ctx) + (((s16)p3 << (s8)flag) << 1) + (y<<16 >> 15);  // y*2
    for (i=0; (s16)i < (s8)p5; i++) {
        SetIfXZero(dst, W | *p1++, 0);
        dst++;
    }
}
```

Notable details decoded during W33:
- The `(s16)p3 < 0` check uses `cmp r3, #0` — the pre-`mov r9,r3` value. The compiler
  computed (s16)p3 in r3, copied to r9, but the first compare uses r3.
- `dst` offset uses a two-step shift: `lsls r1,r0` then `lsls r1,r1,#1` (i.e. `(x<<f)<<1`,
  NOT `x<<(f+1)` — no `adds` present).
- The `y*2` term is `(s32)(y<<16) >> 15` via `asrs r0,r1,#15` — the frame slot holds `y<<16`.
- Loop increment is the u16 shift-first idiom: `(i<<16)+0x10000` then `lsrs`/`asrs` for
  (u16)(i+1)/(s16)(i+1); `movs r1,#128; lsls r1,#9` materializes 0x10000.
- `p1` is reloaded/stored to `[sp,#0]` every loop iteration (memory local, not register).

## Variant history (W33: 3 new C variants; 7 total with W32's 4 — bar met)

- **v5 (245 diffs)**: Pure C, no asm prologue. Pins sl/r9/r8/r6 (NO r7 pin), separate u32
  locals. Prologue `push {r4-r7,lr} / mov r7,sl / mov r6,r9 / mov r5,r8 / push {r5,r6,r7}`
  MATCHED except `sub sp,#12` (need #16). But init sequence diverged (y7→r5, pp→r7).
- **v6 (245 diffs)**: v5 + `register u16 y7 __asm__("r7")`. WORSE prologue (`sub sp,#8`);
  gcc ignored/conflicted the r7 pin (used r7 for pp). Confirmed r7 pin unworkable.
- **v7 (203 diffs)**: v3's asm prologue (perfect 44B) + body reordered to ROM's exact op
  order (h8=(s8)h6 moved to bound computation at ROM 0x8007040; ysh before bound).
  Improved from 211 but wall holds.
- **Transcription (0 diffs)**: dis2asm2.py from `staging/wave32_B/dis_06fe8.txt`. 126 insns,
  7 labels, 6 `bl`s to matched symbols. Stripped `.globl`+`.set` per landing hygiene
  (real build T/A symbols); coordinator links against the real build.

## Walls (why C failed)

1. **r7 pin vs Thumb frame pointer**: gcc hardcodes r7 as the Thumb fp. Explicit
   `__asm__("r7")` pins conflict — gcc either miscompiles (uses r7 as stk base without
   setup, probe2) or ignores the pin (v6). The "never pin r7" idiom is confirmed
   load-bearing. Without the pin, gcc allocates p2 to r5 and pp to r7 (v5) — the
   reverse of ROM.
2. **Opaque-asm dataflow distrust**: After the asm prologue block, gcc does not know
   values are already extended, so `if (p3s < 0)` (p3s pinned to r9) generates
   `mov r1,r9; lsls r0,r1,#16; cmp r0,#0` instead of ROM's `cmp r3,#0`. Pinned outputs
   are distrusted (cf. W32 idiom: plain asm outputs trusted, pinned distrusted).
3. **Fine-grained scheduling**: ROM's init interleaves p3/p5/p6 processing
   (`lsls r3,r3,#16` ... `lsls r0,r0,#24` ... `lsrs r0,r3,#16`) and the body has
   specific store scheduling (`str r5,[sp,#12]` placed after the FlagA_8628 call).
   C cannot reproduce this scheduling.
4. **Memory-local p1**: ROM reloads/stores p1 via `[sp,#0]` each loop iteration.
   Pure C keeps pp in a register (r7). Forcing it to the frame requires the explicit
   `stk[0]` store/load pattern, which then conflicts with other allocation.

## New idioms / confirmations

- **r7 pin is unusable on Thumb** (strengthens "never pin r7"): causes miscompile or
  silent ignore. If a function uses r7 for a variable, prefer asm prologue or transcription.
- **Prologue reproducibility**: Pure C CAN generate the
  `push {r4-r7,lr} / mov r7,sl / mov r6,r9 / mov r5,r8 / push {r5,r6,r7} / sub sp,#N`
  pattern when the function uses r4-r7 + r8/r9/sl (v5 matched it except the `sub` size).
  The `sub` size follows from the actual stack locals (12 vs 16).
- **`(x<<f)<<1` vs `x<<(f+1)`**: Two consecutive `lsls` (variable then `#1`) with no
  intervening `adds` means the C was `(x << f) << 1`, not `x << (f+1)`.

## Staged files

- `staging/wave33_A/w33a_08006fe8_asm.c` — **MATCHED transcription** (0 diffs).
- `staging/wave33_A/w33a_08006fe8_v5.c` (245), `w33a_08006fe8_v6.c` (245),
  `w33a_08006fe8_v7.c` (203) — C attempts.
- `staging/wave33_A/w33a_08006fe8_v3baseline.c` — W32 v3 re-verified (211).
- `staging/wave33_A/verify_v5.sh` — verify harness (adapted from W32-B).
- `staging/wave33_A/dis2asm2.py` — transcription tool copy.
- `staging/wave33_A/probe*.c/.s/.o/.i` — prologue/allocation probes (scratch).

## For the coordinator

Landing `w33a_08006fe8_asm.c`: file-scope `__asm__`, section `.text.w33a_08006fe8_asm`,
global `PatternRowsBlit_08006FE8`, `.thumb_func`. No `.set` symbols (all 5 callees are
MATCHED in the build). Needs a Makefile rule compiling with agbcc main (the `__asm__`
block assembles via `as`; no C code involved, so compiler choice is flexible, but keep
main for consistency). Append MATCHED row to `docs/match_status.tsv` (append-only).
