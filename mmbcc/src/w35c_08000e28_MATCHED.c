/* Wave 35-C v4: 0x08000e28 — idx in r0 via unnamed load, k in r1, base+=0x1e08 in r2 */
typedef unsigned char u8;
typedef unsigned int u32;
extern void Worker_08000300(u8 *a, u8 *b, u32 c);
__asm__(".set Worker_08000300, 0x08000300");
__attribute__((section(".text.w35c_08000e28")))
void Sub_08000E28(void)
{
    register u32 *base __asm__("r2") = (u32 *)0x030005c0;
    u32 k = *(u32 *)((u8 *)base + 0x1e50) * 24;
    u8 *p;
    base = (u32 *)((u8 *)base + 0x1e08);
    p = (u8 *)(k + (u32)base);
    *p = 1;
    Worker_08000300(p + 4, p + 8, *(u32 *)0x02000800);
}
