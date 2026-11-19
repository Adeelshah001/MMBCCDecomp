/* Sub_080067BC @ 0x080067BC (306 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w58b_080067bc_MATCHED.c (registry: src/w58b_080067bc_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 FlagA_8628(u8 *p);

extern u8 FlagA_8680(u8 *p);

extern void sub_08008BC8(u8 *p0, s8 p1, s8 p2, u8 p3, u8 arg5, u8 flags, u32 x, u8 arg6);

extern void sub_0800909C(u8 *p0, s8 p1, s8 p2, u8 p3, u8 arg5, u8 flags, u32 x);

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
        sub_08008BC8(p0, (s8)p1, (s8)p2, p3, arg5, flags, (((u32)arg7 << 28) >> 16), arg6);
    else
        sub_0800909C(p0, (s8)p1, (s8)p2, p3, arg5, flags, (((u32)arg7 << 28) >> 16));
}
