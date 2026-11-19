/* ProcByte_DB40 @ 0x0800DB40 (44 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave8_u_old.c (registry: src/wave8_u_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

void ProcByte_DB40(u8 *p)
{
    register u8 *pp __asm__("r2") = p;
    int i = 0;
    s8 *q;
    int v;
    s8 c;

    q = (s8 *)(pp + 33);
    c = q[i];
    if (c != 0) {
        v = 14;
        q[i] = c - 1;
    } else {
        v = ((unsigned)pp[31] << 28) >> 28;
    }
    pp += 69;
    v <<= 4;
    *pp = (*pp & 15) | v;
}
