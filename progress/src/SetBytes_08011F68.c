/* SetBytes_08011F68 @ 0x08011F68 (20 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x08011f68: SetBytes_08011F68 (20B, coordinator-verified). */
__attribute__((section(".text.w7g2_08011f68")))
void SetBytes_08011F68(unsigned char *s, unsigned char v)
{
    unsigned char *p = s + 124;
    unsigned int z;
    __asm__ volatile("movs %0, #0" : "=r"(z));
    s[13] = v;
    s[14] = z;
    s[15] = z;
    p[5] = v;
}
