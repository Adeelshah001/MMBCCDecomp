# Wave 15-C2 Match Notes (TAG=C2)

Worker: TAG=C2. 10 MATCHED, 2 BLOCKED, 18 UNATTEMPTED.
All MATCHED verified with old_agbcc -O2 -mthumb-interwork via hardened protocol.
C sources in /tmp/wave15_C2/f_*.c (one section per function, .text.w15c2_<addr>).

## MATCHED

### 0x0804D7C0 MaskWrite23_0804D7C0 (110B)
Guards on `*(u32*)(s+52)==0x68736D53` (pool word, shared cmp/store).
Increments the guard word, then loops over `n=s[8]` object slots at `*(s+44)`,
stepping 0x50 per slot with a `mask=1<<=1` bitmask. Per slot: if `(a&mask)` and
`(p[0]&0x80)`, writes `p[23]=b`; if the b-copy is 0, calls sub_0804D7A0(p).
Idioms: pinned r6=rs, sl=ra(u32), r8=rb(u32), r9=rv(u32); inline-asm prologue
for exact `adds r6,r0,#0; lsls/lsrs r1,#16; mov sl,r1; lsls/lsrs r2,#24; mov r8,r2`
order (scheduler paired the extensions otherwise); `register u32 am __asm__("r0")=ra`
+ `am &= mask` gives `mov r0,sl; ands r0,r7`; `(0x80 & p[0])` operand swap for
`movs r0,#0x80` before `ldrb`; do-while with `if(n>0)` guard for `ble`+`bgt`
layout; `u32 v` temp for `v+1` single-`adds`.

### 0x0804D834 MaskWrite25_0804D834 (110B)
Byte-identical twin of 0x0804D7C0 except `strb [r4,#25]` vs `[r4,#23]`.
Same C with offset changed.

### 0x08011A0C FlagApply_08011A0C (108B)
Reads s8 values at `p[6]`, `p[7]` (p=`*(s8**)s`, via `ldrsb`). If >0 calls
`FlagBit_Set_11D68((u16)v,1)`; else if <0 calls `FlagBit_Set_11D68((u16)(-p[6]),0)`
(note: re-reads p[6], does not reuse v). Then `s[4]++`, zeros s[5..7],
returns -1 as `movs r0,#0; subs r0,#1`. Idioms: `register u8 t __asm__("r1")`
for the increment (ROM uses r1); `int zero=0` local with `t=s[4]+1; zero=0;
s[4]=t;` ordering to get `ldrb/adds/movs/strb` sequence; `return zero-1`.

### 0x0801A6AC ObjInit_0801A6AC (110B)
Wave-5 family: `ChipSlot_Setup(s,594,0)` (pool 0x252), `ChipSlot_IncUse(s,0)`,
then `idx=(*(u8*)((((*((u16*)0x081705B0)>>4)<<1)+(u32)(u8*)0x020031E4))&3`
with `if(c>3) idx=3` via `register int c __asm__("r0")` + `movs` asm;
`*p=(*p&-13)|(idx<<2)` at s+0x45, `s[0x22]=13`, four u32 zeros at s+88/96/92/100,
`SetBit16(*(s+44),3)`, `Text_SelectBlobIdx(0xa3)` (return discarded),
`s[18]=gTbl_082265C0[s[17]]`. Idiom: `gTbl_082265C0` as global `.set`
(0x082265C0) forces `ldr r0,[pc]` before `ldrb r1,[r4,#17]`.

### 0x08019B64 ObjInit_08019B64 (106B)
Same family: `ChipSlot_Setup(s,0x80<<2,s[17])` (`movs r1,#0x80; lsls r1,#2`),
`ChipSlot_IncUse(s,0)`, same idx/mask/sh, then `Vec2_AddMirrored(s,0xFFFFC400,0)`
(pool), `SetBit16(*(s+44),3)`. No Text_SelectBlobIdx.

