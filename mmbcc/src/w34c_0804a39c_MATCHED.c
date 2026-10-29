/* Wave 34-C v1: 0x0804a39c — A(); q->h2 |= 1; *(p+120) = 0 (dead-load quirk). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void A_08000F28(void);
__asm__(".set A_08000F28, 0x08000f28");

__attribute__((section(".text.w34c_0804a39c")))
void Sub_0804A39C(void)
{
    u8 *p = (u8 *)0x0200bd20;
    volatile u16 *q;
    u16 t, v, one;
    A_08000F28();
    q = (volatile u16 *)0x02002ee0;
    t = q[1];
    one = 1;
    v = q[1];
    v = 0;
    q[1] = one | t;
    *(u32 *)(p + 120) = v;
}
