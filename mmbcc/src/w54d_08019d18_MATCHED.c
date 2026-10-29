/* W54-D v5: 0x08019d18 (v4 + trailing .balign 4, 0 for the 2-mod-4 pad), 244 B true extent (bx 0x08019e08, next 0x08019e0c).
 * Re-decoded from ROM (correcting W38 on three points):
 *  - dispatch is a balanced switch tree (cmp #1/beq c1, bgt upper,
 *    cmp #0/beq c0, then cmp #2/beq c2, cmp #3/beq c3), so source is
 *    a switch(mode) with cases in order 0,1,2,3, not a goto chain;
 *  - mode lives in callee-saved r7 (push {r4,r5,r6,r7,lr}), out0 in r5,
 *    out1 in r6, s in r4 (all live across calls);
 *  - SetBit16/TestBit16 take the s44 VALUE (ROM ldr r0,[r4,#44]),
 *    not the s+44 address;
 *  - c1: TestBit!=0 path (fall-through) sets s[13]=2; else path is the
 *    two-AND block (253 & s[10] via an intermediate t, defeating the
 *    &252 fold, const-first matching ROM) then s[13]=3; TestBit
 *    returns u8 (ROM lsl #24; cmp #0). Mode is NOT pinned: with
 *    out0/out1 pinned to r5/r6, the allocator must give the
 *    call-crossing mode the remaining callee-saved r7 AND save it
 *    (a direct r7 pin is used but NOT saved by old_agbcc).
 *  - c2/c3 share the return-1 movs block (9dee in ROM).
 * Pools: -7680 only (mid, 0x08019dd0). Callees: AddMirrored MATCHED,
 * CopyMirrored via .set, SetBit16/IncUse/TestBit16/GetField/ChipInit
 * MATCHED (ChipInit 5th arg s44 VALUE).
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern void Vec2_AddMirrored(u8 *s, int a, int b);
extern void Vec2_CopyMirrored(u8 *out, u8 *s);
__asm__(".set Vec2_CopyMirrored, 0x0800dd08");
extern void SetBit16(u32 v, int bit);
extern void ChipSlot_IncUse(u8 *s, int idx);
extern void ChipInit_080178A8(int a, int b, int c, int d, int e);
extern u8 TestBit16(u32 v, int bit);
extern u8 GetField17_U8(int v);

__attribute__((section(".text.w54d_08019d18")))
int Sub_08019D18(u8 *s)
{
    u32 out[2];
    register int out0 __asm__("r5");
    register int out1 __asm__("r6");
    int mode;
    Vec2_AddMirrored(s, *(u32 *)(s + 88), *(u32 *)(s + 92));
    *(u32 *)(s + 88) += *(u32 *)(s + 96);
    *(u32 *)(s + 92) += *(u32 *)(s + 100);
    Vec2_CopyMirrored((u8 *)out, s);
    out0 = out[0];
    out1 = out[1];
    mode = s[13];
    switch (mode) {
    case 0:
        if ((u8)(s[119] - 3) <= 1) {
            SetBit16(*(u32 *)(s + 44), 3);
            ChipSlot_IncUse(s, 1);
            *(u32 *)(s + 88) = 128 << 3;
            *(u32 *)(s + 96) = 10;
            *(u32 *)(s + 92) = mode;
            *(u32 *)(s + 100) = mode;
            s[13]++;
        }
        break;
    case 1:
        if (out0 > 200 << 6) {
            int nib = (int)(((u32)s[35] << 28) >> 28);
            ChipInit_080178A8(93, nib, (s16)out0, (s16)(out1 - 7680), *(u32 *)(s + 44));
            if (TestBit16(*(u32 *)(s + 44), 0) != 0) {
                s[13] = 2;
            } else {
                u32 t = 253 & s[10];
                s[10] = t & 254;
                s[13] = 3;
            }
        }
        break;
    case 2:
        if (out0 > 130 << 8)
            return 1;
        break;
    case 3:
        if (GetField17_U8(*(u32 *)(s + 44)) > 5)
            return 1;
        break;
    default:
        break;
    }
    return 0;
}

/* Trailing pad: code ends 2 mod 4 (bx at +240); ROM has 00 00 here. */
__asm__(".balign 4, 0");
