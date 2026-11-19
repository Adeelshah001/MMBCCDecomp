/* G05130_SetU16_12 @ 0x0800EE38 (12 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_c.c (registry: src/wave3_c.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 g_02005130[];

__attribute__((section(".text.w3c_g05130_setu16_12")))
void G05130_SetU16_12(u16 v)
{
    u8 *p = g_02005130;

    ((u16 *)p)[9] = v;
}
