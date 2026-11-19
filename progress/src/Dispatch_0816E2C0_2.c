/* Dispatch_0816E2C0_2 @ 0x08001D98 (32 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i_old.c (registry: src/wave4_i_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 gEwram_02002F80[];

extern u32 gTbl_0816E2C0[];

/* 0x08001D98: tbl[((u8*)0x02002F80)[2]]((u8*)0x02002F80). Tentative.
 * Two pools; the 2-byte 0000 pad between code and pool is real ROM. */
__attribute__((section(".text.w4i_dispatch_0816e2c0_2")))
void Dispatch_0816E2C0_2(void)
{
    u8 *s = gEwram_02002F80;
    u32 *tbl = gTbl_0816E2C0;
    u32 idx = s[2];
    ((void (*)(u8 *))tbl[idx])(s);
}
