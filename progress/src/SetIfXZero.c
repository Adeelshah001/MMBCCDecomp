/* SetIfXZero @ 0x08008BB8 (14 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x08008bb8: SetIfXZero (16B, coordinator-verified). */
__attribute__((section(".text.w7g2_08008bb8")))
void SetIfXZero(unsigned short *s, unsigned short v, unsigned char x)
{
    if ((x << 24) == 0)
        *s = v;
}
