/* Dispatch_08232E48_4 @ 0x08045EA0 (28 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i_old.c (registry: src/wave4_i_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u32 gTbl_08232E48[];

/* 0x08045EA0 */
__attribute__((section(".text.w4i_dispatch_08232e48_4")))
u8 Dispatch_08232E48_4(u8 *s)
{
    u32 *tbl = gTbl_08232E48;
    u32 idx = s[4];
    return (u8)((u32 (*)(u8 *))tbl[idx])(s);
}
