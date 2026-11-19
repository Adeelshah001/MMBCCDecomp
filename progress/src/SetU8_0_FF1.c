/* SetU8_0_FF1 @ 0x080256D4 (8 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_c.c (registry: src/wave3_c.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w3c_setu8_0_ff1")))
void SetU8_0_FF1(u8 *s, u8 v)
{
    s[0] = v;
    s[1] = 0xFF;
}
