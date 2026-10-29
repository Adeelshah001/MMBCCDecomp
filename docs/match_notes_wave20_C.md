# Wave 20 Worker C — Match Notes (blocked revisits)

## Matched (7)

| Address | Name | Size | Compiler | Idiom |
|---------|------|------|----------|-------|
| 0x0801d2c8 | F_0801D2C8 | 62 | main+FIXALIGN1 | Sibling-shape transfer + u32 pin to r4 |
| 0x0801e14c | SlotCopy_0801E14C | 40 | old_agbcc | Pinned-barrier scheduling (pool before ldrb) |
| 0x080173d4 | TblSlotInit_080173D4 | 40 | old_agbcc | Pinned-barrier scheduling (twin of 0801e14c) |
| 0x0801787c | SlotClear_0801787C | 44 | old_agbcc | Pinned-barrier scheduling + prologue |
| 0x0804a450 | F_0804A450 | 68 | main | Pool-control: dual barrier for upfront pools |
| 0x0803e9bc | F_0803E9BC | 96 | main | Pool-control: nested-if + goto body |
| 0x08047cc0 | sub_08047CC0 | 36 | main | Dead-reg reuse: pin off->r3, reassign to 0 |

All 7 verified 0-diff: recompile → link at true ROM address → objcopy
extract → cmp vs baserom, full extents including pools; .o/.elf/.bin/ROM
extract all non-empty; exact byte counts.

## Per-function detail

