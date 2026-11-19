/* SetBit2_08007CDC @ 0x08007CDC (24 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x08007cdc: SetBit2 (24B, coordinator-verified). */
extern unsigned char g_02004e18[];

__attribute__((section(".text.w7g2_08007cdc")))
void SetBit2_08007CDC(unsigned short v)
{
    unsigned char *p = g_02004e18 + v * 8;
    p[7] |= 4;
}
