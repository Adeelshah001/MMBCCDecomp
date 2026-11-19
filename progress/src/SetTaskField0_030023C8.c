/* SetTaskField0_030023C8 @ 0x08000E64 (28 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x08000e64: SetTaskField0_030023C8 (28B, coordinator-verified). */
extern unsigned char g_030023C8[];

__attribute__((section(".text.w7g2_08000e64")))
void SetTaskField0_030023C8(unsigned int idx)
{
    unsigned char *p = g_030023C8 + idx * 24;
    if (p[0] != 1)
        p[0] = 1;
}
