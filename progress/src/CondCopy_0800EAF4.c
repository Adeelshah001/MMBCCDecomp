/* CondCopy_0800EAF4 @ 0x0800EAF4 (48 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w15c_0800eaf4.c (registry: src/w15c_0800eaf4.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 g_02005130[];

void SetByte20_Clear21to23_02005130(u8 x);

void CondCopy_0800EAF4(u8 x, u8 y)
{
    u8 *p = g_02005130;
    if (p[4] != x || p[5] != y)
    {
        p[6] = x;
        p[7] = y;
        SetByte20_Clear21to23_02005130(2);
    }
}
