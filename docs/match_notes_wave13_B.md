# Wave 13 Worker B (TAG=B) — Task_3AFFC Callees — Match Notes

Worker: Wave 13 specialist (TAG=B). Date: 2026-10-22.
Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` before start.
Toolchain: `mmbcc/tools/agbcc/bin/agbcc` (main; old_agbcc tried where noted);
`arm-none-eabi` 2.42 (present).
Harness: `staging/wave13_B/mk.sh` (copied from wave12_A; hardened non-empty
assertions, file offset = addr − 0x08000000, full extent incl pools, `cmp -l`).
Final verification: `staging/wave13_B/verify_final.sh` (clean rebuild from .c).
Staging: `~/workspace/mmbcc-decomp/staging/wave13_B/` (NEVER delete).
Results: `docs/wave13_B_results.tsv`.

**Result: 3 MATCHED, 0 BLOCKED.** All three Task_3AFFC callees from wave12_A
are now byte-for-byte identical.

## Target 1: sub_0800BEE0 @ 0x0800BEE0 (100 B) — MATCHED as SyncObjFlagBits_BEE0

Behavior: `void (u16 a, u8 b)` on object at 0x02004F40. If
`*(u16*)(base+20) == a` return; else `*(u16*)(base+6) = a`, then:
- `b == 128`: `base[9] = (base[9] & 3) | 128; base[10] &= ~7;`
- `b > 128`: `base[10] |= 8`; else `base[10] &= ~9`; then
  `base[10] = (base[10] & ~7) | 4`.

Final: `staging/wave13_B/w13b_0800bee0_final.c` (main agbcc).

### Decisive idioms

1. **Pinned r0 accumulator, mask as target.** `register int m __asm__("r0");`
   with `m = 3; m &= base[9];` etc. makes the mask materialize first
   (`movs r0,#imm` [`; negs r0,r0`]) and the AND/OR accumulate into r0
   (`ands r0,rX` / `orrs r0,rX`), matching ROM's mask-first order. Writing
   `base[9] = (base[9] & m) | 128` instead puts the result in the load
   register — the target must be the pinned var.
2. **`|128` constant substitution defeated by asm materialization.** The
   compiler replaces the constant 128 with any register known to hold 128
   (here b3 in r3, via the `b3 == 128` branch), emitting `orr r0,r0,r3`.
   Empty-asm laundering of b3 and `int o = 128` locals do NOT defeat it.
   Fix: `register int o __asm__("r1"); __asm__ volatile("mov %0, #128" : "=r"(o));`
   then `m |= o;` → `movs r1,#128; orrs r0,r1`. (The `|-128` neg-fold from
   wave12 probes does not trigger in this shape.)
3. **r6 loads via dead prologue var.** ROM does two of the `ldrb [r2,#10]`
   loads into r6. Reusing the dead prologue `register u16 v __asm__("r6")`
   (`v = base[10]; m &= v;`) routes them to r6.
4. **Prologue** carried over from wave12 v12: `(u32,u32)` params + explicit
   shifts in statement order, `vs` pinned r1, pool 0x02004F40 mid-function
   (GAS dumps it after the branch barrier — matches ROM placement).
5. **Tail pad:** `.s` post-processing — append `\t.align\t2, 0` after
   `.size`. GAS 2.42 pads the 98-B section with `46c0` (`mov r8,r8`); the
   explicit align makes it emit ROM's `00 00`.

## Target 2: sub_080241F8 @ 0x080241F8 (176 B) — MATCHED as TblGetByte_241F8

Behavior: `u8 (u16 a)` dispatch on `a >> 12`:
- `a == 0` → 200
- case 1: `GetByte1_25A08(p + p[432] * 144)`, `p = *(u8 **)0x020070A4`
- case 2: if `(a & 0xFFF) == 0` → same as case 1;
  else `GetByte1_26554((void *)0x020070A8, a & 0xFFF)`
