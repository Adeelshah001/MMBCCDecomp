# Wave 6 Batch L3 Match Notes (2026-10-20)

15/16 matched (all old_agbcc). 1 blocked (0x0804B980).

## Verification correction applied
Per coordinator notice: L2 harness had false-MATCHED bugs (quoted section
pattern `*(".text...")` matching nothing → empty .bin; dd skip using ROM
address instead of file offset → empty baserom extract; `cmp -s` on two
empty files = false match). All L3 claims re-verified with strict harness
(`/tmp/wave6_l3/verify_one.sh`): asserts .o/.elf/.bin/rom-extract ALL
non-empty (prints sizes), baserom offset = addr - 0x08000000, compares
exactly NBYTES, `cmp -l` sanity check. All 15 re-verified 0 diffs.

## New idioms

### Volatile-asm adds/subs to defeat LICM + constant folding (Sram_VerifySlot @0x08001DB8)
Need `adds r1, r4, #0; subs r1, #32` inside an if-block, where compiler
hoists `p4-32` out of the loop (LICM) and folds `(p4-32)+40` into `p4+8`.
Empty `__asm__ volatile("" : "+r"(p))` does NOT block it in old_agbcc.
Working idiom: emit the real instructions opaquely with a pinned output:
```c
register u8 *p __asm__("r1");
__asm__ volatile ("add %0, %1, #0\n\tsub %0, %0, #32"
                  : "=r" (p) : "r" ((u8 *)p4));
```
NOTE: GAS in Thumb mode rejects `adds`/`subs` mnemonics in inline asm
("instruction not supported in Thumb16 mode"); use `add`/`sub` (no 's') —
agbcc itself emits the s-less form and GAS assembles it to the flag-setting
encoding (verified: `add r1, r4, #0` → 0x1c21, `sub r1, r1, #32` → 0x3920).

### Nested-if vs &&-chain placement (Sram_VerifySlot)
ROM computes `p = p4 - 32` immediately after the FIRST check (`*p4 ==
magic`), before the `[12]`/`[15]` checks. A single `if (A && B && C)`
places the computation after all three. Source shape is nested:
```c
if (*p4 == magic) {
    /* p = p4 - 32 via asm idiom above */
    if (((u8 *)p4)[12] == 0 && ((u8 *)p4)[15] == 1 && *(u32 *)(p + 40) == key)
        return 1;
}
```

### Local u32 declaration defeats u16 zero-extension (Gfx_Blit3 @0x08042EC0)
Real `Gfx_BlitRequest` is `(u32, u16, u16, u8, u8)` but ROM has no
`lsls/lsrs #16` on r1/r2. Declare locally as
`void Gfx_BlitRequest(u32, u32, u32, u32, u32);` (same idiom as
wave5_g2.c). Also: assign second table to a local (`tB = ...`) immediately
before its call so the compiler emits `ldr r1, [pc]` BEFORE the `ldrb`
(ROM order); a direct `((u32 **)gTbl)[*p]` loads the byte first.

### `ldrsb` register-offset form (Gfx_Blit3)
`movs r1, #4; ldrsb r1, [r5, r1]` comes from plain `((s8 *)base)[4]`
with old_agbcc — no special source shape needed.

### Magic is a counter, not a pointer (Mem1_AllocInit @0x0804CD70)
`*p += 1` with `p` as `u32 **` emits pointer arithmetic (`adds r0, r1,
#4`). ROM does `adds r0, r1, #1`: declare `p` as `u32 *` (the magic word
at `*(0x03007FF0)` is a u32 counter). Pool magic is `0x68736D53`
(verified from ROM bytes; earlier notes guessed 0x08046D53 — wrong).
`0x80000000` via literal gives `movs r0, #128; lsls r0, #24` as needed.
Zero-fill loop is `if (cnt) { do { *d=0; cnt--; d+=0x50; } while (cnt); }`
(pre-test + do-while; the pre-test is not dead-code-eliminated).

### Duplicate/interleaved literal pools (Task_3AF98 @0x0803AF98)
ROM interleaves pool words with code (one pool group per if-block) and
duplicates `0x020070F0`/`0x4698` across the v==8 / v==9 blocks. old_agbcc
reproduces this layout naturally when each block uses a SEPARATE extern
(`gEwram_020070F0_A` vs `_B`, `gOff_4698_A` vs `_B`, each `.set` to the
same value). Register pinning needed: `off`/`p`/`q`/`o` pinned to r1/r0
to get `ldr r1; adds r0, r4, r1; ldrb r0, [r0]` and
`ldr r0; adds r1, r4, r0; movs r0, #imm; strb r0, [r1]` shapes. Else block
uses the `u8 z = 0;` idiom (`movs r1, #0` first, then `movs r0, #1`).

## Blocked: Mem1_TaskChain @0x0804B980 (106 B)
Structure (from disasm): magic check + `bx lr` BEFORE any stack frame;
then `push {r4-r7,lr}`, save of r8/r9/sl/fp + r0, `sub sp, #24`; VCOUNT
(`0x04000006`) byte math; two indirect calls via `bl 0x0804BDA2` (2-byte
`bx r3` stub, r3 = fn ptr); multiply-accumulate; tail `bx r3` to IWRAM
`0x03000001` (no epilogue). Natural C produces a simple `push {lr}`
frame and `_call_via_r3` thunks — nowhere close. Needs heavy inline asm
(pinned-r3 stub calls, noreturn tail jump) or targeted RE. Saved draft:
`/tmp/wave6_l3/Mem1_TaskChain_0804b980_v2.c` (incomplete).
