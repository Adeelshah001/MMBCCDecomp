/* Check_B308 @ 0x0800B308 (24 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave9_e_old.c (registry: src/wave9_e_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 gEwram_02004E40[];

__attribute__((section(".text.w9e_800b308")))
u32 Check_B308(void)
{
    u8 v = gEwram_02004E40[4];
    if ((v & 15) == 0)
        return 1;
    return 0;
}
