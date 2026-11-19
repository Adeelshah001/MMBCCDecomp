/* Sub_0801D464 @ 0x0801D464 (36 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34c_0801d464_MATCHED.c (registry: staging/wave34_C/w34c_0801d464_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Func_0801D488(u8 *s);

extern void sub_0801D598(u8 *s);

extern void ChipSlot_Tick(u8 *s);

__attribute__((section(".text.w34c_0801d464")))
void Sub_0801D464(u8 *s)
{
    if (s[17] == 0)
        Func_0801D488(s);
    else
        sub_0801D598(s);
    ChipSlot_Tick(s);
}
