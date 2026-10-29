/* Wave 34-C v1: 0x0800c588 — worker(b, (u16)c, 4, 4, 2). 28 B (0x0800c5a4 is next fn). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void Worker_0800C268(u32 b, u16 c, int d, int e, int f);
__asm__(".set Worker_0800C268, 0x0800c268");

__attribute__((section(".text.w34c_0800c588")))
void Sub_0800C588(int dummy, u32 b, u32 c)
{
    u32 bb = b;
    u16 cc = c;
    Worker_0800C268(bb, cc, 4, 4, 2);
}
