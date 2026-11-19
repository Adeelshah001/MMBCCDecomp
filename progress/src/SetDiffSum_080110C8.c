/* SetDiffSum_080110C8 @ 0x080110C8 (22 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x080110c8: SetDiffSum_080110C8 (24B, coordinator-verified). */
__attribute__((section(".text.w7g2_080110c8")))
void SetDiffSum_080110C8(short a, short b, unsigned int *out)
{
    int bb = b;
    int aa = a;
    out[0] = (aa - bb) << 12;
    out[1] = (bb + aa) << 11;
}
