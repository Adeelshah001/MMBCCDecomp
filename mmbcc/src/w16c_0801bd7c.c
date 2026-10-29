typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
extern void Wrapper_D770(u8 *p, u16 x, u8 y);
extern void ChipSlot_IncUse(u8 *p, u8 x);
extern void Vec2_AddMirrored(u8 *p, u32 x, u32 y);
__attribute__((section(".text.w16c_0801bd7c")))
void ChipInit_0801BD7C(u8 *p)
{
    u32 idx;
    int mask;
    u8 *q;
    u32 sh;
    Wrapper_D770(p, 0x825, 0);
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
    p[0x22] = 13;
    Vec2_AddMirrored(p, 0xFFFFC400, 0);
}