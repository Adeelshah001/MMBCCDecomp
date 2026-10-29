/* W60-D v3: 0x08013024, TRUE extent 276 B (code to bx @0x13130, pad @0x13132,
 * pool @0x13134 = 0xffffc400, next fn @0x13138). Switch on s[14], jump table
 * @0x13044 (cases -> 0x13058/0x1306c/0x1307e/0x130d4/0x130f2). Shared
 * IncUse+s[14]++ tail (cross-jump) + ChipSlot_Tick epilogue. Case2: two
 * Sub_1AA70 calls sharing a pool var (r5) and a zero temp (r4), nibble
 * re-read from the s+35 pointer (r7) after the first call. */
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
extern void Sub_0801AA70(int a, int b, int c, int d, int e, u8 *f);
__asm__(".set Sub_0801AA70, 0x0801aa70");
extern int Text_SelectBlobIdx(int idx);
extern u8 GetField17_U8(u8 *s);
extern void DecIfNonZero_18(u8 *s);
extern void SetBytes_08011F68(u8 *s, u8 v);

__attribute__((section(".text.w60d_08013024")))
void Sub_08013024(u8 *s)
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
        ChipSlot_IncUse(s, 9);
        s[14]++;
        break;
    case 2: {
        u8 *q;
        register int nib __asm__("r2");
        int c;
        int z;
        if (Check119_Minus3_Le1(s) == 0)
            break;
        SetBit16(*(u8 **)(s + 44), 3);
        q = s + 35;
        nib = ((u32)*q << 28) >> 28;
        c = -15360;
        z = 0;
        Sub_0801AA70(2, 0, nib, c, z, *(u8 **)(s + 44));
        nib = ((u32)*q << 28) >> 28;
        Sub_0801AA70(3, 0, nib, c, z, *(u8 **)(s + 44));
        Text_SelectBlobIdx(152);
        s[14]++;
        break;
    }
    case 3:
        if (GetField17_U8(*(u8 **)(s + 44)) <= 6)
            break;
        ChipSlot_IncUse(s, 10);
        s[14]++;
        break;
    case 4:
        if (Check119_Minus3_Le1(s) == 0)
            break;
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
