/* F_0802533c @ 0x0802533C (60 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave14_C_old.c (registry: src/wave14_C_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* F_0802533c @ 0x0802533c */
void IncMod128_080252E8(u8 *p);

__attribute__((section(".text.w14c_0802533c")))
void F_0802533c(u8 *p, u8 idx)
{
    u8 *q;
    if (idx > 0xf8) return;
    if (idx > 0xc7) {
        q = p + idx;
        if ((*q & 0x7f) > 0x62) return;
        IncMod128_080252E8(q);
    } else {
        q = p + idx;
        if ((*q & 0x7f) > 0x62) return;
        IncMod128_080252E8(q);
    }
}
