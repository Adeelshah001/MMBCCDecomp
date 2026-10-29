/* Wave 35-B v2: 0x0802d488 explicit-shift pins aa->r4, bb->r0, r->r5. */
typedef unsigned char u8;
typedef unsigned int u32;

extern u8 Worker_0802D574(void);
__asm__(".set Worker_0802D574, 0x0802d574");

__attribute__((section(".text.w35b_0802d488")))
int Sub_0802D488(u8 a, u8 b)
{
    register u32 aa __asm__("r4") = ((u32)a << 24) >> 24;
    register u32 bb __asm__("r0") = ((u32)b << 24) >> 24;
    register int r __asm__("r5") = 0;
    if (aa == 5)
    {
        if (bb == 3 || bb == 1)
            r = 3;
    }
    else
    {
        if (aa == Worker_0802D574())
            r = 6;
    }
    return r;
}
__asm__(".short 0x0000");
