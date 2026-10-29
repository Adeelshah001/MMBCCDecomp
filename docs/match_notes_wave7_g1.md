# Wave 7 Batch G1 — Match Notes (TAG=G1)

79 functions, leaves-up SMALL layer (<40 bytes), all n_bl=0 (no calls).
Worker verified ROM SHA-1 72309736f3820470c6f372d6a05ad1f16bc5a946 before start.
Harness: /tmp/wave7_g1/mk.sh (custom linker script per build — the default
ld script merges `.text.*` into `.text`, silently breaking `-j` extraction;
this was caught by the non-empty assertions).

## MATCHED (15)

### Init_080021C4 @ 0x080021C4 (main, 56 B incl pool)
Clears two EWRAM u32s at 0x02002FB0[0] and [50], writes stack-marker
0x11111111, VRAM base (192<<19), and 0x85006000 to IO block at 0x040000D4,
returns 0x85006000 (via volatile reload). Pool order follows first-use.
Lesson: od `-t x2` prints LE numeric values — read pool bytes with `-t x1`
to avoid misreading constants (twice misread 0x02002FB0/0x040000D4).

### Clr8_08004B94 @ 0x08004B94 (main, 44 B incl pool)
Zeroes 8 bytes at 0x02003668 with u16 counter using the shift-add-shift
increment idiom (((i<<16)+0x10000)>>16, r4 scratch). No natural C produces
it (`i++`, `i=i+1`, `(u16)(i+1)` all give adds-then-truncate). Solution:
whole loop body in one inline-asm block with pinned registers
(r3=base, r1=ptr, r0=counter, r2=zero, r4 clobbered → push{r4,lr}).
Pre-UAL mnemonics in asm (`add` not `adds`, etc.). The `p[4]=0` after the
loop is a dead store the compiler keeps.

### FlagSet_08026F98 @ 0x08026F98 (old_agbcc, 52 B incl pool)
Sets bit 0x1200 in u16 at 0x020031E0, writes (x!=0?32:0) to
0x02003670+0x11AC. Key findings:
- Mask `144<<5` NOT constant-folded by agbcc; `u16 v=*p; v|=144<<5; *p=v;`
  with old_agbcc gives the exact shape (mask→r3, move to r1, ldrh, orr).
- Nonzero test uses branchless `(x|-x)>>31` idiom: `s32 t=(x|-x)>>31;`
  gives `negs/orrs/asrs` exactly. `x?32:0` and `-(x!=0)` are branchy.
- Address kept unfolded via `__asm__ volatile("":"+r"(b))` barrier on the
  base; b pinned to r2 so poolB loads before the idiom and the add
  (`adds r2,r2,r0`) lands after the `ands`.

### SubClamp_0802C7B4 @ 0x0802C7B4 (old_agbcc, 40 B)
Signed saturating subtract: `*p -= (s16)a`, clamp at 0, return u8 borrow.
Critical: use `int` temporaries (`int t=*p; int d=t-a;`) — 16-bit typed
variables cause the compiler to emit redundant `lsl/lsr` converts or to
optimize the signed subtract to unsigned. `(s16)d<=0` gives the `lsls/cmp/bgt`
test. Explicit `00 00` pad needed (no pool; linker emits `c0 46`).

### Clr36_080475D4 @ 0x080475D4 (main, 44 B incl pool)
Sibling of Clr8: 36-byte clear at 0x0200B7A8 (bound 35), then `strh` zero
to [4]. Same whole-loop asm pattern.

### Test_08010454 @ 0x08010454 (old_agbcc, 36 B)
If x==1 use base+20 (0x02005168), return `(p[16]&2)?1:0`. Mid-function pool
(after unconditional branch) reproduced naturally. The `==0` formulation
needs old_agbcc (main reorders).

### Fill_0802520C @ 0x0802520C (old_agbcc, 36 B)
Struct init (ptr/u16/u16) + `0xFF` fill loop reusing param regs (r3=ptr,
r2=counter). old_agbcc avoids the spurious `push{lr}` that main emits for
this loop shape.

