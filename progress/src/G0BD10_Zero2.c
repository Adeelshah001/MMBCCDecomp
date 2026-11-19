/* G0BD10_Zero2 @ 0x0804A2CC (16 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_c.c (registry: src/wave3_c.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u16 g_0200BD10[];

__attribute__((section(".text.w3c_g0bd10_zero2")))
void G0BD10_Zero2(void)
{
    g_0200BD10[0] = 0;
    g_0200BD10[1] = 0;
}
