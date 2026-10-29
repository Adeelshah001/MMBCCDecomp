/* Wave 36-D v5 (a pinned r0): 0x0800c878 — u8 temp a (r0) + barrier, then v pinned r1. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void Worker_0800244C(u8 *p, int v);
__asm__(".set Worker_0800244C, 0x0800244c");
__attribute__((section(".text.w36d_0800c878")))
void Sub_0800C878(u8 *s)
{
    register u8 *q __asm__("r2") = s + 52;
    register u16 *fp __asm__("r2");
    register u8 a __asm__("r0");
    register u32 v __asm__("r1");
    u8 *entry;
    int w;
    __asm__ volatile("" : "+r"(q));
    a = *q + 1;
    __asm__ volatile("" : "+r"(a));
    v = a;
    __asm__ volatile("" : "+r"(v));
    if (v > 24)
        v = 0;
    *q = (u8)v;
    entry = (u8 *)0x0830b660 + (v >> 2) * 20;
    fp = (u16 *)0x020031e8;
    __asm__ volatile("" : "+r"(fp));
    w = 12;
    w &= *fp;
    Worker_0800244C(entry, (w << 12) + 0x2320);
}
