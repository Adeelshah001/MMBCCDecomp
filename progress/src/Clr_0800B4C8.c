/* Clr_0800B4C8 @ 0x0800B4C8 (28 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave8_r.c (registry: src/wave8_r.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w8r_0800b4c8")))
void Clr_0800B4C8(void) {
    u8 *p = (u8 *)0x02004E40;
    int m9 = 9;
    int m17 = 17;

    p[19] &= -m9;
    p[19] &= -m17;
    p[8] = 0xFF;
}
