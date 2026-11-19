/* Store5_0800EBA0 @ 0x0800EBA0 (48 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w15c_0800eba0.c (registry: src/w15c_0800eba0.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 g_02005130[];

void SetByte20_Clear21to23_02005130(u8 x);

void Store5_0800EBA0(u8 a, u8 b, u8 c, u8 d, u8 e)
{
    u8 *p = g_02005130;
    p[38] = a;
    p[39] = b;
    p[40] = c;
    p[11] = d;
    p[42] = e;
    SetByte20_Clear21to23_02005130(6);
}
