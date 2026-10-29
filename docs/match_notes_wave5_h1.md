# Wave 5 Batch POOL-H1 — Match Notes (worker)

Date: 2026-10-20. Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946`
(read in place, never copied). Toolchain: `mmbcc/tools/agbcc/bin/agbcc` (main) /
`old_agbcc` at `-O2 -mthumb-interwork`, exact project build rule. Verification:
link each `.o` section at its ROM address (absolute `.set` symbols), `objcopy -O
binary --only-section`, byte-diff vs baserom. Scratch: `/tmp/wave5_h1/` (probes
`p*.c`, `build.sh`, `verify.py`).

Result: **3 MATCHED, 7 BLOCKED, 20 NOT ATTEMPTED** (time).

Staged C for the 3 matches is in `/tmp/wave5_h1/` (`pbb78d.c`, `pd568b.c`,
`p9380i.c`); coordinator to land into `mmbcc/src/` (do NOT copy baserom).

## MATCHED

### 0x0800bb78 — TableCall_BB78 (52 B: 44 code + 8 pool) — agbcc
Indirect call through ROM tables, guarded by s16 != -1.
```c
void TableCall_BB78(u8 *s) {
    s16 v = *(s16 *)(s + 0x14);
    u32 *tbl;
    s8 idx;
    if (v != -1) {
        tbl = gTbl_081731A0;          // 0x081731A0
        idx = gTbl_0817313C[v];       // 0x0817313C, (s8) sign-extend
        ((void (*)(u8 *))tbl[idx])(s); // via _call_via_r1
    }
}
```
Key: declaring `tbl`/`idx` as locals (assigned inside the if) gives ROM's
register allocation (s in r3, v in r2) and pool order (0x081731a0 before
0x0817313c). The `-1` uses runtime negation (`movs r0,#1; rsbs r0,#0`).
`.set`: gTbl_0817313C=0x0817313C, gTbl_081731A0=0x081731A0,
_call_via_r1=0x0804DCD0.

### 0x0800d568 — ListIterate_D568 (46 B) — agbcc
Linked-list iteration with InitLinkedNode setup; calls fn pointer at node+0x14
for each node until back to s+0x14 sentinel.
```c
void ListIterate_D568(u8 *s) {
    u8 *p;
    u8 *end;
    InitLinkedNode(s);                       // 0x0800440C
    p = *(u8 **)(*(u8 **)(s + 0xc) + 4);
    *(u8 **)(s + 0xc) = p;
    if (p != s + 0x14) {                     // literal, not via end var
        end = s + 0x14;
        do {
            ((void (*)(u8 *))*(u32 *)(p + 0x14))(p); // via _call_via_r1
            p = *(u8 **)(*(u8 **)(s + 0xc) + 4);
            *(u8 **)(s + 0xc) = p;
        } while (p != end);
    }
}
```
Key: `if (p != s + 0x14)` with the literal (not `end`) gives ROM's
`adds r1,r4,#0; adds r1,#0x14; cmp; beq; adds r5,r1,#0` (r1 then r5).
`.set`: InitLinkedNode=0x0800440C, _call_via_r1=0x0804DCD0.

### 0x08009380 — TableDispatch_9380 (76 B: 68 code + 8 pool) — old_agbcc
Loop over 6 entries (0x34 stride) at 0x02004CE0; if byte at +0x2c has bit 0,
dispatch via table 0x0817212c indexed by `(v>>6)&0xf` from u16 at +0x2c.
```c
void TableDispatch_9380(void) {
    u16 i = 0;
    s16 j = i;
    u32 *tbl = gTbl_0817212C;   // 0x0817212C, hoisted to r5 before loop
    while (j <= 5) {
        u8 *p = gEwram_02004CE0 + j * 0x34;  // 0x02004CE0
        u8 b = *(p + 0x2c);
        if (b & 1) {
            u16 v = *(u16 *)(p + 0x2c);
            u32 idx = ((u32)v << 22) >> 28;  // (v>>6)&0xf as lsls#22/lsrs#28
            ((void (*)(u8 *))tbl[idx])(p);    // via _call_via_r1
        }
        i = j + 1;
        j = i;
    }
}
```
Key: **old_agbcc** required (main agbcc mis-allocates r0/r1 for the derived
pointers). Declaring `tbl` AFTER `j` (not before) gives ROM's
`movs r1,#0; ldr r5; lsls/asrs` order. The dual `u16 i`/`s16 j` loop vars
reproduce the `(s16)(u16)` truncation pattern. `.set`: gTbl_0817212C=0x0817212C,
gEwram_02004CE0=0x02004CE0, _call_via_r1=0x0804DCD0.

