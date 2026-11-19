/* Get_0802503C @ 0x0802503C (24 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave6_l4_old.c (registry: src/wave6_l4_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x0802503c: Get_0802503C (coordinator-verified). */
u16 Sub80_Field22(u8 *s);

extern u8 ew02007090[];

__attribute__((section(".text.w6l4_0802503c")))
u16 Get_0802503C(void)
{
    u8 *p = ew02007090;
    p += 24;
    return Sub80_Field22(p);
}
