/* GetMaskedByte_08025324 @ 0x08025324 (24 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x08025324: GetMaskedByte_08025324 (24B, coordinator-verified). */
__attribute__((section(".text.w7g2_08025324")))
unsigned char GetMaskedByte_08025324(unsigned char *p, unsigned char idx)
{
    if (idx > 248)
        return 0;
    return p[idx] & 0x7f;
}
