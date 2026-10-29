/* Wave 34-C v1: 0x08024fd8 — (u16)worker(0x02007090+24, a, b). */
typedef unsigned char u8;
typedef unsigned short u16;

extern u16 Worker_08026430();
__asm__(".set Worker_08026430, 0x08026430");

__attribute__((section(".text.w34c_08024fd8")))
u16 Sub_08024FDC(int a, int b)
{
    u8 *p = (u8 *)0x02007090;
    u8 *q;
    __asm__ volatile("" : "+r"(p));
    q = p + 24;
    return (u16)Worker_08026430(q, a, b);
}
