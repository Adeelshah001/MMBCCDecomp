/* Classify_3FD68 @ 0x0803FD68 (52 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave9_e_old.c (registry: src/wave9_e_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w9e_803fd68")))
u32 Classify_3FD68(u16 x)
{
    u16 xr = x;
    int sxr = xr;
    if (xr == 37)
        goto L1;
    if (sxr > 37)
        goto Lgt;
    if (xr == 18)
        goto L4;
    goto Ldef;
Lgt:
    if (xr == 67)
        goto L5;
    if (xr == 0x2004)
        goto L4;
    goto Ldef;
L1:
    return 1;
L4:
    return 4;
L5:
    return 5;
Ldef:
    return xr >> 12;
}
