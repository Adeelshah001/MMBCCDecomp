/* Wave 34-C v1: 0x0800d7b8 — worker(s, 1, (u16)b, (u8)c, 0). */
typedef unsigned char u8;
typedef unsigned short u16;

extern void Worker_0800D800(u8 *s, int one, u16 b, u8 c, int zero);
__asm__(".set Worker_0800D800, 0x0800d800");

__attribute__((section(".text.w34c_0800d7b8")))
void Sub_0800D7B8(u8 *s, int b, int c)
{
    u16 bb = b;
    u8 cc = c;
    Worker_0800D800(s, 2, bb, cc, 1);
}
