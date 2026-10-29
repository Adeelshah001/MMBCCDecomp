/* Wave 35-C v2: 0x08026dbc — ordered locals to force pool/load order */
typedef unsigned int u32;
extern void Worker_0800DEA4(void *a, u32 b, int c, int d, u32 e, u32 f, int g);
__asm__(".set Worker_0800DEA4, 0x0800dea4");
__attribute__((section(".text.w35c_08026dbc")))
void Sub_08026DBC(void)
{
    u32 *base = (u32 *)0x020038ac;
    void *a0 = (void *)0x0871e4e4;
    u32 b1 = base[1];
    u32 *tbl = (u32 *)0x0871c8a4;
    u32 t = *tbl + (u32)tbl;
    Worker_0800DEA4(a0, b1, 1, 1, t, base[0], 32);
}
