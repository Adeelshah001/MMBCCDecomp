/* Count_08042a38 @ 0x08042A38 (42 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave14_C.c (registry: src/wave14_C.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* Count_08042a38 @ 0x08042a38 */
u8 TblStride_24818(u8 i);

__attribute__((section(".text.w14c_08042a38")))
u8 Count_08042a38(void)
{
    u8 c = 0;
    u8 i = 0;
    do {
        if (TblStride_24818(i))
            c++;
        i++;
    } while (i <= 0x1d);
    return c;
}
