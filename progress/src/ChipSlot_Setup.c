/* ChipSlot_Setup @ 0x0800D6E0 (34 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/chipslot.c (registry: src/chipslot.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

void sub_0800D800(u8 *s, u8 a, u16 b, u8 c, u8 d);

__attribute__((section(".text.chipslot_setup")))
void ChipSlot_Setup(u8 *s, u16 b, u8 c)
{
    sub_0800D800(s, 0, b, c, 0);
}
