/* CountNonzeroStride @ 0x0804580C (42 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w16b_0804580c.c (registry: src/w16b_0804580c.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 TblStride_24818(u16 idx);

u8 CountNonzeroStride(void)
{
    u8 n = 0;
    u8 i = 0;
    do {
        if (TblStride_24818(i))
            n = n + 1;
        i = i + 1;
    } while (i <= 29);
    return n;
}
