# Wave 8 Worker R — Match Notes (TAG=R)

Re-derivation of the 13 lost Wave-7-G1 claims, from
`docs/match_notes_wave7_g1.md`. All 13 re-derived and re-verified per the
hardened protocol (non-empty assertions at every step, unquoted `-j`
section pattern, `dd skip = addr - 0x08000000`, full-extent `cmp -l`
including literal pools). ROM SHA-1 verified:
`72309736f3820470c6f372d6a05ad1f16bc5a946`.
C candidates: `staging/wave8_R/*.c`, one section per function
(`.text.w8R_0800xxxx`). Harness: `staging/wave8_R/mk.sh`.

## MATCHED (13)

### Init_080021C4 @ 0x080021C4 (main, 56 B incl pool)
Clears two EWRAM u32 at 0x02002FB0[0] and [50], writes stack-marker
0x11111111, VRAM base (192<<19), 0x85006000 to the IO block at
0x040000D4, returns 0x85006000 via volatile reload. Re-derivation note:
statement order in C must mirror ROM order or the pool order
(first-use: 0x02002FB0, 0x11111111, 0x040000D4, 0x85006000) and the
single `ldr r1,=0x040000D4` break. The `io` pointer is declared in an
inner block *after* the zero-stores and the marker store so its pool
load lands after the `str r0,[sp,#0]`; `volatile u32 *` forces the final
reload that produces the return value. Pool bytes read with `od -t x1`
(LE) — 0x02002FB0 / 0x11111111 / 0x040000D4 / 0x85006000.

### Clr8_08004B94 @ 0x08004B94 (main, 44 B incl pool)
Zeroes 8 bytes at 0x02003668. The u16 counter uses the shift-add-shift
increment `(((i<<16)+0x10000)>>16)` with r4 scratch — no natural C
produces it. Whole loop body in one inline-asm block with pinned
registers (`r3`=base, `r1`=ptr, `r0`=counter, `r2`=zero, `r4` clobbered
→ automatic `push{r4,lr}` / `pop{r4}` / `pop{r0}` / `bx r0` epilogue).
Pre-UAL mnemonics in the asm (`add`/`lsl`/`lsr`, no `adds`; numeric
local label `1:` / `bls 1b`, no `#` on the branch target). The trailing
`base[4] = 0` (strb) is a dead store the compiler keeps. Operand order
care: `"=r"(ctr), "=r"(ptr), "=r"(zero)` are operands 0–2, `"r"(base)`
is operand 3.

### FlagSet_08026F98 @ 0x08026F98 (old_agbcc, 52 B incl pool)
Sets bit 0x1200 in the u16 at 0x020031E0, writes `(x!=0 ? 32 : 0)` to
0x02003670+0x11AC.
- Mask `144<<5` is NOT constant-folded: `u16 v = *p; v |= 144 << 5;
  *p = v;` with old_agbcc gives mask→r3, `adds r1,r3,#0`, ldrh, orr.
- Nonzero test is branchless: `s32 t = (x | -x) >> 31;` → exactly
  `negs/orrs/asrs`; `t &= 32` → `movs r0,#32; ands r1,r0`.
- `u8 x` param: old_agbcc emits the entry `lsls/lsrs #24` extend.
- The second base is declared in an inner block *after* the `strh` so
  its pool load lands after; `__asm__ volatile("" : "+r"(b))` barrier
  with b pinned to r2 keeps `b+0x11AC` unfolded (`ldr r0,=0x11AC;
  adds r2,r2,r0` after the `ands`).

### SubClamp_0802C7B4 @ 0x0802C7B4 (old_agbcc, 40 B, no pool)
Signed saturating subtract: `*p -= (s16)a`, clamp at 0, return u8
borrow = `(u8)((u16)a - t)` when clamped. Critical scheduling detail:
ROM does `lsls r0,r0,#16` first, then `ldrh`, `movs r2,#0`, then
`lsrs r4,r0,#16` / `asrs r0,r0,#16`. Reproduced with split statements
in program order: `int a16 = a << 16; int t = *p; u8 borrow = 0;
u16 ua = (u16)((unsigned)a16 >> 16); int d = t - (a16 >> 16);`.
`int` temporaries (never 16-bit-typed) avoid redundant converts and the
signed→unsigned subtract miscompile; `(s16)d <= 0` gives the
`lsls/cmp/bgt` test. No pool: explicit `static const u16` zero in the
same section supplies the `00 00` pad (linker would otherwise need
alignment bytes).

