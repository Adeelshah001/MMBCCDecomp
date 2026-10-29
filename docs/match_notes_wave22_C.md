# Wave 22 Worker C notes — blocked revisits with clobber-reservation idiom (2026-10-23)

## Matched (2)

### 0x08011A78 (80 B) — F_08011A78, main agbcc + explicit `.short 0x0000` pad
State-init with TableWalk_080113F4 call. Parked by w20-B (59 diffs, AND
operand order), deferred by w21-D (49–61 diffs, pinned r1/r2/r6).

Solution shape:
- `q` pinned r1, but later uses go through `p->f0` (not `q`), so ROM's
  `ldrb r1,[r1,#10]` (kill q) + `ldr r1,[r4,#0]` reload fall out naturally.
  (Pinning q AND using it later kept it live, forcing the temp to r3.)
- `eight` (r6) initialized AFTER `*r2 = z` for ROM's `movs r5`/`movs r6` order.
- 78 B code + 2 B zero pad: trailing nop replaced via explicit
  `.short 0x0000` (linker-padding pad idiom; sed inserts after the unique
  `bx r1` line in the Makefile rule).
- Callee TableWalk_080113F4 is matched/global → plain extern, no `.set`
  (hygiene: stripped per nm-hygiene rule).

Landed: `mmbcc/src/w22c_08011a78.c`, Makefile rule (main agbcc + pad sed),
ldscript slot at 0x08011A78. Full-build region 0-diff (80/80).

### 0x08016D2C (128 B) — sub_08016D2C, old_agbcc
Blocked by w15-C2 (26 diffs: r2=s allocation not reproduced; pinning broke).

Solution shape:
- Entry `adds r2,r0,#0; adds r3,r2,#0; adds r3,#124` falls out of natural C
  (`u8 *q = s + 124` with `s` used afterwards).
- **Clobber-reservation** denies r4+r0 for the tbl pool pseudo (-> r1) and
  r4 for the tab2 pool pseudo (-> r1):
  `__asm__ volatile("" : : "r"(tbl) : "r4", "r0")`.
- Tied empty asm `__asm__ volatile("" : "+r"(ti))` keeps the `int ti = b`
  copy (`adds r0,r1,#0`) before the signed clamp compare (`cmp r0,#3; ble`).
- `int m = -13` forces `movs r1,#13; negs r1,r1` mask materialization
  (not `movs r1,#0xF3` from u8 narrowing).
- Pool 3 is **0x020031E4** (EWRAM table), read from ROM bytes — the disasm
  decode (`adds r1,#228`) misleads; always verify pools from bytes.
- Word stores (`str` not `strb`) for s[12], s[20], s[108].
- 116 B code + 12 B trailing pool (3 pools at +0x74/+0x78/+0x7C).

Landed: `mmbcc/src/w22c_08016d2c.c`, Makefile rule (old_agbcc, no sed),
ldscript slot at 0x08016D2C. Full-build region 0-diff (128/128).
Neighbor after is ObjInit_08016DAC (matched); neighbor before is unlanded
(zeros in build, no overlap).

## Blocked revisits (refined)

### 0x0804BDE0 — ListWalk_0804BDE0 (48 B): tst wall CONFIRMED
Attempt: natural C with `u8 v` (solves `orrs r1,r0` order). 32 diffs, single
root cause: `ands r0,r1; cmp r0,#0` vs ROM `tst r0,r1` (cascades branch
offsets; mine 48 B code vs ROM 46 B + 2 pad). No `tst` precedent exists in
any matched object; this GCC's thumb backend lacks a tst combine pattern
(ARM-only). Needs inline-asm or other vintage. Staging:
`staging/wave22_C/w22c_0804bde0_p1.c`.

### 0x08010F34 — already MATCHED by Wave 22-D
`Entry_TryActivate_08010F34`, 84 B, main agbcc. Skipped per registry check.
(Uses inline asm for the bit test + pinned r1/r2 — see w22d_08010f34.c.)

### 0x0804AF20 — sub_0804AF20 (112 B): 68 diffs (was 73)
**New idiom found**: explicit u16-increment
`t = ((u32)i << 16) + 0x10000; i = t >> 16;` (from w16b_08025754.c)
produces ROM's `lsls/movs r5,#128/lsls r5,#9/adds/lsrs` + 0x10000
materialization. Also achieved: r8 save/restore (`mov r7,r8; push {r7}`),
b->r2 correct.
Resists: a/c/d register rotation (mine a->r8,c->r7,d->r6 vs ROM
a->r7,c->r6,d->r8); 0x10000 hoisted before loop vs ROM inside; clobber
denying r5 for d moves d->r6 not r8. Staging:
`staging/wave22_C/w22c_0804af20_p5.c` (best).

### 0x08002CB0 — sub_08002CB0 (112 B): 31 diffs (was not attempted)
Pools are INSIDE the 112 B extent (w20 thought 78 B). Structure matches
(76 code + 2 pad + 32 pool). Resists: prologue scheduling (q-pool load
early vs late, mask in r1 vs r0, spv=0 store early vs late) and pool order
(q-pool before mask-pool vs after). 8 variants tried. Staging:
`staging/wave22_C/w22c_08002cb0_p1.c` (best).

### 0x08002E80 — sub_08002E80 (84 B): 4 diffs (was 53)
Progress: `&disp`-twice form gives ROM's `mov rX,sp` pattern; pp assigned
inside OR fixes pool-load order; clobber denies r4 for DISPCNT (->r3) +
explicit dp for order. Resists: r1/r4 swap for disp-store-addr vs pp0-load
(mine `mov r4,sp`/`ldrh r1` vs ROM `mov r1,sp`/`ldrh r4`). Staging:
`staging/wave22_C/w22c_08002e80_p6.c` (best).

## New idioms for catalog

1. **Kill-and-reload via re-derivation** (0x08011A78): if ROM kills a pointer
   in a load and reloads it later, write later uses via the base expression
   (`p->f0`) not the variable, so the variable dies and the temp reuses its
   register.
2. **Explicit u16 increment** (0x0804AF20): `t = ((u32)i << 16) + 0x10000;
   i = t >> 16;` produces the `lsls/movs #128/lsls #9/adds/lsrs` pattern.
   (Found in w16b_08025754.c; generalizable.)
3. **Tied-asm to preserve a copy** (0x08016D2C): `__asm__ volatile("" :
   "+r"(x))` prevents the compiler from forwarding a variable into its use,
   preserving a redundant `adds` copy.
4. **Int mask variable for movs+negs** (0x08016D2C): `int m = -13` forces
   `movs r1,#13; negs r1,r1`; a u8 context narrows to `movs r1,#0xF3`.
5. **Verify pools from bytes, not disasm** (0x08016D2C): objdump decodes
   pool words as instructions; always `dd`/`od` the pool bytes.
6. **`&var`-twice for double `mov rX,sp`** (0x08002E80): `*(volatile u16
   *)&disp = *(volatile u16 *)&disp & K;` emits two `mov rX,sp` (one per
   `&`); the `&=` form emits one.

## Registry
- MATCHED rows appended for 0x08011a78, 0x08016d2c (checked for duplicates first).
- BLOCKED rows appended for 0x0804bde0, 0x0804af20, 0x08002cb0, 0x08002e80
  (append-only, history preserved).
