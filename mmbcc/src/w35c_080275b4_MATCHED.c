/* Wave 35-C v2: 0x080275b4 — a1 computed before tbl pool load */
typedef unsigned char u8;
typedef unsigned int u32;
extern void Worker_0800DEA4(u32 a, u32 b, u32 c, u32 d, u32 e, u32 f, u32 g);
extern void Worker_0800DD74(u32 a, u32 b);
__asm__(".set Worker_0800DEA4, 0x0800dea4");
__asm__(".set Worker_0800DD74, 0x0800dd74");
__attribute__((section(".text.w35c_080275b4")))
void Sub_080275B4(void)
{
    u32 base = 0x020038ac;
    u32 arg0 = 0x0871e4e4;
    u32 a1 = *(u32 *)(base + 4);
    u32 tbl = 0x0871c8a4;
    Worker_0800DEA4(arg0, a1, 1, 1,
        *(u32 *)tbl + tbl, *(u32 *)base, 32);
    Worker_0800DD74(0x03002440, 0x03002440);
}
