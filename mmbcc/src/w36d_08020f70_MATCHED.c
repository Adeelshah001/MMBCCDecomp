/* Wave 36-D v4: 0x08020f70, 144 B, extent next-func 0x08021000 (includes trailing helper at +0x80). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 *Sub_08020ED4(u32 a, u32 b, u32 c, u32 d);
__asm__(".set Sub_08020ED4, 0x08020ed4");
extern void Sub_08002300(u32 *p, u32 a);
__asm__(".set Sub_08002300, 0x08002300");
extern void Sub_08002904(u32 *p, u32 a, u32 b);
__asm__(".set Sub_08002904, 0x08002904");

__attribute__((section(".text.w36d_08020f70")))
u8 *Sub_08020F70(u8 a, u32 b, u32 c)
{
    register u32 bb __asm__("r6") = b;
    u32 cc = c;
    register u8 *r5 __asm__("r5");
    u32 c0, c1;
    if (a == 14) {
        c0 = 0;
        c1 = 1;
    } else {
        c0 = 0;
        c1 = 0;
    }
    r5 = Sub_08020ED4(c0, c1, 0, 0);
    if (r5 != 0) {
        r5[16] = 0;
        r5[17] = a;
        *(u32 *)(r5 + 40) = bb;
        *(u32 *)(r5 + 44) = cc;
    }
    {
        u32 *base1 = (u32 *)0x08173760;
        u32 *r4 = *(u32 **)((u8 *)base1 + 88);
        u32 *base2 = (u32 *)0x08226f34;
        r4 = (u32 *)((u8 *)r4 + ((u32)*(u8 *)((u8 *)base2 + r5[17]) << 2));
        r4 = (u32 *)((u8 *)r4 + *r4);
        {
            u32 *base3 = (u32 *)0x0817386c;
            Sub_08002300(r4, ((u32)*(u16 *)((u8 *)base3 + 44) << 5) + 65536);
        }
        r4 = (u32 *)((u8 *)r4 + 12);
        {
            u32 *base4 = (u32 *)0x081738f2;
            u16 hv = *(u16 *)((u8 *)base4 + 44);
            Sub_08002904(r4, 0, (u8)hv);
        }
    }
    return r5;
}

/* Trailing helper at section offset +0x80 (ROM 0x08020ff0). */
__attribute__((section(".text.w36d_08020f70")))
u32 Sub_08020FF0(u8 *s)
{
    u32 r = 0;
    if (s[12] > 1) r = 1;
    return r;
}

/* Explicit 00 00 pad: GAS would otherwise emit a c0 46 nop fill here. */
__asm__(".short 0");
