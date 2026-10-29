# Wave 29-B Match Notes (Worker B, 0x0801C030 + 0x0801C428)

Worker B, 2026-10-23. Staging: `staging/wave29_B/` (C sources, verify.sh harness).
Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` before starting.

Registry check: 0x0801c030 and 0x0801c428 both IN-REGISTRY as BLOCKED (revisits,
not claims). No duplicates. No skips.

## MATCHED (1)

### 0x0801C030 — ChipState_0801C030 (216 B true extent, 0 diffs) ✅

**True extent correction:** 216 B (0xd8), not 214 B. Function: 0x801c030–0x801c104
(code), pad 0x801c106, next function at 0x801c108. Pools inline at 0x801c0d8/0xdc/0xe0
(3 words: 0x0822688b, 0x08226894, 0x08226887).

**Compiler:** main agbcc. Staged: `staging/wave29_B/w29b_0801c030_MATCHED.c`.

**Evidence:** `./verify.sh 0x0801c030 216 .text.w29b_0801c030 w29b_0801c030_MATCHED.c main`
→ `sizes: o=1172 elf=4992 bin=216`, `rom extract: 216 bytes`, `diffs: 0`.
Clean-room recompile → linked at true ROM address with custom .ld → objcopy →
cmp vs baserom extract at file offset 0x1c030, exact 216 bytes, 0 diffs.

**Key techniques (new idioms):**
1. **r6 zero-index via live-reg pressure:** For `ldrsh r3,[r3,r6]` with `movs r6,#0`,
   keep ALL low regs (r0-r4) live at the load point. gcc then cannot use a dead
   low reg for the zero index. However, gcc's cost model prefers `ldrh`+sign-extend
   over `movs r6,#0`+`ldrsh` when no low reg is free. Solution: inline asm
   `__asm__ volatile("movs r6, #0\n\tldrsh %0, [%1, r6]" : "=r"(d) : "r"(t1) : "r6")`
   with s32 output/param to avoid post-asm sign-extension (see #2).
2. **s32 laundering for asm outputs:** When inline asm produces a sign-extended
   s16 via `ldrsh`, declare the C variable and extern param as `s32` (not s16).
   This prevents gcc from emitting `lsls/asrs` sign-extension after the opaque asm.
   Same ABI (32-bit in register); coordinator restores u16/s16 at landing.
   (Precedent: s16-extern-params idiom, but inverted — use s32 to suppress extension.)
3. **In-place shift via dead value:** `u32 sh = (u32)vv << 3;` where vv is dead
   after gives `lsls r4,r4,#3` (in-place reuse). Assigning back to u8 (`vv <<= 3`)
   gives weird `lsls r0,r6,#27; lsrs r6,r0,#24` (correct but not ROM).
4. **Adds operand order via addition commutativity:** `b = ((u8 *)(u32)vv)[(u32)p1]`
   (i.e., `*(vv + p1)`) gives `adds r0,r4,r0`; `b = p1[vv]` (i.e., `*(p1 + vv)`)
   gives `adds r0,r0,r4`. Write the addition with the desired Rn first.
5. **Pool-load ordering via `+r` barrier:** `__asm__ volatile("" : "+r"(tbl))`
   forces the literal pool load at that point. Combine with live-reg analysis to
   control the destination register.
6. **Zero-fill section padding:** GAS pads Thumb sections with `46c0` (mov r8,r8)
   by default, but ROM uses `0000`. Fix with file-scope asm:
   `__asm__(".section .text.NAME\n.align 2, 0\n.previous");`
7. **Pinned r0 for address-then-load:** `register u32 a35 __asm__("r0") = (u32)(sp+35);`
   `__asm__ volatile("ldrb %0, [%0]" : "+r"(a35));` gives `ldrb r0,[r0]` (in-place).
8. **Tail `++sp[19]` in compare:** `if (++sp[19] != ...)` gives `ldrb/adds/strb`
   then later `lsls/lsrs`, matching ROM's order (strb before shifts).

**Full case-1 ROM sequence matched:**
```
ldr r0,[pc] / ldrb r4,[r5,#19] / adds r0,r4,r0 / ldrb r1,[r0]
adds r0,r5,#0 / adds r0,#35 / ldrb r0,[r0] / lsls r2,r0,#28 / lsrs r2,r2,#28
ldr r0,[pc] / lsls r4,r4,#3 / adds r3,r4,r0
movs r6,#0 / ldrsh r3,[r3,r6]  (via asm)
adds r0,#4 / adds r4,r4,r0
movs r6,#0 / ldrsh r0,[r4,r6]
str r0,[sp,#0] / ldr r0,[r5,#44] / str r0,[sp,#4]
movs r0,#2 / bl ChipInit
... tail matches ...
```

**Name:** ChipState_0801C030 (chip state dispatch on s[13], sibling of 0x0801bf10).

## BLOCKED (attempted)

### 0x0801C428 — ChipFxTick_0801C428 (280 B true extent, 171 diffs best, was 177)

Chip FX state machine. True extent 280 B (278 code + 2 pad @ 0x801c53e).

**What matches:** Prologue, switch dispatch, `(s8)--p[18]` countdown, nibble via
`((u32)*q<<28)>>28` + barrier, call-2/call-3 sequences, pools.

**Progress:** Eliminated the `mov r8,r2` / `mov r2,r8` save/restore around call-1
(via inline asm for a1's load). Call-1 now has `movs r5,#0; ldrsh r3,[r3,r5]`
(correct!) without the r8 save. 171 diffs with old_agbcc (vs 177 baseline).

**Remaining wall (precise):** Call-1 register allocation for idx/base.
ROM:
```
801c470: 7cf1 ldrb r1,[r6,#19]  @ idx -> r1
801c472: 00c8 lsls r0,r1,#3     @ idx*8 -> r0
801c474: 1901 adds r1,r0,r4     @ base -> r1 (reuse!)
801c476: 2500 movs r5,#0
801c478: 5f4b ldrsh r3,[r1,r5]  @ a1 -> r3
```
Mine (v1g, best):
```
7cf1 ldrb r1,[r6,#19]  @ idx -> r1 ✓
00cb lsls r3,r1,#3     @ idx*8 -> r3 (WRONG, should be r0)
191b adds r3,r3,r4     @ base -> r3 (WRONG, should be r1)
2500 movs r5,#0        ✓
5f5b ldrsh r3,[r3,r5]  @ a1 -> r3 ✓, but base should be r1
```

The `base = t1 + idx*4` computation goes to r3 instead of reusing r1.
Tried: block-scoped `register int idx1 __asm__("r1")` (idx→r1 ✓), eliminating
`base` variable, `=l` constraint, pinning a1→r3. gcc stubbornly uses r3 for the
shift/base instead of r0/r1.

**Tried:**
- v1a: pin zero→r5 (ignored due to const-prop)
- v1b: inline asm `movs r5,#0; ldrsh` with s32 a1 (got `ldrsh r3,[r3,r5]` ✓,
  eliminated r8 save!)
- v1c: pin idx→r1 function-wide (broke call-2 with `ldrsh ip` assembler error)
- v1d/v1e: block-scoped idx1→r1 (idx→r1 ✓, but base→r3)
- v1f: pin a1→r3 (dest correct, but base still r3)
- v1g: eliminate base variable (no change)
- old_agbcc on v1g: 171 diffs (vs 173 main)

**Staged:** `staging/wave29_B/w29b_0801c428_v1g.c` (171 diffs, best),
plus v1a-v1f.

**For coordinator:** The idx/base allocation (r1/r0 vs r3) is the last wall for
call-1. Call-2/call-3 also need work (they have different save/restore patterns).
The inline-asm + s32 idiom from 0x0801C030 works for the ldrsh itself; the
remaining issue is purely gcc's register choice for the address computation.

## New idioms discovered

1. **s32 laundering for asm outputs:** When inline asm produces a value via a
   sign/zero-extending load, declare the variable and extern param as s32 to
   prevent gcc from emitting redundant extension after the opaque asm.
2. **Zero-fill section padding:** File-scope `__asm__(".section NAME\n.align 2, 0\n.previous")`
   forces `0000` padding instead of GAS's default `46c0` Thumb nop.
3. **In-place ldrb via pinned r0:** `register u32 a __asm__("r0") = (u32)(sp+35);`
   `__asm__ volatile("ldrb %0, [%0]" : "+r"(a));` gives `ldrb r0,[r0]`.
4. **Adds order via operand position:** `*(a + b)` gives `adds Rd,Ra,Rb` where Ra
   is the first operand; swap to flip.
5. **Block-scoped register pins are safe for r1/r2/r5/r6** (unlike r7 which breaks
   prologue function-wide). Used successfully for qq→r1, ii→r2 in 0x0801C030 tail.

## Tooling
- `staging/wave29_B/verify.sh` — hardened harness (tolerant of short builds
  during iteration; strict for final claims).
- `staging/wave29_B/w29b_0801c030_MATCHED.c` — MATCHED source (0 diffs).
- `staging/wave29_B/w29b_0801c030_v4*.c` — iteration history (v4..v4z).
- `staging/wave29_B/w29b_0801c428_v1*.c` — blocked attempts.
- `staging/wave29_B/rom_0801c428.bin` — ROM extract.

## Summary for coordinator
- **MATCHED:** 0x0801C030 (ChipState_0801C030, 216 B, main agbcc, 0 diffs).
  Staged at `staging/wave29_B/w29b_0801c030_MATCHED.c`.
  Needs registry claim + landing. Note: uses inline asm (2 places) + s32 param
  (coordinator restores u16/s16 at landing); file-scope asm for zero-fill padding.
- **BLOCKED:** 0x0801C428 (171 diffs best, was 177; call-1 r8 save eliminated,
  `movs r5,#0; ldrsh r3,[r3,r5]` achieved; remaining wall is idx/base r1/r0 vs r3).
- **Progress:** 1/2 targets matched. 0x0801C030 was the primary target and is done.
