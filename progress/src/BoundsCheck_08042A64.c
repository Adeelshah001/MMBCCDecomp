/* BoundsCheck_08042A64 @ 0x08042A64 (100 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34d_08042a64.c (registry: staging/wave34_A/).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed int s32;

__attribute__((section(".text.w34d_08042a64")))
u32 BoundsCheck_08042A64(u8 a, u8 b, u8 c, u8 d)
{
    register u32 bb __asm__("r4") = ((u32)b << 24) >> 24;
    register u32 dd __asm__("r5") = ((u32)d << 24) >> 24;
    register u8 *base __asm__("r7");
    register s32 b1 __asm__("r3");
    register s32 b2 __asm__("r2");
    register s32 sb __asm__("r4");
    int off;
    s32 sa, sac;

    __asm__ volatile("" : "+r"(base));
    base = (u8 *)0x02003670;
    if (c == 0 || dd == 0)
        return 0;
    sa = (s8)a;
    sac = sa + (s32)c;
    off = 0x11ac;
    __asm__ volatile("" : "+r"(off));
    b1 = *(s8 *)(off + base);
    if (sac <= b1)
        return 0;
    {
        register u32 t0 __asm__("r0");
        t0 = bb << 24;
        sb = (s32)t0 >> 24;
    }
    {
        register s32 s __asm__("r1");
        s = sb + (s32)dd;
        off++;
        b2 = *(s8 *)(off + base);
        if (s <= b2)
            return 0;
    }
    {
        register s32 t1 __asm__("r0") = b1;
        t1 += 28;
        if (sa >= t1)
            return 0;
    }
    {
        register s32 t2 __asm__("r0") = b2;
        t2 += 20;
        if (sb < t2)
            return 1;
    }
    return 0;
}