## BLOCKED

### 0x08003154 / 0x080031b8 / 0x0800322c / 0x08003298 — struct-init family
**Blocker: compiler value-reuse optimization vs ROM's fresh runtime negation.**

All four share a prologue calling `sub_08003130` (SetU32_4) then bitfield ops
with runtime-negated masks (`movs rX,#K; rsbs rX,rX,#0` for -0x21, -0x0d, -4,
-0x3f). Both agbcc and old_agbcc perform value-tracking: after `m |= 0x10`
(r0=0x10), `k = -0x0d` becomes `subs r0,#0x1d` (not fresh `movs r0,#0xd;
rsbs`); after `k = -0x0d`, `k = -4` becomes `adds r1,#9` (not fresh).
~12 variants tried: literals, two-statement `k=0xd;k=-k`, block-scoped
separate vars (gives fresh negation but 8 live values → high-reg spill for
a/b), initializers vs assignments. The ROM's compiler does NOT do this
optimization. Best probe (`/tmp/wave5_h1/p3154c.c`): 52/100 diffs.

Precise diff for 0x08003154 (mine vs ROM):
- `+42..+46`: mine `subs r0,#0x1d; ands r2,r0; ands r1,r0` vs ROM
  `movs r0,#0xd; rsbs r0,r0,#0; ands r2,r0; ands r1,r0`
- `+58..+62`: mine `subs r0,#0xc` (from 0x8) vs ROM `movs r0,#4; rsbs r0,r0,#0`
- Pool for `0xfffffe00` mask: mine materializes `0xfe00` via `movs+ lsls`
  (compiler narrows u16 `&`), ROM pool-loads full `0xfffffe00`.

The 0x080031b8 variant additionally parks 3rd arg in r8 (register pressure
from double-`ands` temp); 0x0800322c/0x08003298 differ in tail stores
(0x100 halfwords, `|3` vs `&-4|1`).

### 0x0800288c — CpuFastSet/LZ77 wrapper (64 B)
**Blocker: register allocation (arg copies, v reload).**

ROM: `adds r2,r0,#0; adds r3,r1,#0` (BOTH args copied at start, s→r2, a→r3);
`ldrh r0,[r2,#4]; cmp r0,#0` (v NOT saved); else-branch reloads v via
`ldrh r2,[r2,#4]; lsrs r2,r2,#2`. Mine: only s copied (r3), v saved to r2,
pools in r2/r3 (ROM uses r1 for both). ~6 variants tried (arg locals,
if-condition forms, old_agbcc). The dual arg-copy + v-reload pattern not
reproduced. Best: `/tmp/wave5_h1/p288cb.c` (30/68 diffs).

### 0x08017d50 — ObjInit_TypeC? (100 B + 16 pool)
**Blocker: `ands` destination register in idx computation.**

ROM idx calc:
```
movs r1,#3; ldrb r0,[r0]; ands r1,r0; adds r0,r1,#0; cmp r0,#3; ble; movs r1,#3
```
Mine (best, `/tmp/wave5_h1/pidx4.c` fragment): `ldrb r0,[r0]; movs r1,#3;
ands r0,r1` — dest r0, ROM wants dest r1. The `3 & byte` with byte in r0
and mask in r1 consistently gives `ands r0,r1` on both compilers; ROM's
`ands r1,r0` not reproduced (~8 variants: `3&b`, `b&3`, `m&=b`, u8/u32 types,
old_agbcc). Full function also needs the `s[0x45]` RMW order
(`r2=s+0x45; r1<<=2; mask; r0&=r3; r0|=r1`).

This idx pattern (`(gRom_081705B0>>4)<<1` → `gEwram_020031E4[]` → `&3` →
clamp) appears in ALL 15 ObjInit-family functions (0x08017d50–0x08020d54);
cracking the `ands` dest unlocks the family.

### 0x080129f8 — dual-path table dispatch (62 B)
**Blocker: else-branch register allocation.**

