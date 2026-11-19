/* Test_08010454 @ 0x08010454 (36 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave8_r_old.c (registry: src/wave8_r_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w8r_08010454")))
int Test_08010454(u8 x) {
    u8 *p = (u8 *)0x02005168;

    if (x == 1)
        p += 20;
    if ((p[16] & 2) == 0)
        return 0;
    return 1;
}