### 0x08018310 ObjInit_08018310 (116B)
`ChipSlot_Setup(s,541,s[17])`, `ChipSlot_IncUse(s,1)`, same idx/mask/sh,
`s[0x22]=13`, then `*(s+88)=0xA0<<3` (0x500), `*(s+96)=10`, zeros at 92/100,
`Vec2_AddMirrored(s,0xFFFFD300,0xFFFFF800)`, `SetBit16(*(s+44),3)`,
`Text_SelectBlobIdx(0xA3)` discarded.

### 0x08018E1C ObjInit_08018E1C (116B)
Twin of 0x08018310: `ChipSlot_Setup(s,553,s[17])`, `ChipSlot_IncUse(s,0)`,
`*(s+88)=0x80<<3` (0x400), `Vec2_AddMirrored(s,0xFFFFD200,0xFFFFFB00)`,
`Text_SelectBlobIdx(0x8D)` discarded.

### 0x080181AC ObjInit_080181AC (126B)
`ChipSlot_Setup(s,543,((u32)s[17]<<25)>>24)` (bit-extract idiom:
`ldrb/lsls #25/lsrs #24`), `ChipSlot_IncUse(s,0)`, same idx/mask/sh,
`s[0x22]=13`, `*(s+88)=0x80<<2` (0x200), `*(s+96)=0`,
`*(s+92)=(u32)-(int)0x80` (`movs/negs`), `*(s+100)=8`,
`Vec2_AddMirrored(s,0xFFFFD300,0)`, `SetBit16(*(s+44),3)`,
`Text_SelectBlobIdx(0x9F)` discarded.

### 0x0801F9EC ObjInit_0801F9EC (112B)
Wave-5 ObjInit_207EC variant: `r5=*(s+40)` pinned; `*(s+108)=0` via
`register u32 z __asm__("r0")`; `t=2; t|=s[10]; s[10]=t|1`;
`Wrapper_D728(s,15639,0)`, `ChipSlot_IncUse(s,0)`; idx/mask/sh with
`gRom_081705B0[0]`/`gEwram_020031E4` globals; `s[0x22]=0`, zeros at 80/84,
`s[18]=0x40`, `s[19]=16`, `r5[7]=0`.

### 0x080200EC ObjInit_080200EC (120B)
`p2=*(u8**)(*(u8**)(s+40)+40)` pinned to r2; `s[18]=((u32)(*(p2+0x23))<<28)>>28`
(inlined to get `lsls r0,r2,#28`); `w=(s[18]==0)?0x3E18:0x3F18`;
`Wrapper_D728(s,w,0)`, `ChipSlot_IncUse(s,1)`; idx via `gRom_081705B0[1]`
(note index 1, `ldrh [r0,#2]`); mask/sh; `s[0x22]=30`, `s[19]=4`.

## BLOCKED

### 0x08016D2C (116B, 26 diffs, old_agbcc)
Calls ObjInit_08016DAC. ROM uses `r2=s` (caller-saved, s not live after final
bl), `r3=s+0x7c`, `r1=tbl` pool, `r4=s[9]`. Tried: natural allocation (r3=s,
wrong), pinning r2/r3 (97 diffs, broke), inlining (98 diffs), decl-order
(108 diffs), main agbcc (106 diffs). The `adds r2,r0,#0` first-instruction
allocation not reproduced.

### 0x08025108 (128B, 74 diffs, old_agbcc)
Data copier with `Clamp_26720`. ROM loop uses r7 base + sign-extended index
with `lsls/asrs` pattern; my for-loop over-optimized to 112B (16B short).
Tried do-while (124B, worse). Complex loop not reproduced.

## UNATTEMPTED
18 functions: 0x0803aed0, 0x0800a6bc, 0x0801b47c, 0x080211ec, 0x08011ac8,
0x0801f254, 0x08020b60, 0x08003fc8, 0x0801fcd0, 0x080482d8, 0x08042c04,
0x0802d6e0, 0x0801b0dc, 0x0802298c (all smaller ones), plus 0x0800ac8c,
0x08001f1c, 0x08002070, 0x0804d8a8 (294B+, skipped per budget).

Note: /tmp was cleared mid-session (VM restart); all 10 MATCHED .c files were
reconstructed from notes and re-verified to 0 diffs before writing results.
