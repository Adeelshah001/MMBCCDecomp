/* Wave 34-C v1: 0x08000e04 — if (b) { s->h2=b; s->b0=4; worker(s+4, s+8, *(u32*)0x02000800); } */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void Worker_08000300(u8 *p1, u8 *p2, u32 v);
__asm__(".set Worker_08000300, 0x08000300");

__attribute__((section(".text.w34c_08000e04")))
void Sub_08000E04(u8 *s, int b)
{
    u8 *p1, *p2;
    u32 v;
    if (b == 0)
        return;
    *(u16 *)(s + 2) = b;
    s[0] = 4;
    p1 = s + 4;
    p2 = s;
    p2 += 8;
    v = *(u32 *)0x02000800;
    Worker_08000300(p1, p2, v);
}
