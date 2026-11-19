/* CheckPair_258D8 @ 0x080258D8 (32 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave9_d_old.c (registry: src/wave9_d_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w9d_080258d8")))
u8 CheckPair_258D8(u8 *p, u16 idx)
{
    u32 off = ((u32)idx << 16) >> 14;
    u8 *q;
    off += 20;
    q = p + off;
    if (q[0] == 0)
        return 0;
    if (q[1] == 255)
        return 1;
    return 2;
}
