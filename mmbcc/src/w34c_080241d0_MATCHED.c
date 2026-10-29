/* Wave 34-C v1: 0x080241d0 — r=A(aa,0); if (!r) r=B(aa); return r (u8). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern int A_080242A8(u16 a, int zero);
extern int B_080241F8(u16 a);
__asm__(".set A_080242A8, 0x080242a8");
__asm__(".set B_080241F8, 0x080241f8");

__attribute__((section(".text.w34c_080241d0")))
u8 Sub_080241D0(u32 a)
{
    u16 aa = a;
    u8 r = A_080242A8(aa, 0);
    if (r == 0)
        r = B_080241F8(aa);
    return r;
}
__asm__(".short 0x0000");
