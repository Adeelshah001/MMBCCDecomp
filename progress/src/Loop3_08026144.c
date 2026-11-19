/* Loop3_08026144 @ 0x08026144 (40 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w18b_08026144.c (registry: src/w18b_08026144.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Sub_257FC(u8 *s, u16 v);

__attribute__((section(".text.w18b_08026144")))
void Loop3_08026144(u8 *p, u16 x)
{
    u8 i = 0;
    do {
        Sub_257FC(p + i * 144, x);
        i = (u8)(i + 1);
    } while (i <= 2);
}
