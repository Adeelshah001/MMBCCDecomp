/* Wave 34-C v3: 0x08006928 — Worker(0x0200483c, a, (s16)b, (s16)c, (s8)d, 0). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef signed char s8;

extern void Worker_0800695C(u8 *p, u8 *a, s16 b, s16 c, s8 d, int e);
__asm__(".set Worker_0800695C, 0x0800695c");

__attribute__((section(".text.w34c_08006928")))
void Sub_08006928(u8 *a, int b, int c, int d)
{
    u8 *aa = a;
    s16 bb = b;
    s16 cc = c;
    s8 dd = d;
    Worker_0800695C((u8 *)0x0200483c, aa, bb, cc, dd, 0);
}
