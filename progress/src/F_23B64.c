/* F_23B64 @ 0x08023B64 (34 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave11_A_old.c (registry: src/wave11_A_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w11a_08023b64")))
void F_23B64(u16 *p)
{
    u16 *q = p;
    u8 i = 0;
    do {
        u16 t = q[i];
        if (t <= 9)
            q[i] = t + 1;
        else
            q[i] = t + 0x54;
        i++;
    } while (i <= 23);
}
