/* G05130_GetS8_0A @ 0x0800EAB4 (16 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_c.c (registry: src/wave3_c.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 g_02005130[];

__attribute__((section(".text.w3c_g05130_gets8_0a")))
s8 G05130_GetS8_0A(void)
{
    u8 *p = g_02005130;

    return (s8)p[0x0A];
}
