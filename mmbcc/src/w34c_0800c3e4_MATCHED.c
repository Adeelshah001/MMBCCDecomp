/* Wave 34-C v1: 0x0800c3e4 — three Worker_080006DC calls. */
typedef unsigned char u8;
typedef unsigned int u32;

extern void Worker_080006DC(u32 a, u32 b, int c);
__asm__(".set Worker_080006DC, 0x080006dc");

__attribute__((section(".text.w34c_0800c3e4")))
void Sub_0800C3E4(void)
{
    u32 *p1 = (u32 *)0x000014a5;
    u32 *p2 = (u32 *)0x03002440;
    u32 *p3;
    Worker_080006DC((u32)p1, (u32)p2, 32);
    p3 = (u32 *)0x020038ac;
    Worker_080006DC(0, *(p3 + 1), 32);
    Worker_080006DC(4096, *p3, 2048);
}
