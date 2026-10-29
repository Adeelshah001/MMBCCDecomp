/* Wave 34-C v1: 0x08003058 — if ((s32)(a<<16))>=0: b=a; if (G(b)) H(b). */
typedef unsigned int u32;
typedef unsigned short u16;
typedef signed int s32;

extern int G_0800300C(u16);
extern void H_0804C780(u16);
__asm__(".set G_0800300C, 0x0800300c");
__asm__(".set H_0804C780, 0x0804c780");

__attribute__((section(".text.w34c_08003058")))
void Sub_08003058(u32 a)
{
    u32 t = a << 16;
    u16 b;
    if ((s32)t < 0)
        return;
    b = t >> 16;
    if (G_0800300C(b))
        H_0804C780(b);
}
