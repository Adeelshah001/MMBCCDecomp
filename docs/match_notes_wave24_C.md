# Wave 24 Worker C Notes (rows 38-75)

## 0x0800a6bc — Ewram4830_StateReset_0800A6BC — MATCHED (152 B, old_agbcc, 0 diffs)
EWRAM 0x02004830 state reset. If p[1]==0: p[1]=1, Ewram4E40_Init_0B4E4(),
Clr_0800B4C8(), p[19] &= -3 (widened-temp idiom: movs r0,#3; negs).
If p[1] not in {0,1}: return 1. Then saturating decrement of the byte at
0x02004830+0x264: when (p[19]&1) and (s8)b>1, r=(u8)((s8)b-max((s8)b>>2,1));
if r>0 store, else zero p[0..3] and *(u8*)(0x02004830+0x265), then store r.
Idioms: pinned `sh`->r1 for the `lsls r1,r1,#24; adds r2,r1,#0` shift/copy;
honest s8 intermediates (sb2, ds) to force the sign-extends that the
compiler folds through the trailing (u8); empty asm barrier on `base`
defeats constant folding so `*(base+0x265)` emits the two ROM pool loads
(0x02004830, 0x265) instead of folding to 0x02004A95. Mid-function pool
(0x02004830 for r5) placed by old_agbcc after the `b end`, as in ROM.

## 0x0800e748 — ChipState_Tick_0800E748 — MATCHED (128 B, main agbcc, 0 diffs)
Sibling of 0x0800E3A0 (chip-init state machine on 0x02005130). Differences:
arg is S[37] ? 6 : 2 (not 0); null case zeroes *(u16*)(0x02005130+24) and
calls SetByte20(0) instead of just breaking. Idioms: inline asm for the
`cmp; beq; movs r0,#6; b; movs r0,#2` ternary (both agbcc emit a speculative
mov without it); volatile u32 forces the `str r0,[r4,#28]; ldr r1,[r4,#28]`
store+reload; second base variable S2 (not the pinned S) defeats constant
folding so the mid-function pool holds 0x02005130 (not 0x02005148) with
`strh r1,[r0,#24]`. Previously BLOCKED in wave21 for pool extents; the
trailing-pool extent fix (128 B true) resolved it.

## 0x0800e224 — ChipList_Setup_0800E224 — MATCHED (168 B, main agbcc, 0 diffs)
Node setup on 0x02005130: two Node_PopAndInit_11E20(1,0/1,1) + F_08016E0C
with S[4]/S[5]; ListIterate over 0x02005270/0x020053C0; Byte128_IsZero on
*(u32*)0x02005020/0x02005024 sets S[22] bits; S[22]==3 gate with
Cmp_08004E0C(0) zeroes S[24:25] and calls SetByte20(0). Idioms: the
`v=1; v|=S[22]; S[22]=v` shape forces ROM's `movs r0,#1; ldrb r1; orrs`
order; a u8 zero variable is reused for the `strh` and the following `bl`
so the compiler does not emit a second `movs r0,#0`.

## 0x0800e2cc — ChipState_Tick3_0800E2CC — BLOCKED (prologue register allocation)
3-case state machine (cases 0/1/2 on S[21]) with 0xFFFF mask check in case 0,
F_08016E4C calls in case 1, Byte128_IsZero bit-setting in case 2. The body
structure is understood, but the prologue `movs r7,#0` (r7 used as zero for
two later `strh r7,[r4,#24]`) cannot be reproduced: pinning z->r7 gets
clobbered by the compiler reusing r7 for the constant 1; without the pin the
compiler uses r8 or omits the init. The `ldr r6,[r0,#4]` (vs `add`+`ldr`)
was solved via pp[0]/pp[1]. Needs a register-allocation idiom for the
r7-zero pattern.

## 0x08020b60 — ChipSlot_Init_08020B60 — BLOCKED (r5 CSE)
Chip-slot init: *(u32*)(p+108)=0; p[10]=(p[10]|2)|1; ChipSlot_Setup(p,0x401b,0);
ChipSlot_IncUse(p,0); t=(*(u16*)0x081705b0>>4<<1 offset into 0x020031e4)&3;
if t>3 t=3; *(p+69)=(*(p+69)&-13)|(t<<2); if p[17] { *(p+72)=1; p[10]|=16; }
p[18]=16; *(u32*)(p+80)=0xF0<<7; *(u32*)(p+84)=p[17]?0x8C<<8:0x80<<6.
BLOCKED: compiler CSEs the constant 1 (used in `p[10]|=1` and `*(p+72)=1`)
into callee-saved r5, giving push {r4,r5,lr} vs ROM's push {r4,lr}. The ROM
rematerializes 1 in temps. An r5 clobber asm did not defeat it.
