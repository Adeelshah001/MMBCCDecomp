/* Step_0801e93c @ 0x0801E93C (52 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36a_0801e93c_MATCHED.c (registry: mmbcc/src/w36a_0801e93c_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void ChipSlot_Tick(u8 *s);

extern u32 Tbl_082243D8[];

__attribute__((section(".text.w36a_0801e93c")))
void Step_0801e93c(u8 *s)
{
    ChipSlot_Tick(s);
    if ((u8)(s[119] - 3) <= 1) {
        u32 *entry = (u32 *)Tbl_082243D8[s[9]];
        *(u32 *)(s + 12) = 2;
        *(u32 *)(s + 20) = *(u32 *)((u8 *)entry + 8);
    }
}
