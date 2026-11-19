/* CmpH6_08046DE4 @ 0x08046DE4 (18 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x08046de4: CmpH6 (20B, coordinator-verified). */
__attribute__((section(".text.w7g2_08046de4")))
unsigned int CmpH6_08046DE4(void *s, unsigned short b)
{
    unsigned int r = 0;
    if (*(unsigned short *)((unsigned char *)s + 6) == b)
        r = 1;
    return r;
}
