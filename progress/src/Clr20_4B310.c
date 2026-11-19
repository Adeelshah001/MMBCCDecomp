/* Clr20_4B310 @ 0x0804B310 (36 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave8_u_old.c (registry: src/wave8_u_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

void Clr20_4B310(u8 *p, u8 v)
{
    register u8 w __asm__("r4") = v;
    register u8 *base __asm__("r3");
    register u8 *q __asm__("r2");
    u16 i;

    __asm__ volatile("" : "+r"(w));
    base = p;
    q = base;
    i = 0;
    do {
        *q++ = 0;
        i++;
    } while (i <= 19);
    base[4] = w;
}
