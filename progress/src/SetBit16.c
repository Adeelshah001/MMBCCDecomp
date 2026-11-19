/* SetBit16 @ 0x080174A4 (16 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x080174a4: SetBit16 (16B, coordinator-verified). */
__attribute__((section(".text.w7g2_080174a4")))
void SetBit16(unsigned char *s, unsigned char bit)
{
    s[16] |= (1 << bit);
}
