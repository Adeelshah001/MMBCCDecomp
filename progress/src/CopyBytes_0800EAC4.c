/* CopyBytes_0800EAC4 @ 0x0800EAC4 (48 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w15c_0800eac4.c (registry: src/w15c_0800eac4.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 g_02005130[];

extern u8 g_02005168[];

void SetByte20_Clear21to23_02005130(u8 x);

void CopyBytes_0800EAC4(u8 a, u8 b)
{
    g_02005130[6] = a;
    g_02005130[4] = a;
    g_02005130[7] = b;
    g_02005130[5] = b;
    g_02005168[10] = g_02005130[8];
    g_02005168[30] = g_02005130[9];
    SetByte20_Clear21to23_02005130(1);
}
