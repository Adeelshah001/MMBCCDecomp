/* Wave 36-D v3 (mask-first split): 0x080050f0 — nb pinned r1, block-scoped after first test. */
typedef unsigned char u8;
extern void Worker_08005130(u8 *base);
extern void Worker_08005208(u8 *base);
__asm__(".set Worker_08005130, 0x08005130");
__asm__(".set Worker_08005208, 0x08005208");
__attribute__((section(".text.w36d_080050f0")))
void Sub_080050F0(void)
{
    register u8 *base __asm__("r3") = (u8 *)0x02003670;
    register u8 *p __asm__("r4") = base + 0x11ae;
    register int b __asm__("r2") = *p;
    if ((b & 2) == 0)
        return;
    {
        register int nb __asm__("r1");
        nb = ~2;
        nb &= b;
        *p = nb;
        if ((nb & 248) != 8)
            Worker_08005130(base);
        else
            Worker_08005208(base);
    }
}
