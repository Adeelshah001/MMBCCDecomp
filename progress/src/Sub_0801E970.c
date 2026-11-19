/* Sub_0801E970 @ 0x0801E970 (32 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w37b_0801e970_MATCHED.c (registry: mmbcc/src/w37b_0801e970_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w37b_0801e970")))
void Sub_0801E970(u8 *s)
{
    u32 *base;
    u32 *p;
    s[10] &= 254;
    base = (u32 *)0x082243d8;
    __asm__ volatile("" : "+r"(base));
    p = base + s[9];
    *(u32 *)(s + 12) = 4;
    *(u32 *)(s + 20) = *(u32 *)(*p + 16);
}
