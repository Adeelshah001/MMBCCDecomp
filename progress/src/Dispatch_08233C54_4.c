/* Dispatch_08233C54_4 @ 0x08047CA4 (28 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i_old.c (registry: src/wave4_i_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u32 gTbl_08233C54[];

/* 0x08047CA4 */
__attribute__((section(".text.w4i_dispatch_08233c54_4")))
u8 Dispatch_08233C54_4(u8 *s)
{
    u32 *tbl = gTbl_08233C54;
    u32 idx = s[4];
    return (u8)((u32 (*)(u8 *))tbl[idx])(s);
}
