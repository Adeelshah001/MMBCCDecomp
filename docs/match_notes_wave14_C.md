# Wave 14-C Match Notes (TAG=C)

## Summary
- **Matched:** 34 functions (rows 100-199 tiny/small + 4 from 100-124)
- **Blocked:** 12 functions (documented below)
- **Unattempted:** ~128 functions (rows 125-199 remainder + medium subset 292-335)

## New Idioms

### 1. `t = CONST;` as statement (not decl-init)
Controls `movs` placement vs pool loads. When a constant assignment is a separate
statement after opaque base loads, the compiler emits the `movs` after the loads,
matching ROM scheduling. (Used in 0x0800456C.)

### 2. Explicit if/else with uninitialized result var → `bne` layout
Initializing `u32 r = 0` or using early returns gives `beq` layout. Leaving the
result uninitialized and assigning in both branches gives ROM's `bne` fallthrough.
(Used in 0x08011070 FlagInit.)

### 3. `(base - K)` triggers `subs` CSE
Writing `(base - 0x14)` reproduces the compiler's `subs r0,#0x14` instead of a
second pool load for `base+0x...`. The compiler CSEs the subtraction. (Used in
0x08024F88.)

### 4. Callee arity from prologue clobbering
If the first two calls in a sequence don't use r0/r1 (they're clobbered immediately),
they're `void(void)`. Only the later calls that pass args are non-void. Check the
callee's prologue: if it doesn't save/use arg regs, it's void(void). (Used in 0x080429BC.)

### 5. Dead-param extends signal second-vintage — park, don't fight
`adds rX,rY,#0; lsls/lsrs rX` on a parameter that's never used indicates a
second-vintage function (different compiler version). These resist matching;
park them. (0x08024878.)

### 6. Auto-stub `.globl` requirement
Auto-generated stubs need `.globl` (`.set` alone is local and won't satisfy the
external ref) + `.thumb_func` before each `.set`. Fixed in mk.sh.

### 7. Load-before-compute for scheduler
When ROM does `ldr r2,[r4,#4]` BEFORE arithmetic on other regs, the C must load
the variable before the computation, even if they're independent. The scheduler
won't reorder across the sequence. (Used in 0x0802663C: `q = *(u8**)(p+4)` before
`t = w*7; t *= 4`.)

### 8. `(0xD8 << 1)` for 0x1B0
To get `movs r0,#0xd8; lsls r0,#1`, write the constant as `(0xD8 << 1)`, not `0x1B0`.
(Used in 0x080251D8.)

### 9. If/else with duplicated bodies for dispatcher
When ROM has `cmp #0xf8; bhi end; cmp #0xc7; bls L1` with identical bodies, the
source had an if/else with duplicated code. Write it explicitly with the duplication;
old_agbcc keeps them separate. (Used in 0x0802533C.)

### 10. `p[7] & 1` guard with early return 0
Functions that check a flag bit and return 0 early, then allocate and conditionally
init. The `return 0` is `movs r0,#0; b end`, not a shared epilogue. (Used in 0x08022FE4.)

## Blocked Functions (detailed)

### 0x0800B448 (36B, 3 diffs)
Shift-split: `lsls r3,#24` early … `lsrs r3,#20` late, plus pool folding
(0x02004E40+0x24 as separate adds). Tried natural, pinned, asm variants; scheduler
resists the split.

### 0x08024878 (46B, 4 diffs)
Dead 2nd param: `adds r2,r1,#0; lsls/lsrs r2` not reproducible. Second-vintage;
parked.

### 0x08000DC0 (68B, 4 diffs)
Register allocation: ROM keeps `t` in r0 through `lsls r0,#24; lsr r0,#22`, but
compiler puts the final shift in r1. Tried pinning t to r0 (breaks load dest),
combining shifts, splitting. Allocator resists.