ROM else-branch:
```
ldr r0,[pc] (tbl); ldrb r3,[r1,#2]; ldrb r4,[r1]; adds r1,r3,r4; ...
```
(v2 in r3, v in r4, tbl loaded FIRST). Mine: `ldrb r0,[r1,#2]; ldr r2,[pc];
ldrb r1,[r1]` (v2 in r0, tbl second, v in r1; no r4 → `push {lr}` not
`push {r4,lr}`). The tbl-first + r3/r4 allocation not reproduced (~5
variants). Best: `/tmp/wave5_h1/p129f8b.c` (26/68 diffs).

## NOT ATTEMPTED (20)
Time. The 15 ObjInit-family functions (0x08017e6c, 0x080186f4, 0x08019090,
0x0801abe4, 0x0801acf4, 0x0801ae00, 0x0801aef4, 0x0801afe4, 0x0801b3ac,
0x0801b6c4, 0x0801b81c, 0x0801bc04, 0x0801d658, 0x0801dad4, 0x0801db9c,
0x08020d54 — note 0x08017d50 attempted/blocked above) share the idx
computation; see blocker. 0x08001db8/0x08001e30 (save-path), 0x08011cd4
(table-copy), 0x08016dac also pending.

## New idioms / observations
1. **old_agbcc for r0/r1 allocation**: 0x08009380 needed old_agbcc (main
   agbcc mis-allocates derived pointers to r0; old_agbcc uses r1 like ROM).
   Extends the old_agbcc catalog to a new function class.
2. **`((u32)v << 22) >> 28` for `(v>>6)&0xf`**: reproduces ROM's
   `lsls r0,r1,#0x16; lsrs r0,r0,#0x1c` exactly (0x08009380).
3. **Dual u16/s16 loop counters**: `u16 i=0; s16 j=i; while(j<=N){...;
   i=j+1; j=i;}` reproduces the `(s16)(u16)` truncation dance
   (`lsls#16; asrs#16` / `lsrs#16`) seen in dispatch loops.
4. **Literal in `if` for r1-then-r5**: `if (p != s + 0x14) { end = s + 0x14;
   ... }` gives `adds r1; adds r1,#0x14; cmp; beq; adds r5,r1,#0`
   (0x0800d568) — the end pointer is computed in r1, then saved to r5.
5. **Value-reuse optimization (blocker)**: both agbcc variants optimize
   `k=-0x0d` after `r0=0x10` into `subs r0,#0x1d`, and `k=-4` after
   `k=-0x0d` into `adds`. The ROM's compiler does fresh `movs; rsbs` each
   time. This is a systematic toolchain difference affecting the 3154
   family; may need a different compiler version or inline asm.

## Recomp-relevant discoveries
- **0x081731a0 / 0x0817313c**: function-pointer table + s8 index table pair
  used by 0x0800bb78 (guarded by `*(s16*)(s+0x14) != -1`).
- **0x0817212c / 0x02004ce0**: 6-entry array (0x34 stride) at 0x02004ce0
  with per-entry dispatch via table 0x0817212c (0x08009380).
- **0x08223d6c**: shared dispatch table for 0x080129f8 (both paths).
- **0x020031e4 / 0x081705b0**: EWRAM byte table + ROM u16 used for the
  ObjInit idx computation (`(u16>>4)<<1` index, `&3` clamp).
- **0x03002420**: WRAM destination base for CpuFastSet/LZ77 in 0x0800288c
  (32-byte strides, matches wave4_h Copy8_28D0 finding).
- **Linked-list pattern** (0x0800d568): nodes with `next` at +4, fn pointer
  at +0x14; `s+0xc` is current node, `s+0x14` is end sentinel; InitLinkedNode
  initializes the list.

## ldscript lines (coordinator)
```
. = 0x0800BB78; .text.tblcall_bb78 : { build/wave5_h1.o (.text.tblcall_bb78); }   /* 52 B incl pools */
. = 0x0800D568; .text.listiter_d568 : { build/wave5_h1.o (.text.listiter_d568); } /* 46 B */
. = 0x08009380; .text.tbldisp_9380 : { build/wave5_h1.o (.text.tbldisp_9380); }   /* 76 B incl pools, old_agbcc */
```
Section sizes include pools; strip gas trailing `c046` if present (none of
the three had non-4-aligned ends). The three matches use distinct `.set`
symbols (no duplicates): gTbl_0817313C, gTbl_081731A0, gTbl_0817212C,
gEwram_02004CE0, InitLinkedNode, _call_via_r1 (all `.set` at end of file per
GAS 2.42 rule; remove when callees matched for real).
