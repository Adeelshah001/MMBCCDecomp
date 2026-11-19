/* SetEwram5130_12 @ 0x0800EDE4 (12 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_a.c (registry: src/wave3_a.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 g_02005130[];

/* 0x0800EDE4: *(u16*)(0x02005130+12) = v. Tentative. */
__attribute__((section(".text.w3a_setewram5130_12")))
void SetEwram5130_12(u16 v)
{
    u8 *base = g_02005130;
    *(u16 *)(base + 12) = v;
}
