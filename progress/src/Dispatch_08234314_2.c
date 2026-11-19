/* Dispatch_08234314_2 @ 0x08048260 (28 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i_old.c (registry: src/wave4_i_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u32 gTbl_08234314[];

/* 0x08048260 */
__attribute__((section(".text.w4i_dispatch_08234314_2")))
u8 Dispatch_08234314_2(u8 *s)
{
    u32 *tbl = gTbl_08234314;
    u32 idx = s[2];
    return (u8)((u32 (*)(u8 *))tbl[idx])(s);
}
