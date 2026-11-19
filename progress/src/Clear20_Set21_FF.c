/* Clear20_Set21_FF @ 0x08025994 (16 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x08025994: Clear20_Set21_FF (16B, coordinator-verified). */
__attribute__((section(".text.w7g2_08025994")))
void Clear20_Set21_FF(unsigned char *s, unsigned short idx)
{
    unsigned int off = idx * 4;
    register unsigned char *p __asm__("r1") = (unsigned char *)off;
    p = (unsigned char *)((unsigned int)p + (unsigned int)s);
    p[20] = 0;
    p[21] = 0xff;
}
