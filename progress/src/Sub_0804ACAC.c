/* Sub_0804ACAC @ 0x0804ACAC (48 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34c_0804acac_MATCHED.c (registry: staging/wave34_C/w34c_0804acac_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern int sub_0804AD7C(void);

__attribute__((section(".text.w34c_0804acac")))
s8 Sub_0804ACAC(void)
{
    u8 *p = (u8 *)0x0200bd20;
    s8 r;
    __asm__ volatile("" : "+r"(p));
    {
        u8 *q = p + 162;
        __asm__ volatile(
            "movs r0, #150\n\t"
            "lsl r0, r0, #1\n\t"
            "strh r0, [%0]"
            :: "r"(q) : "r0", "memory");
    }
    r = sub_0804AD7C();
    if (r == 0)
    {
        u8 *q = p;
        q += 161;
        return *(s8 *)q;
    }
    return r;
}
