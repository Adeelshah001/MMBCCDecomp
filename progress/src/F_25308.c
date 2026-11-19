/* F_25308 @ 0x08025308 (28 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave11_A_old.c (registry: src/wave11_A_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

__attribute__((section(".text.w11a_08025308")))
void F_25308(u8 *p)
{
    u8 *q = p;
    s16 i = 0;
    u8 z = 0;
    do {
        q[i] = z;
        i++;
    } while (i <= 0xF8);
}
