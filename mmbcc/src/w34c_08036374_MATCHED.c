/* Wave 34-C v1: 0x08036374 — A(p); p[1]=B((s8)x,0,0); return 1. */
typedef unsigned char u8;
typedef signed char s8;

extern void A_080363EC(u8 *p);
extern int B_0803643C(s8 x, int y, int z);
__asm__(".set A_080363EC, 0x080363ec");
__asm__(".set B_0803643C, 0x0803643c");

__attribute__((section(".text.w34c_08036374")))
int Sub_08036374(int x)
{
    u8 *p = (u8 *)0x0200bce8;
    int xx = x;
    s8 ss;
    A_080363EC(p);
    ss = xx;
    p[1] = B_0803643C(ss, 0, 0);
    return 1;
}
