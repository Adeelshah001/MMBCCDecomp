/* W60-D v2: 0x080137e4, TRUE extent 288 B (code 282 B to bx @0x138fc, pad
 * @0x138fe, pool @0x13900 = 0xffffc400, next fn @0x13904). Switch on s[14],
 * jump table @0x13804 (cases -> 0x13818/0x1382c/0x13864/0x138a0/0x138bc).
 * Shared IncUse + s[14]++ tail (case3's block @0x138b0) + Tick epilogue.
 * Case1: F_0801EBF0(36,-1,nib,-15360,0); case2: Sub_0801AA70(20,s[134],
 * nib,h0,h1,s44) with 0x08223ed8 table, register-offset ldrsh halves. */
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
extern void F_0801EBF0(int a, int b, int c, s16 d, s16 e);
__asm__(".set F_0801EBF0, 0x0801ebf0");
extern void Sub_0801AA70(int a, int b, int c, int d, int e, u8 *f);
__asm__(".set Sub_0801AA70, 0x0801aa70");
extern u8 GetField17_U8(u8 *p);
extern void DecIfNonZero_18(u8 *s);
extern void SetBytes_08011F68(u8 *s, u8 v);

__attribute__((section(".text.w60d_080137e4")))
void Sub_080137e4(u8 *s)
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
        F_0801EBF0(36, -1, ((u32)s[35] << 28) >> 28, -15360, 0);
        ChipSlot_IncUse(s, 9);
        s[18] = 5;
        s[14]++;
        break;
    case 2: {
        int a1;
        int nib;
        register u8 *base __asm__("r3");
        int idx;
        u8 *ep;
        int off0;
        int h0;
        int off;
        int h1;
        s[18]--;
        if (s[18] != 0)
            break;
        a1 = p[10];
        nib = ((u32)s[35] << 28) >> 28;
        base = (u8 *)0x08223ed8;
        __asm__ volatile("" : "+r"(base));
        idx = p[0];
        ep = (u8 *)(idx * 4);
        __asm__ volatile("add %0, %0, %1" : "+r"(ep) : "r"(base));
        off0 = 0;
        h0 = *(s16 *)(ep + off0);
        off = 2;
        h1 = *(s16 *)(ep + off);
        Sub_0801AA70(20, a1, nib, h0, h1, *(u8 **)(s + 44));
        s[14]++;
        break;
    }
    case 3:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        ChipSlot_IncUse(s, 10);
        s[14]++;
        break;
    case 4:
        if (GetField17_U8(*(u8 **)(s + 44)) <= 6)
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
