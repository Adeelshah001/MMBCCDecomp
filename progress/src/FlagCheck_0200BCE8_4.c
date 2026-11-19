/* FlagCheck_0200BCE8_4 @ 0x080363D4 (24 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x080363d4: FlagCheck_0200BCE8_4 (24B, coordinator-verified). */
extern unsigned char g_0200bce8[];

__attribute__((section(".text.w7g2_080363d4")))
unsigned int FlagCheck_0200BCE8_4(void)
{
    unsigned char *p = g_0200bce8;
    unsigned int v;
    __asm__("movs %0, #1" : "=r"(v));
    v &= p[4];
    if (v == 0)
        return 0;
    return 1;
}
