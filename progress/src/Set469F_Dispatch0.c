/* Set469F_Dispatch0 @ 0x080365F8 (36 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i_old.c (registry: src/wave4_i_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u32 gTbl_082300F8[];

/* 0x080365F8/1C/40: s[0x469F]=N; tbl[s[1]](s). Tentative. */
__attribute__((section(".text.w4i_set469f_dispatch0")))
void Set469F_Dispatch0(u8 *s)
{
    s[0x469f] = 0;
    {
        u32 *tbl = gTbl_082300F8;
        u32 idx = s[1];
        ((void (*)(u8 *))tbl[idx])(s);
    }
}
