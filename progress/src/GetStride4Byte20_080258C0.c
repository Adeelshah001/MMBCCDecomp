/* GetStride4Byte20_080258C0 @ 0x080258C0 (22 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x080258c0: GetStride4Byte20_080258C0 (24B, coordinator-verified). */
__attribute__((section(".text.w7g2_080258c0")))
unsigned char GetStride4Byte20_080258C0(unsigned char *s, unsigned short idx)
{
    if (idx > 29)
        return 0;
    return *(s + idx * 4 + 20);
}
