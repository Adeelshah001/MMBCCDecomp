/* Wave 34-C v1: 0x08021780 — worker(base+v+68, (w<<5)+0x10000). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void Worker_0800244C(u8 *p, u32 x);
__asm__(".set Worker_0800244C, 0x0800244c");

__attribute__((section(".text.w34c_08021780")))
void Sub_08021780(void)
{
    u8 *p = (u8 *)0x08173760;
    u32 base = *(u32 *)(p + 108);
    u32 t = *(u32 *)(base + 68);
    u8 *q;
    u32 w;
    t += 68;
    base += t;
    q = (u8 *)0x0817386c;
    w = *(u16 *)(q + 54);
    Worker_0800244C((u8 *)base, (w << 5) + 0x10000);
}
