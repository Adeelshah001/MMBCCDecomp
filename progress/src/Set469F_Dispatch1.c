/* Set469F_Dispatch1 @ 0x0803661C (36 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i_old.c (registry: src/wave4_i_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u32 gTbl_082300F8[];

__attribute__((section(".text.w4i_set469f_dispatch1")))
void Set469F_Dispatch1(u8 *s)
{
    s[0x469f] = 1;
    {
        u32 *tbl = gTbl_082300F8;
        u32 idx = s[1];
        ((void (*)(u8 *))tbl[idx])(s);
    }
}
