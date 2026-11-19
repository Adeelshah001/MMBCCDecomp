/* Clear126_127_160_Set161_0200BD20 @ 0x0804AC48 (28 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x0804a494: Clear126_127_Set131 (28B, coordinator-verified). */
extern unsigned char gEwram_0200BD20[];

__attribute__((section(".text.w7g2_0804ac48")))
void Clear126_127_160_Set161_0200BD20(unsigned char v)
{
    unsigned char *p = gEwram_0200BD20;
    p[127] = 0;
    p[126] = 0;
    p[160] = 0;
    p[161] = v;
}
