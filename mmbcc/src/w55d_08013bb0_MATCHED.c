/* W55-D: 0x08013bb0, 252 B. Move-task step (SetMirrored family).
 * Goto-dispatch on int mode = s[14] (bgt form, like matched 139fc).
 * Cases inline IncUse + s[14]++ + goto tail (cross-jump candidate).
 * c1: F1EBF0(33, -1, nib, -15360, 0) with nib INLINE in call.
 * c2: SetBit16 takes s44 VALUE; ChipInit(86, nib, -5120, -7680, s44).
 * c3: GetField>5 -> MaxAssign + Dec + s44=0 + SetMirrored + IncUse(0)
 *   + p[4]=0 + SetBytes, then tail. Tail: Tick(s).
 * Pools (raw LE): -15360 @0x13be4, @0x13c14, @0x13ca8;
 * -5120 @0x13c54; -7680 @0x13c58.
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern void Vec2_SetMirrored(u8 *o, s32 x, s32 y);
extern u16 Check119_Minus3_Le1(u8 *s);
extern void Sub_0801EBF0(int a, int b, int c, int d, int e);
__asm__(".set Sub_0801EBF0, 0x0801ebf0");
extern void SetBit16(u32 v, int bit);
extern void ChipInit_080178A8(int a, int b, int c, int d, u32 e);
extern u8 GetField17_U8(u32 v);
extern void MaxAssign_17(u32 v, int n);
extern void DecIfNonZero_18(u32 v);
extern void ChipSlot_IncUse(u8 *s, int idx);
extern void SetBytes_08011F68(u8 *s, u8 v);
extern void ChipSlot_Tick(u8 *s);



__attribute__((section(".text.w55d_08013bb0")))
void Sub_08013BB0(u8 *s)
{
    u8 *p = s + 124;
    int mode;
    mode = s[14];
    if (mode == 1)
        goto c1;
    if (mode > 1)
        goto gt1;
    if (mode == 0)
        goto c0;
    goto tail;
gt1:
    if (mode == 2)
        goto c2;
    if (mode == 3)
        goto c3;
    goto tail;
c0:
    Vec2_SetMirrored(s, -15360, 0);
    ChipSlot_IncUse(s, 8);
    s[14]++;
    goto tail;
c1:
    if (Check119_Minus3_Le1(s) == 0)
        goto tail;
    Sub_0801EBF0(33, -1, ((u32)s[35] << 28) >> 28, -15360, 0);
    ChipSlot_IncUse(s, 9);
    s[14]++;
    goto tail;
c2:
    if (Check119_Minus3_Le1(s) == 0)
        goto tail;
    SetBit16(*(u32 *)(s + 44), 3);
    {
        int nib = ((u32)s[35] << 28) >> 28;
        ChipInit_080178A8(86, nib, -5120, -7680, *(u32 *)(s + 44));
    }
    ChipSlot_IncUse(s, 10);
    s[14]++;
    goto tail;
c3:
    if ((u8)GetField17_U8(*(u32 *)(s + 44)) <= 5)
        goto tail;
    MaxAssign_17(*(u32 *)(s + 44), 7);
    DecIfNonZero_18(*(u32 *)(s + 44));
    *(u32 *)(s + 44) = 0;
    Vec2_SetMirrored(s, -15360, 0);
    ChipSlot_IncUse(s, 0);
    p[4] = 0;
    SetBytes_08011F68(s, 0);
    goto tail;
tail:
    ChipSlot_Tick(s);
}
