/* ChipInit_0801C540 @ 0x0801C540 (44 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w15c_0801c540.c (registry: src/w15c_0801c540.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Wrapper_D770(u8 *p, u16 x, u8 y);

extern void ChipSlot_IncUse(u8 *p, u8 x);

__attribute__((section(".text.w15c2_0801C540")))
void ChipInit_0801C540(u8 *p)
{
    u8 b;
    Wrapper_D770(p, 0x82a, 0);
    ChipSlot_IncUse(p, 0);
    b = p[10];
    b &= 253;
    b &= 254;
    p[10] = b;
}
