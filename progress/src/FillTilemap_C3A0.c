/* FillTilemap_C3A0 @ 0x0800C3A0 (68 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave12_C_old.c (registry: src/wave12_C_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x0800C3A0: fill 28x32 u16 tilemap with ((b + col) | 0x1000). */
__attribute__((section(".text.w12c_0800c3a0")))
void FillTilemap_C3A0(unsigned short *base, unsigned short b)
{
    short i = 0;
    do {
        unsigned short *p = base + i * 32;
        short j;
        j = 0;
        do {
            *p++ = (b + j) | 0x1000;
            j++;
        } while (j <= 31);
        i++;
    } while (i <= 27);
}
