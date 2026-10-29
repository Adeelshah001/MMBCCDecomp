typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void Sub_080053A0(void);
extern void Sub_08004EE0(void);
extern void Sub_080052DC(int a, int b, int c, int d);
extern void Sub_0800B8D0(void);
extern void Sub_08004EF4(void);
__asm__(".set Sub_08004EE0, 0x08004ee0");
__asm__(".set Sub_080052DC, 0x080052dc");
__asm__(".set Sub_0800B8D0, 0x0800b8d0");
__attribute__((section(".text.w38b_08004e60")))
void Sub_08004E60(u8 a)
{
    register u8 aa __asm__("r6") = a;
    u8 *p = (u8 *)0x02003670;
    u16 q = 4526;
    register u8 bit __asm__("r5") = ((u32)p[q] << 29) >> 31;
    u8 *qq;
    u16 i;
    int z;
    int t;
    qq = p;
    i = 0;
    z = 0;
    while (i <= q + 9) {
        *qq++ = z;
        __asm__ volatile("lsl %0, %0, #16\n\tmovs r7, #128\n\tlsl r7, r7, #9\n\tadd %0, %0, r7\n\tlsr %0, %0, #16" : "+r"(i) :: "r7");
    }
    p += 4526;
    t = (aa << 3) | (*p & 7);
    t &= -5;
    t |= (bit << 2);
    t &= -3;
    *p = t;
    Sub_080053A0();
    if ((*p & 248) != 8)
        Sub_08004EE0();
    Sub_080052DC(0, 160, 0, 240);
    Sub_0800B8D0();
    Sub_08004EF4();
}
