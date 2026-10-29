/* Wave 34-C v1: 0x08005274 — if ((s16)a<0) A(s+12,b<<5) else B(s+12,(u8)a,(u8)b). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

extern void A_0800288C(u8 *p, u32 x);
extern void B_080028D0(u8 *p, u8 a, u8 b);
__asm__(".set A_0800288C, 0x0800288c");
__asm__(".set B_080028D0, 0x080028d0");

__attribute__((section(".text.w34c_08005274")))
void Sub_08005274(u8 *s, u32 a, u32 b)
{
    u32 t = a << 16;
    u16 bb = b;
    u16 aa = t >> 16;
    if ((s32)t < 0)
        A_0800288C(s + 12, bb << 5);
    else
        B_080028D0(s + 12, (u8)aa, (u8)bb);
}
__asm__(".short 0x0000");
