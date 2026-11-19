/* Sub_080112CC @ 0x080112CC (46 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36d_080112cc_MATCHED.c (registry: src/w36d_080112cc_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern s8 sub_08010FB4(u8 i);

__attribute__((section(".text.w36d_080112cc")))
int Sub_080112CC(void)
{
    int found = 0;
    s8 i;
    for (i = 0; i <= 6; i++) {
        if (sub_08010FB4((u8)i) != 1)
            found = 1;
    }
    return found;
}
