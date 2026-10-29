/* W60-D v1: 0x08014a44, TRUE extent 272 B (code to bx @0x14b4c, pad @0x14b4e,
 * pool @0x14b50 = 0xffffc400, next fn @0x14b54). Switch on s[14], jump table
 * @0x14a64 (cases 0..4 -> 0x14a78/0x14a90/0x14ad0/0x14afc/0x14b1a).
 * Shared s[14]++ tail (cross-jump) + ChipSlot_Tick epilogue. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern void Vec2_SetMirrored(u8 *o, u32 x, u32 y);
extern void ChipSlot_IncUse(u8 *s, int idx);
extern void ChipSlot_Tick(u8 *s);
extern u16 Check119_Minus3_Le1(u8 *s);
extern void SetBit16(u8 *s, int bit);
extern void ChipInit_080178A8(u32 a, u32 b, u32 c, u32 d, u32 e);
extern u8 GetField17_U8(u8 *s);
extern void MaxAssign_17(u8 *s, u8 v);
extern void DecIfNonZero_18(u8 *s);
extern void SetBytes_08011F68(u8 *s, u8 v);

__attribute__((section(".text.w60d_08014a44")))
void Sub_08014A44(u8 *s)
{
    u8 *p = s + 124;
    switch (s[14]) {
    case 0:
        Vec2_SetMirrored(s, 0xffffc400, 0);
        ChipSlot_IncUse(s, 8);
        s[14]++;
        break;
    case 1:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        SetBit16(*(u8 **)(s + 44), 3);
        ChipInit_080178A8(125, ((u32)s[35] << 28) >> 28, 0xffffec00, 0, *(u32 *)(s + 44));
        ChipSlot_IncUse(s, 9);
        s[18] = 3;
        s[14]++;
        break;
    case 2:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        {
            int t = s[18] - 1;
            s[18] = t;
            if ((u8)t == 0) {
                ChipSlot_IncUse(s, 10);
                s[14]++;
            } else {
                ChipSlot_IncUse(s, 9);
            }
        }
        break;
    case 3:
        if (GetField17_U8(*(u8 **)(s + 44)) <= 5)
            break;
        MaxAssign_17(*(u8 **)(s + 44), 7);
        s[14]++;
        break;
    case 4:
        DecIfNonZero_18(*(u8 **)(s + 44));
        *(u32 *)(s + 44) = 0;
        Vec2_SetMirrored(s, 0xffffc400, 0);
        ChipSlot_IncUse(s, 0);
        p[4] = 0;
        SetBytes_08011F68(s, 0);
        break;
    }
    ChipSlot_Tick(s);
}
