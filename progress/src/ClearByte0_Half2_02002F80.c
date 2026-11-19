/* ClearByte0_Half2_02002F80 @ 0x08001D88 (16 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2.c (registry: src/wave7_g2.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x08001d88: ClearByte0_Half2_02002F80 (16B, coordinator-verified). */
extern unsigned char gEwram_02002F80[];

__attribute__((section(".text.w7g2_08001d88")))
void ClearByte0_Half2_02002F80(unsigned int dummy)
{
    unsigned char *p = gEwram_02002F80;
    unsigned int zero = 0;
    p[0] = zero;
    *(unsigned short *)(p + 2) = zero;
}