### Append_0802526C @ 0x0802526C (old_agbcc, 36 B)
Buffer append: `if (s->b >= s->a) return 1; s->p[s->b]=v; s->b++; return 0;`

### Set_08004E24 @ 0x08004E24 (old_agbcc, 32 B)
`p[0]=(x<<7)|64; p[2]=(x==0)?1:2;` at 0x02004F80. The ternary must be
written as `v=2; if(x==0) v=1;` — the `(x!=0)?2:1` form generates
cmp-first codegen vs ROM's movs-first.

### Clr_0800B4C8 @ 0x0800B4C8 (main, 28 B)
`p[19] &= -9; p[19] &= -17; p[8]=0xFF;` at 0x02004E40. The `-9`/`-17` must
come from negated *variables* (`int m9=9; p[19]&=-m9;`) — literals fold to
`movs #247` instead of ROM's `movs+negs`.

### Clr_08010478 @ 0x08010478 (old_agbcc, 32 B)
If x==1 p+=20 (0x02005168); `p[16] &= -2; return 1;`

### Zero_0801052C @ 0x0801052C (old_agbcc, 32 B)
Zero `p[28]` and `p[60]` (via `p+=32`) if nonzero, at 0x02004CA0.

### Cmp_08004E0C @ 0x08004E0C (old_agbcc, 24 B)
`return (*(u8*)(0x02004F80+1) == x) ? 1 : 0;`

## BLOCKED (7)

### Check_0800B2B4 @ 0x0800B2B4
2-byte diff: ROM `ands r0,r1; cmp r0,#0`, mine `ands r1,r0; cmp r1,#0`.
Compiler destroys dead r1 in the second mask test; ROM preserves it.
Tried: main/old/-O1/-Os, operand swap, named temp, fake asm use (too
invasive — adds push{lr}), `if(v&128)` vs `if((v&128)!=0)`.

### Clr20_0804B310 @ 0x0804B310
Scheduler order: ROM does `lsls/lsrs` (a1 trunc) BEFORE `adds r3,r0`;
mine reverses them. Tried main/old, reordered C, pinned r4.

### crt0_thumb_helpers @ 0x080002DC
Context-switch helper (saves r8-r11, `str sp,[r3]`, `mov lr,r1`,
`mov sp,r2`, restores). Hand-written asm; needs `.s` implementation,
not C.

### Init_08000CA8 @ 0x08000CA8
Regalloc: ROM pool→r3/zero→r2; mine swapped. Pinned regs cause
spurious `push{lr}`. Tried main/old.

### Tst_0800B2D8 @ 0x0800B2D8, Tst_0800B2F0 @ 0x0800B2F0
Same family as Check_0800B2B4: ROM loads pool→r1 then mask→r0 with
`ldrb r1,[r1,#4]` reuse; mine uses pool→r0. Tried main/old.

### Avg_080110B0 @ 0x080110B0
Regalloc: ROM uses r4 for `(x>>1)+(y>>1)` sum (needs `push{r4,lr}`);
mine reuses registers, no push. Tried main/old, reordered loads.

## New idioms found
- `(x|-x)>>31` branchless nonzero→mask (old_agbcc and main).
- `int m=9; x &= -m;` to force `movs+negs` instead of folded `movs #247`.
- `v=2; if(x==0) v=1;` vs ternary for movs-before-cmp scheduling.
- Whole-loop inline asm with pinned regs for shift-add-shift u16
  increments (no natural C works).
- Barrier `__asm__ volatile("":"+r"(b))` to keep `base+const` unfolded,
  with pinning to control load placement.
- `int` temporaries to avoid 16-bit conversion artifacts in signed
  subtract/compare sequences.
- C89: declarations must precede statements (agbcc rejects mixed).
  Inner `{ }` blocks allow fresh declarations.
- Section pad: explicit `static const u16 pad=0` ONLY when no literal
  pool exists; the pool's `.align` already emits `00 00`. If the linker
  still pads with `c0 46`, the section is oversized — drop the pad var.
- Custom linker script required: default ld merges `.text.*` into
  `.text`, breaking `-j` extraction (caught by non-empty assertions).
