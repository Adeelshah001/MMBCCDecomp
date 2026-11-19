/* Dispatch_08232D2C_4 @ 0x08042AC8 (28 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i_old.c (registry: src/wave4_i_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u32 gTbl_08232D2C[];

/* 0x08042AC8 */
__attribute__((section(".text.w4i_dispatch_08232d2c_4")))
u8 Dispatch_08232D2C_4(u8 *s)
{
    u32 *tbl = gTbl_08232D2C;
    u32 idx = s[4];
    return (u8)((u32 (*)(u8 *))tbl[idx])(s);
}