### Clr36_080475D4 @ 0x080475D4 (main, 44 B incl pool)
Sibling of Clr8: 36-byte clear at 0x0200B7A8 (bound 35 → `cmp r0,#35;
bls`), then `strh` zero to `[4]` (`((u16 *)base)[2] = 0`). Same
whole-loop asm pattern.

### Test_08010454 @ 0x08010454 (old_agbcc, 36 B incl pool)
If `x==1`, `p += 20` (base pool constant 0x02005168); return whether
`p[16] & 2`. The ternary `(p[16]&2) ? 1 : 0` miscompiles branchless
(`lsr/and`) — the `== 0` if/return form is required:
`if ((p[16] & 2) == 0) return 0; return 1;` (needs old_agbcc; main
reorders). Mid-function pool (after the unconditional branch)
reproduces naturally.

### Fill_0802520C @ 0x0802520C (old_agbcc, 36 B, no pool)
Struct `{ u8 *p; u16 a; u16 b; }` init (`s->p = ptr; s->a = n;
s->b = 0;`) plus `0xFF` fill loop: `while (n != 0) { *ptr++ = 0xFF;
n--; }` reuses param regs (`adds r3,r1,#0`, r2 as u16 counter with
`subs/lsls/lsrs` decrement). old_agbcc avoids the spurious `push{lr}`
main emits for this shape.

### Append_0802526C @ 0x0802526C (old_agbcc, 36 B, no pool)
`if (s->b >= s->a) return 1; s->p[s->b] = v; s->b++; return 0;`
reproduces the `bcs`, the reloaded `s->b` for index and increment, and
the `movs r0,#0; b; movs r0,#1` join exactly.

### Set_08004E24 @ 0x08004E24 (old_agbcc, 32 B incl pool)
`p[0] = (x << 7) | 64;` then the movs-first ternary shape:
`v = 2; if (x == 0) v = 1; p[2] = v;` — the `(x!=0)?2:1` form generates
cmp-first codegen vs ROM's `movs r1,#2` first. At 0x02004F80.

### Cmp_08004E0C @ 0x08004E0C (old_agbcc, 24 B incl pool)
`if (p[1] == x) return 1; else return 0;` with `u8 *p =
(u8 *)0x02004F80`. Two lessons: writing `0x02004F80 + 1` as an integer
constant folds into the pool (0x02004F81) — a pointer plus `[1]` index
keeps 0x02004F80 in the pool with `ldrb r1,[r1,#1]`; and the if/else
(not bare ternary) gives ROM's `beq`-to-`movs#1` / `b`-over shape.

### Clr_0800B4C8 @ 0x0800B4C8 (main, 28 B incl pool)
`p[19] &= -m9; p[19] &= -m17; p[8] = 0xFF;` at 0x02004E40. The masks
must come from negated *variables* (`int m9 = 9; p[19] &= -m9;`) —
literal `-9` folds to `movs #247`. agbcc merges the two `&=` into one
load, two `ands` (`movs+negs` each), one `strb`.

### Clr_08010478 @ 0x08010478 (old_agbcc, 32 B incl pool)
If `x==1`, `p += 20` (pool 0x02005168); `p[16] &= -m2;` with
`int m2 = 2;` (literal `-2` would fold to `movs #254`); `return 1;`.

### Zero_0801052C @ 0x0801052C (old_agbcc, 32 B incl pool)
`u8 *p = (u8 *)0x02004CA0;` zero `p[28]` if nonzero, `p += 32`, zero
`p[28]` (= original p[60]) if nonzero. Straightforward.

## New idioms / re-derivation lessons
- Pool constants: read with `od -t x1` (LE bytes); `-t x2` prints LE
  numeric values and misreads (bit twice on 0x02002FB0/0x040000D4).
- Integer constant arithmetic on addresses (`0x02004F80 + 1`) folds at
  compile time into the pool word — use pointer+index (`p[1]`) to keep
  the base unfolded with an immediate offset.
- Ternary `? 1 : 0` on a bit-test goes branchless under old_agbcc;
  the if/return or if/else form preserves the branchy ROM shape.
- Scheduler prologues: split 16-bit extends into separate statements
  in program order (`a16 = a<<16; …; ua = …; d = t - (a16>>16);`) to
  reproduce interleaved `lsls/ldrh/movs/lsrs/asrs` schedules.
- Re-derivation is cheap when the recipe records the *why* (register
  allocation, pool order, fold hazards), not just the final C.
