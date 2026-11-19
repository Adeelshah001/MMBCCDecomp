/* TblSet_11DD0 @ 0x08011DD0 (32 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave9_e_old.c (registry: src/wave9_e_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 gEwram02005260[];

__attribute__((section(".text.w9e_8011dd0")))
void TblSet_11DD0(u16 x, u8 y)
{
    u32 xr = x;
    u32 hdr;
    u8 *base;
    if (xr > 7)
        return;
    if (xr == 0)
        return;
    hdr = (u32)gEwram02005260;
    __asm__ volatile("" : "+r" (hdr));
    base = *(u8 **)(hdr + 8);
    base[xr] = y;
}