### 0x0801d2c8 — F_0801D2C8 (62 B, main+FIXALIGN1)
Node_PopAndInit(0,1,0,12) wrapper with type = a ? 6 : 5. Sibling-shape
transfer from w19c_08017620.c (ChipInit family). The "descending alloc"
(a→r7,b→r6,c→r5,type→r4) was reproduced by copying the sibling shape
verbatim. The r4/r5 swap (d vs type) was fixed by pinning
`register u32 type __asm__("r4")` — a u32 pin to an already-saved
callee-saved reg is safe (unlike the wave-19 r7 pin which miscompiled).
Key: `type = 6; if (a == 0) type = 5;` gives ROM's 6-first layout
(movs r4,#6; cmp; bne; movs r4,#5).

### 0x0801e14c — SlotCopy_0801E14C (40 B, old_agbcc)
ROM: `ldr r1,[pc]` (pool 0x082243D8) BEFORE `ldrb r2,[r4,#9]`. The
pinned-constant + empty-asm barrier idiom (wave-19) forces the order:
`register u32 base __asm__("r1") = 0x082243D8;` +
`__asm__ volatile("" : "+r" (base));` before the ldrb. Also needed:
pin idx→r2, explicit `off` temp for `lsls r0,r2,#2`, `(off + base)`
operand order for `adds r0,r0,r1`, and moving `s[12]=4` before the
dereference to get `ldr r0,[r0]`. Pool word 0x082243D8 (wave-15 note
had typo 0x082243D4). Section 40 B: 34 code + 2 pad + 4 pool.

### 0x080173d4 — TblSlotInit_080173D4 (40 B, old_agbcc)
Twin of 0x0801e14c pattern. ROM: `ldr r2,[pc]` BEFORE `ldrb r3,[r0,#9]`.
Same pinned-barrier idiom with base→r2, idx→r3. Then `s[12]=1`,
`p=p[1]`, `s[20]=p`, `s[10]&=254` inline, `bl F_173FC`. 40 B: 36 code
+ 4 pool (no pad needed).

### 0x0801787c — SlotClear_0801787C (44 B, old_agbcc)
Same scheduling pattern as 0x0801e14c. Prologue:
`DecIfNonZero_18(*(s+44)); *(s+44)=0;` then the pinned-barrier table
lookup. 44 B: 38 code + 2 pad + 4 pool.

### 0x0804a450 — F_0804A450 (68 B, main)
Pool-control: ROM loads BOTH pools upfront (`ldr r1`, `ldr r3` before
the early-return beq). Forced with dual-operand barrier:
`__asm__ volatile("" : "+r" (tbl), "+r" (flag));` + pin tbl→r1.
The `movs r0,#1` before `ldrb` uses pinned-constant barrier +
accumulator `&=` idiom (`one &= *flag` gives `ands r0,r2`).
The `&=` tail needed volatile pointer to force the redundant
`ldrh r0,[r3,#2]` (volatile prevents dead-load elimination):
`volatile u16 *pv; u16 v=*pv; u16 m=0xFFFD; m&=v; dummy=*pv; *pv=m;`
gives ROM's `ldrh r0; ldr r1; ands r1,r0; ldrh r0; strh r1`.
68 B: 56 code + 12 pool (3 pools).

### 0x0803e9bc — F_0803E9BC (96 B, main)
Pool-control + structure. ROM branch: `cmp #0; beq L_zero; cmp #1;
beq L_body; b L_ret; (pool 0x469d); L_zero: ...`. Achieved with:
```c
if (v != 0) {
    if (v == 1)
        goto body;
    goto ret;
} else {
    Sub_080475D4();
    (*p)++;
}
body:
```
The explicit `goto body` gives `beq L_body` (not `bne`). Pool1 dumps
after the `b L_ret` per the pool-control rule. `(*p)++` gives
`ldrb; adds #1; strb` (not `movs #1; strb`). CopyHdr_Dispatch takes
`&dummy` (stack slot, `sub sp,#4; mov r0,sp`). 96 B: 88 code + 8 pool
(pool1 mid-function at +0x18, pools 2/3 at end).

### 0x08047cc0 — sub_08047CC0 (36 B, main)
Scheduler: ROM hoists `movs r3,#0` above the first `strb` by reusing
the dead r3 (0x46b4 offset). Achieved by pinning
`register u32 off __asm__("r3") = 0x46B4;` then `off = 0;` BEFORE
the store: `u8 *p = s + off; off = 0; *p = v; ... s[5] = (u8)off;`
gives `ldr r3; adds r1,r0,r3; movs r3,#0; strb r2,[r1]; ... strb r3,[r0,#5]`.
The `u8 z` local approach (wave-4) forces `push {r4,lr}` — worse.
36 B: 32 code + 4 pool.

## Blocked revisits (still blocked)

### 0x08002e80 — sub_08002E80 (84 B)
Complex volatile function (DISPCNT save/restore + palette copy).
The pp pool (`ldr r2,[pc]`) hoists above `mov r1,sp; mov r0,sp`;
ROM has it after. Tried memory barrier — insufficient (PC-relative
constant load not treated as memory access for barrier). Needs
a different approach to pin the load down (or force it via tied asm).
Parked.

### 0x08016d2c — sub_08016D2C (116 B)
50 diffs (was 26). Head now matches: `adds r2,r0,#0` (s→r2),
`ldr r1,[pc]` before `ldrb r4,[r2,#9]`, `lsls r0,r4,#2`,
`adds r0,r0,r1` via pinned-barrier + r4 pin + old_agbcc.
Tail diverges at the 0x020031E4 pool (goes to r4, ROM wants r1).
The `register ... __asm__("r1")` pin for the pool base was ignored.
Needs a working r1 pin or different structuring. Good progress;
not yet matched.

## New idioms / refinements

### Pinned-barrier for pool-load-before-ldrb (generalized)
The wave-19 pinned-constant idiom generalizes to pool loads:
`register u32 base __asm__("rX") = POOL;` +
`__asm__ volatile("" : "+r" (base));` before the ldrb forces
`ldr rX,[pc]` above `ldrb`. Proven on 3 functions (0801e14c,
080173d4, 0801787c). Combine with idx pin + explicit `off` temp
+ `(off + base)` operand order for the full table-lookup pattern.

### u32 pin to saved callee-saved reg is safe
Wave-19 said "pinning actively harmed codegen" and "never pin r7".
Refinement: pinning a u32 to an ALREADY-SAVED callee-saved reg
(here r4, in the push set) is safe and effective. The r7 problem
was specific (agbcc uses r7 without pushing).

### Volatile forces redundant loads
If ROM has a seemingly-redundant load (e.g. `ldrh` between `ands`
and `strh`), the source may use a `volatile` pointer — volatile
prevents dead-load elimination, preserving the redundant access.

### Dead-register reuse via pin + reassign
To get `movs r3,#0` hoisted above a store by reusing a dead
register: pin the dead value's register
(`register u32 off __asm__("r3")`), then reassign (`off = 0;`)
BEFORE the store statement. The compiler emits the zeroing early,
reusing the pinned register.
