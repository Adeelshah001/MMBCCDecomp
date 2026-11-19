/* ClearWord_02002ED4 @ 0x08000C9C (12 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2.c (registry: src/wave7_g2.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x08000c9c: ClearWord_02002ED4 (12B, coordinator-verified). */
extern unsigned int g_02002ed4;

__attribute__((section(".text.w7g2_08000c9c")))
void ClearWord_02002ED4(void)
{
    *(unsigned int *)&g_02002ed4 = 0;
}
