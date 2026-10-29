/* W58-B H6 (H5 + trailing-pad asm, w36b/w57c convention): 0x080067BC, TRUE extent 308 B (code thru bx @0x68ec + 2 B pad
 * @0x68ee; next fn @0x68f0). Bounds/clamp helper: p0 passed to two getters
 * (FlagA_8628/8680, results g1/g2); p3 and arg5 must be nonzero; signed
 * offsets p1/p2 must satisfy -p3 < (s8)p1 < g1 and -arg5 < (s8)p2 < g2, else
 * early return. Negative offsets are clamped to 0 (flags bit 4 for p1,
 * bit 1 for p2); coords p3/arg5 are adjusted by the offsets (u8 wrap) and
 * clamped to g1/g2 (flags bits 8/2). Dispatch on arg6: <=1 or ==3 calls
 * 0x08008bc8 with (p0, (s8)p1, (s8)p2, p3, arg5, flags,
 * ((u32)arg7 << 28) >> 16, arg6) [8 args], else 0x0800909c with the same
 * first 7 args and NO arg6 [7 args — the second callee takes no mode
 * argument; its [sp,#12] setup is absent in ROM]. Getter returns declared
 * u8 here (caller zero-extends; wave8's defs return s8 — coordinator to
 * reconcile; ROM's post-call lsls/lsrs zero-extension supports u8 here).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;

extern u8 FlagA_8628(u8 *p);
extern u8 FlagA_8680(u8 *p);
extern void Sub_08008BC8(u8 *p0, s8 p1, s8 p2, u8 p3, u8 arg5, u8 flags, u32 x, u8 arg6);
__asm__(".set Sub_08008BC8, 0x08008bc8");
extern void Sub_0800909C(u8 *p0, s8 p1, s8 p2, u8 p3, u8 arg5, u8 flags, u32 x);
__asm__(".set Sub_0800909C, 0x0800909c");

__attribute__((section(".text.w58b_080067bc")))
void Sub_080067BC(u8 *p0, u8 p1, u8 p2, u8 p3, u8 arg5, u8 arg6, u16 arg7)
{
    u8 flags = 0;
    u8 g1 = FlagA_8628(p0);
    u8 g2 = FlagA_8680(p0);

    if (p3 == 0 || arg5 == 0)
        return;
    if (-p3 >= (s8)p1)
        return;
    if ((s8)p1 >= g1)
        return;
    if (-arg5 >= (s8)p2)
        return;
    if ((s8)p2 >= g2)
        return;
    if ((s8)p1 < 0) {
        p3 = (u8)(p3 + p1);
        p1 = 0;
        flags = 4;
    }
    if ((s8)p2 < 0) {
        arg5 = (u8)(arg5 + p2);
        p2 = 0;
        flags |= 1;
    }
    p3 = (u8)(p3 + p1);
    if (p3 > g1) {
        p3 = g1;
        flags |= 8;
    }
    arg5 = (u8)(arg5 + p2);
    if (arg5 > g2) {
        arg5 = g2;
        flags |= 2;
    }
    if (arg6 <= 1 || arg6 == 3)
        Sub_08008BC8(p0, (s8)p1, (s8)p2, p3, arg5, flags, (((u32)arg7 << 28) >> 16), arg6);
    else
        Sub_0800909C(p0, (s8)p1, (s8)p2, p3, arg5, flags, (((u32)arg7 << 28) >> 16));
}

__asm__(".section .text.w58b_080067bc\n\t.byte 0, 0\n\t.previous");