### 0x080260D4 (56B, 4 diffs)
Loop init hoisting: ROM does `movs r0,#0; lsls r4,r0,#16; asrs r4,#16` ONCE before
the loop. Compiler puts the extend inside the loop (at the top). Tried do-while,
for, while, goto. Not hoisted.

### 0x08040364 / 0x080437D4 (56B twins, 8 diffs)
`ldrsb r4,[r1,r4]` idiom: ROM does `movs r4,#0; ldrsb r4,[r1,r4]` (indexed by r4=0).
Compiler generates `ldrb r4,[r1]` + separate sign-extend, or `ldrsb r4,[r1]`
(non-indexed). The indexed-with-zero form resists. Twins differ only in pool
(0x082329E0 vs 0x08232D84) and callee (0x08042A64 vs 0x080459F8).

### 0x08043630 (62B, 12 diffs)
Register lifetime puzzle: `v = sub_08005A9c(8)` in r0, then `adds r0,r4,#0` (r0=p),
then `bl sub_0804580C`, then `strb r0,[r2]`. The v appears lost, but ROM stores r0.
Needs investigation of sub_0804580C's r0 behavior.

### 0x08006124 / 0x08006578 (64B twins, 12 diffs)
6-arg wrappers with stack args. My output 76B vs ROM 64B. The stack arg setup
(`str r3,[sp]; str r1,[sp,#4]; str r2,[sp,#8]`) plus extends is 12B over. Twins
differ only in callee (0x08006168 vs 0x080065BC).

### 0x08011170 (68B, 6 diffs)
u16 increment idiom: ROM does `lsls r0,r4,#16; movs r1,#0x80; lsls r1,#9;
adds r0,r0,r1; lsrs r4,r0,#16; asrs r0,#16` (i.e., `(i<<16)+0x10000`). Compiler does
`add r0,r4,#1; lsl r0,#16; lsr r4,#16`. The `(0x80<<9)` materialization resists.

### 0x0803618C (70B, 10 diffs)
Base in r5: ROM keeps 0x0200BCE8 in r5 (callee-saved) across the loop. Compiler
uses r2 (caller-saved) and reloads. Pinning to r5 didn't reduce size (76B vs 66B).

### 0x080052DC (68B, 24 diffs)
Pool offsets: ROM loads 0x11b0, 0x11b1, 0x11b2, 0x11b3 as separate 32-bit pools.
My output 92B vs 68B. The offset materialization differs significantly.

## Unattempted (return to pool)
- Rows 125-199 (75 functions): 0x08009F78, 0x08007378, 0x0801AB94, 0x080363EC,
  0x08002C24, 0x08025A10, 0x080060C4, 0x0800B470, 0x0801CD50, 0x08028900,
  0x0804044C, 0x0802FC70, plus 63 more in rows 130-199.
- Medium subset rows 292-335 (44 functions, 66-160B): 0x0801D308, 0x080266AC,
  0x0803618C (blocked), 0x080047A4, 0x080052DC (blocked), 0x0801112C, 0x0801B91C,
  0x0801CCE0, 0x08007C8C, 0x08034BD4, 0x08007728, 0x0801054C, 0x0804D130,
  0x080110E0, 0x08024BC8, 0x08002960, 0x08002CB0, 0x0800CC24, 0x08017A44,
  0x0801A9F8, 0x0801BBB4, 0x08021498, 0x0801D278, 0x080029B0, 0x0801E990,
  0x080248C4, 0x080008C0, 0x0800D680, 0x08010AD8, 0x08010F34, 0x0804C630,
  0x0800C41C, 0x0802567C, 0x08010308, 0x08009994, 0x0800E994, 0x0800EED4,
  0x0802D3E0, 0x080017A0, 0x080098C4, 0x08045FCC, 0x0801DFC4, 0x080259A4,
  0x0800CC94.

## Progress Bar
████████████████████░░░░░░░░░░░░░░░░░░░░ 34/174 (19.6%) matched
