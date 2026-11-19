/* SetNibbleAndLookup_B6F4 @ 0x0800B6F4 (56 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave8_u_old.c (registry: src/wave8_u_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 g_0817310C[];

void SetNibbleAndLookup_B6F4(u8 *p, u8 x)
{
    int m15 = 15;
    int v1 = x & m15;
    int m16 = 16;

    p[18] = (p[18] & -m16) | v1;
    {
        u8 *tbl = g_0817310C;
        u8 *e = *(u8 **)(tbl + x * 12);

        p[18] &= m15;
        p[17] = e[1];
    }
}
