/* Wave 36-D v3: 0x080053a0, 148 B, extent next-func 0x08005434. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void Sub_08005434(u32 *p, u32 a, u32 b);
__asm__(".set Sub_08005434, 0x08005434");

__attribute__((section(".text.w36d_080053a0")))
void Sub_080053A0(void)
{
    register u8 *base __asm__("r4") = (u8 *)0x02003670;
    register u32 *p1 __asm__("r6") = (u32 *)(base + 1140);
    register u32 v2 __asm__("r5") = 0x06004000;
    p1[0] = 0x06001000;
    p1[1] = v2;
    Sub_08005434(p1, 0, 0);
    p1[5] = 240 << 7;
    p1[6] = 160 << 7;
    p1 = (u32 *)(base + 4);
    *(u32 *)(base + 4) = (u32)(base + 1708);
    p1[1] = v2;
    Sub_08005434(p1, 0, 0);
    {
        register u32 *p3 __asm__("r6") = (u32 *)(base + 572);
        u8 flag;
        u8 t;
        u32 a1;
        u32 a2;
        p3[0] = 0x06003000;
        p3[1] = 0x0600c000;
        base = base + 4526;
        flag = *base;
        t = (u8)(4 & flag);
        a1 = 112;
        if (t != 0) a1 = 120;
        a2 = 72;
        if (t != 0) a2 = 80;
        Sub_08005434(p3, a1, a2);
    }
}
