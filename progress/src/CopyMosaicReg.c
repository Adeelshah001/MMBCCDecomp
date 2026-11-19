/* CopyMosaicReg @ 0x08002EE0 (20 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_a.c (registry: src/wave3_a.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u16 gRegMosaic[];

extern u16 g_02003240[];

/* 0x08002EE0: *(u16*)REG_MOSAIC(0x0400004C) = *(u16*)0x02003240. Tentative. */
__attribute__((section(".text.w3a_copymosaicreg")))
void CopyMosaicReg(void)
{
    u16 *dst = gRegMosaic;
    u16 *src = g_02003240;
    *dst = *src;
}