- case 3: `*(u8 *)(0x082298F0 + (a & 0xFFF) * 20 + 1)`
- case 4: `*(u8 *)(0x020070CC + 1)`
- default → 200
Cases 1/2 `(u8)`-truncate the callee result at the join
(`lsls/lsrs r0,#24`).

Final: `staging/wave13_B/w13b_080241f8_v3.c` → renamed
`w13b_080241f8_final.c` (main agbcc).

### Decisive idioms

1. **Pinned prologue registers (the wave12 "fatal" blocker).**
   `register u32 aa __asm__("r0") = a; aa = (aa << 16) >> 16;` forces the
   in-place truncation (`lsls r0,r0,#16; lsrs r0,r0,#16`); then
   `register u32 idx __asm__("r1"); idx = aa >> 12;` forces
   `lsrs r1,r0,#12` instead of the fused `lsr r0,r0,#28`. (Wave12's probe of
   pinned regs "failed" only because the surrounding C shape was wrong.)
2. **Signed switch.** `switch ((int)idx)` — the dispatch uses `bgt`, not
   `bhi`. (Original: `switch (a >> 12)` on u16 promotes to signed int.)
3. **Pinned case temps.** Case 1/2: `p`→r0, `k`→r1 (`movs r1,#216;
   lsls r1,r1,#1`), `q`→r2 (`adds r2,r0,r1`), `x`→r3 (`ldrb r3,[r2]`),
   then `k = (x << 3) + x; k <<= 4;` for the `*144` shift-add.
   Case 2: `m`→r1 (`ldr r1,=0xFFF; ands r1,r0`); the 26554 call needs no
   r1 setup (CSE from the `ands`); callee declared `(void *, u32)` to avoid
   a spurious s16 conversion.
4. **Case-3 ldr/pool order.** `__asm__("" : "+r"(base))` barrier forces the
   `ldr r2,=0x082298F0` before `ldr r1,=0xFFF`, which also orders the pool
   words base,mask as in ROM.
5. **Case-4 anti-fold.** `((u8 *)0x020070CC)[1]` folds the +1 into the pool
   (0x020070CD). Barrier on the pointer (`__asm__("" : "+r"(q))`) keeps the
   pool at 0x020070CC with `ldrb r0,[r0,#1]`.
6. **Tail pad:** same `.align 2,0` append as BEE0 (176 B is 4-aligned).

## Target 3: sub_08024384 @ 0x08024384 (174 B) — MATCHED as TblGetByte_24384

Near-twin of 241F8. Confirmed ROM differences: callees 0x08025A0C /
0x080265B0, cases 3/4 use `ldrb [r0,#0]`, default `movs r0,#50`.
Adapted directly from the 241F8 v3 shape; matched on first build.

Final: `staging/wave13_B/w13b_08024384_final.c` (main agbcc).

Tail pad: 174 B is not 4-aligned; GAS pads the section to 176 with `c046`.
Mid-function `.align 2,0` pool directives force section alignment back to 4,
so the `.align 1` trick (cf. 4D7A0) does not apply. Truncation per wave11_B
precedent: assert tail is pad-only `c046`, truncate to 174, compare.

## .s post-processing (assembler-version compensation)

All three need one documented `.s` tweak because GAS 2.42's section padding
(`mov r8,r8` / `46c0`) differs from the ROM toolchain's (`movs r0,r0` /
`0000`):
- BEE0, 241F8: append `\t.align\t2, 0` after `.size` → 2 bytes of `00 00`.
- 24384: truncate `c046` pad after asserting pad-only (wave11_B precedent).

These are mechanical, reproducible steps in `verify_final.sh`; the `.c`
sources are the real deliverables.

## What's still open

- Task_3AFFC itself remains blocked downstream (its other callees, incl.
  sub_0800B148, belong to other workers).
- The `.set` symbol aliases (GetByte1_25A08 etc.) assume the coordinator's
  final symbol names; adjust at integration.
