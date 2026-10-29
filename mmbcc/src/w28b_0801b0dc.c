/* Wave 27-C: 0x0801b0dc (208 B) - v2: fixed tail */
typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;

extern void ChipSlot_Setup(u8 *s, u16 b, u8 c);
extern void ChipSlot_IncUse(u8 *s, u8 idx);
extern void Wrapper_D770(u8 *p, u16 x, u8 y);
extern void Text_SelectBlobIdx(u8 v);

__attribute__((section(".text.w28b_0801b0dc")))
void ChipSetup_0801B0DC(u8 *s)
{
    u8 v = s[17];
    switch (v) {
    case 0:
        ChipSlot_Setup(s, 0x246, 0);
        ChipSlot_IncUse(s, 2);
        *(u32 *)(s + 88) = 0x200;
        *(u32 *)(s + 96) = 20;
        *(u32 *)(s + 92) = v;
        *(u32 *)(s + 100) = v;
        break;
    case 1:
        ChipSlot_Setup(s, 0x246, 0);
        ChipSlot_IncUse(s, 3);
        *(u32 *)(s + 88) = 0x200;
        *(u32 *)(s + 96) = 5;
        *(u32 *)(s + 92) = 200;
        *(u32 *)(s + 100) = 5;
        break;
    case 2:
        Wrapper_D770(s, 0x847, 1);
        ChipSlot_IncUse(s, 1);
        *(u32 *)(s + 88) = 0x200;
        *(u32 *)(s + 96) = 10;
        *(u32 *)(s + 92) = 406;
        *(u32 *)(s + 100) = (u32)-10;
        break;
    default:
        break;
    }
    {
        u16 base = *(u16 *)0x081705b0;
        u8 *tbl = (u8 *)(0x020031e4 + ((u32)(base >> 4) << 1));
        int t = *tbl & 3;
        u8 *p69;
        u8 v69;
        int m;
        {
            register int c __asm__("r0");
            __asm__ volatile("add %0, %1, #0" : "=r"(c) : "r"(t));
            if (c > 3)
                t = 3;
        }
        p69 = s + 69;
        t <<= 2;
        m = 13;
        m = -m;
        v69 = *p69;
        *p69 = (v69 & m) | t;
        s[34] = 13;
        Text_SelectBlobIdx(0xa0);
    }
}
