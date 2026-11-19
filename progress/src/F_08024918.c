/* F_08024918 @ 0x08024918 (34 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave15_B.c (registry: src/wave15_B.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void F_25490(u8 *p, u8 a, u8 b);

__attribute__((section(".text.w15b_08024918")))
u8 F_08024918(u8 *p, u8 b, u8 c)
{
    u16 lim = *(u16 *)(p + 18);
    if (b >= lim)
        return 1;
    if (c >= lim)
        return 1;
    F_25490(p, b, c);
    return 0;
}
