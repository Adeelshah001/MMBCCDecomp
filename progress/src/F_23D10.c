/* F_23D10 @ 0x08023D10 (34 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave11_A_old.c (registry: src/wave11_A_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w11a_08023d10")))
u8 F_23D10(u8 *p)
{
    u8 *q = p;
    u8 sum = 0;
    u8 i = 0;
    do {
        sum += q[i];
        i++;
    } while (i <= 13);
    return -sum;
}
