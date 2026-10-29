# Wave 12 Worker C — Match Notes (bulk leaves-up layer)

Layer: 39 candidates (docs/wave12_layer.tsv), all pure leaves (n_bl=0), ordered by caller count.
Matched: 5. Attempted: 9. Blocked: 4.

## New Idioms (verified byte-identical via harness)

### 1. Tied-opaque pool load prevents constant folding
`__asm__ volatile("": "=r"(v): "0"(CONST))` forces a literal pool `ldr` instead of
the compiler synthesizing the address via `movs`/`lsls` (e.g. `0x02000EC0+9` folded
to `0x02000EC9`; `0x020070F0+0x152` folded to `0x0002F1C2`).

### 2. Pin + tied-opaque (not pin + initializer) forces pool ldr into a register
`register unsigned short *q __asm__("r0") = (unsigned short *)0x020031E0;` made the
compiler synthesize via `movs`/`lsls` instead of a pool load. Using a tied-opaque
temp then assigning to the pinned register forces the `ldr r0, [pc, #off]`.

### 3. Non-empty asm is honored by old_agbcc; empty is ignored
`__asm__ volatile("add %0, %1, #0": "=l"(p): "l"(addr))` forces `ldr r0, [pc]` +
`adds r3, r0, #0` (a copy barrier). Note: `"=l"` constraint is required — `"=r"`
picked hi register r8 and failed to assemble.

### 4. Offset-first addressing: `*(u8*)((u32)i + (u32)q)` vs `q[i]`
`q[i]` yields `adds r0, r4, r1` (base-first); `*(u8*)((u32)i + (u32)q)` yields
`adds r0, r1, r4` (index-first). The operand order in the source controls the
`adds` operand order.

### 5. In-place `addr += const` (addr opaque) yields accumulate form
With `addr` from tied-opaque, `addr += 0x11AE` yields `ldr r1, [pc]; ldr r0, [pc];
adds r1, r1, r0` (load const, add) rather than synthesizing.

### 6. Duplicated stores in both branches defeat tail-merge
Writing `*q = u;` in BOTH the if and else branches (with branch-local `u`)
triggers the compiler's tail-merge to produce ROM's `bne; ldr; b; movs r0, #0;
strh; strh` shape. Hoisting `u = 0` before the if produces different code.

### 7. Switch case order FF, FE, FD gives ROM's bne-style layout
`case 0xFF:` first (with `r = 3`), then `0xFE`, then `0xFD` produces the exact
`cmp; bne; movs; b` chain. Different order changes the branch structure.

### 8. Explicit trailing pad instead of GAS 46c0
`__asm__(".section .text.w12c_<addr>,\"ax\",%progbits\n.byte 0, 0\n.previous")`
emits `00 00` padding. Relying on alignment produces `46 c0` (mov r8, r8).

### 9. `short` loop counters produce ROM's (s16) shift idiom
`short i = 0; do { ... i++; } while (i <= 27);` yields `lsls r1, #16; asrs r0,
r1, #10` style sign-extension. `int` counters produce different code.

### 10. `j = 0;` as assignment (not initializer) fixes movs scheduling
`short j; j = 0;` (assignment after `p` computation) yields `movs r3, #0` at the
ROM's position. `short j = 0;` (initializer) schedules it differently.

### 11. `(u8)(a+1)` via shifted-add idiom
old_agbcc emits `lsls r0, #24; movs r1, #0x80; lsls r1, #17; adds r0, r1; lsrs
r2, #24` for `(unsigned char)(a + 1)`. The `0x80<<17 = 0x1000000` (not 0x10000).

### 12. Branch-local `u = t; u |= *q` with pinned regs controls adds placement
`register unsigned short t __asm__("r1");` + tied-opaque `t = 0xFFFF`, then
`u = t; *(p+20) |= u;` yields the exact `ldr r1; mov r0, r1; ldrh; orrs; strh`
sequence. Using `t` directly in the OR produces different register allocation.

