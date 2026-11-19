/* Set_08004E24 @ 0x08004E24 (32 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave8_r_old.c (registry: src/wave8_r_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w8r_08004e24")))
void Set_08004E24(u8 x) {
    u8 *p = (u8 *)0x02004F80;
    u8 v;

    p[0] = (x << 7) | 64;
    v = 2;
    if (x == 0)
        v = 1;
    p[2] = v;
}
