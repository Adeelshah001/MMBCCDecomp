/* F_0802663c @ 0x0802663C (48 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave14_C.c (registry: src/wave14_C.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* F_0802663c @ 0x0802663c */
u8 GetBoundedByte_080252D0(u8 *p);

__attribute__((section(".text.w14c_0802663c")))
u8 F_0802663c(u8 *p, u16 v)
{
    u8 w;
    u32 t;
    register u8 *q __asm__("r2");
    if (v >= *(u16 *)(p + 0x16))
        return 1;
    w = GetBoundedByte_080252D0(p + 0x10);
    q = *(u8 **)(p + 4);
    t = w * 7;
    t *= 4;
    t += (u32)q;
    return *(u8 *)(t + 0x18);
}
