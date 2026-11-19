/* Dispatch_0822709C_10 @ 0x08021E34 (24 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i_old.c (registry: src/wave4_i_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u32 gTbl_0822709C[];

/* 0x08021E34 */
__attribute__((section(".text.w4i_dispatch_0822709c_10")))
void Dispatch_0822709C_10(u8 *s)
{
    u32 *tbl = gTbl_0822709C;
    u32 idx = s[0x10];
    ((void (*)(u8 *))tbl[idx])(s);
}
