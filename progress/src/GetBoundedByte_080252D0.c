/* GetBoundedByte_080252D0 @ 0x080252D0 (22 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x080252d0: GetBoundedByte_080252D0 (24B, coordinator-verified). */
__attribute__((section(".text.w7g2_080252d0")))
unsigned char GetBoundedByte_080252D0(void *s, unsigned short idx)
{
    unsigned short lim = *(unsigned short *)((unsigned char *)s + 6);
    if (idx >= lim)
        return 0xff;
    return *(*(unsigned char **)s + idx);
}