## Corrections to func_stats.tsv / assumptions

- `0x80 << 17 = 0x1000000`, not 0x10000. The `(u8)(a+1)` in 0x08002C74 uses
  `(a<<24) + (1<<24)` then `>>24`.
- ROM pool at `0x80499d4` is `0x020070F0` (bytes `f0 70 00 02`), not `0x0002F070`.
  Always verify pool words with `od`, never trust the disassembler's guess.
- ROM constant at `0x800cd20` is `0xC7FF` (bytes `ff c7 00 00`), not `0xFFC7`.
- `func_stats.tsv` sizes often EXCLUDE trailing pools. True sizes (to next real
  code): CD00:56, 2C74:60, 499AC:64, C4B4:68, FBA4:76, 2D20:100, 2678:108,
  5338:104, 2620:72, 48B4:84.
- `sub_0802660C`'s recorded offset is 4 too high; real code starts `0x08002668`.

## Blocked: precise diffs

### 0x0802FBA4 (76 B, 2 callers) — register allocation
ROM:
```
push {r4, r5, lr}          ; uses r5!
...
b==0 branch:
  movs r0, #0xb4; lsls r0, #1   ; r0 = 0x168
  adds r2, r3, r0               ; r2 = p + 0x168 (dest)
  lsls r1, r4, #2               ; r1 = c*4
  movs r5, #0xa8; lsls r5, #1   ; r5 = 0x150
  adds r0, r3, r5               ; r0 = p + 0x150
  adds r0, r0, r1               ; r0 += c*4 (src)
  ldr r0, [r0]; str r0, [r2]
b!=0 branch:
  movs r5, #0xc2; lsls r5, #1   ; r5 = 0x184
  adds r2, r3, r5               ; r2 = p + 0x184 (dest)
  lsls r1, r4, #2               ; r1 = c*4
  subs r5, #24                  ; r5 = 0x16c
  adds r0, r3, r5               ; r0 = p + 0x16c
  adds r0, r0, r1               ; r0 += c*4 (src)
```
Mine (best attempt): `push {r4, lr}` (no r5); branch0 uses r2 for 0x150, dest in
r0; c-normalize via `lsls r1, #24; lsls r2, #24; lsrs r4, r2, #24` matches ROM's
entry. Remaining diffs: byte 0 (0x10 vs 0x30: push), bytes 16-17 (movs r1 vs
movs r0, lsls r1 vs lsls r0). The `subs r5, #24` in branch1 suggests C of form
`off = 0x184; *(p+off) = *(p+off-0x18+cc*4)`, but branch0 uses separate constants
(0x168, 0x150) not `off-0x18`. Inconsistent; compiler chose r5 for offset temp.

### 0x080225B4 (42 B, 1 caller) — register allocation
ROM keeps `a<<16` in r0 throughout: `lsls r0, r0, #16` at entry, then uses r0
for both `(r0>>24)` and `& 0x00FF0000`. Mine saves a to r3 first (`adds r3, r0,
#0; lsls r3, r3, #16`) because the table lookup result goes to r0, forcing a
to move. Need C structure where table value goes to r3, not r0.

### 0x0804A450 (56 B, 1 caller) — pool scheduling
ROM: `push {r4,lr}; ldr r1, [pc] (=0x0200BD20); ldr r3, [pc] (=0x02002EE0); ...`
(both pools upfront). Mine: loads 0x02002EE0 first, then 0x0200BD20 later (after
early return). The `ldrsh r0, [r1, r4]` with `movs r4, #0` WAS achieved via
`int i = 0; ((short *)q)[i]`. Need to hoist both pool loads before the early
return.

### 0x0804C2CC (48 B, 1 caller) — non-standard convention
Uses r4/r5 as inputs without saving (`ldrb r1, [r4, #18]`, `ldrb r0, [r5,
#16]`). Called via `bl` from 0x0804C2FC. Either interior fragment sharing
caller's registers, or custom calling convention. Not matchable via standard C.
