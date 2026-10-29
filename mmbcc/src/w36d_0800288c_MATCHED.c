/* Wave 36-D v4 (barrier on d2): 0x0800288c — block-scoped src (r0) then d2 = pool, d2 = dd + d2. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void LZ77_0804DB30(u8 *src, u8 *dst);
extern void CpuFastSet_0804DB24(u8 *src, u8 *dst, u32 n);
__asm__(".set LZ77_0804DB30, 0x0804db30");
__asm__(".set CpuFastSet_0804DB24, 0x0804db24");
__attribute__((section(".text.w36d_0800288c")))
void Sub_0800288C(u8 *s, u8 *dst)
{
    register u8 *ss __asm__("r2") = s;
    register u8 *dd __asm__("r3") = dst;
    register u8 b __asm__("r1");
    register int sh __asm__("r0");
    if (*(u16 *)(ss + 4) == 0)
        return;
    b = ss[7];
    sh = b << 5;
    dd += sh;
    if (ss[6] == 0)
        goto second;
    {
        register u8 *src __asm__("r0");
        register u32 d2 __asm__("r1");
        src = ss + *(u32 *)ss;
        d2 = 0x03002420;
        __asm__ volatile("" : "+r"(d2));
        d2 = (u32)dd + d2;
        LZ77_0804DB30(src, (u8 *)d2);
    }
    return;
second:
    {
        register u8 *src __asm__("r0");
        register u32 d2 __asm__("r1");
        src = ss + *(u32 *)ss;
        d2 = 0x03002420;
        __asm__ volatile("" : "+r"(d2));
        d2 = (u32)dd + d2;
        CpuFastSet_0804DB24(src, (u8 *)d2, *(u16 *)(ss + 4) >> 2);
    }
}
