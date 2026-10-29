/* Wave 34-C v1: 0x080253f8 — s->w0=b; s->w8=b+249; s->w4=b+498; C(); D(s). */
typedef unsigned char u8;
typedef unsigned int u32;

extern void C_08025308(void);
extern void D_0802538C(u8 *s);
__asm__(".set C_08025308, 0x08025308");
__asm__(".set D_0802538C, 0x0802538c");

__attribute__((section(".text.w34c_080253f8")))
void Sub_080253F8(u8 *s, u32 b)
{
    u32 c = b;
    __asm__ volatile("" : "+r"(c));
    *(u32 *)s = c;
    b += 249;
    *(u32 *)(s + 8) = b;
    b = c + 498;
    *(u32 *)(s + 4) = b;
    C_08025308();
    D_0802538C(s);
}
