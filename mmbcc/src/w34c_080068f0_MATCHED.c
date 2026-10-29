/* Wave 34-C v1: 0x080068f0 — Worker(0x02004830, a, (s16)b, (s16)c, (s8)d, (u8)e). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef signed char s8;

extern void Worker_0800695C(u8 *p, u8 *a, s16 b, s16 c, s8 d, u8 e);
__asm__(".set Worker_0800695C, 0x0800695c");

__attribute__((section(".text.w34c_080068f0")))
void Sub_080068F0(u8 *a, int b, int c, int d, int e)
{
    u8 *aa = a;
    s16 bb = b;
    s16 cc = c;
    s8 dd = d;
    u8 ee = e;
    Worker_0800695C((u8 *)0x02004830, aa, bb, cc, dd, ee);
}
