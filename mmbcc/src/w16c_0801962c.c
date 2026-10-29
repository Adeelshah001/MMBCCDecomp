typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
extern void ChipSlot_Setup(u8 *s, u16 b, u8 c);
extern void ChipSlot_IncUse(u8 *p, u8 x);
extern void SetBit16(u8 *s, u8 bit);
__attribute__((section(".text.w16c_0801962c")))
void ChipInit_0801962C(u8 *p)
{
    u32 idx;
    int mask;
    u8 *q;
    u32 sh;
    ChipSlot_Setup(p, 0x233, 0);
    ChipSlot_IncUse(p, 0);
    {
        u16 *p1 = (u16 *)0x081705B0;
        u8 *p2 = (u8 *)0x020031E4;
        idx = (*(u8 *)((((*p1 >> 4) << 1) + (u32)p2))) & 3;
    }
    {
        register int c __asm__("r0");
        __asm__ ("movs %0, %1" : "=r" (c) : "r" (idx));
        if (c > 3)
            idx = 3;
    }
    q = p;
    q += 0x45;
    sh = idx << 2;
    mask = -13;
    *q = (*q & mask) | sh;
    q -= 0x23;
    {
        u32 z = 0;
        *q = 13;
        *(u32 *)(p + 88) = 0x80 << 3;
        *(u32 *)(p + 96) = z;
        *(u32 *)(p + 92) = z;
        *(u32 *)(p + 100) = z;
        SetBit16(*(u8 **)(p + 44), 3);
    }
}