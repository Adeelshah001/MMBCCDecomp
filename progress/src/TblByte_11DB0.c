/* TblByte_11DB0 @ 0x08011DB0 (32 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave12_B_old.c (registry: src/wave12_B_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 gEwram02005260[];

/* TblByte_11DB0 @ 0x08011DB0 (32 B): table byte from *(u8**)(gEwram02005260+8);
 * returns base[c], 0 if idx > 7 or idx == 0. */
__attribute__((section(".text.w12b_08011db0")))
u8 TblByte_11DB0(u16 idx)
{
    u16 a = idx;
    register u16 c __asm__("r1") = a;
    u8 *p;
    u8 *base;
    if (a > 7) goto ret0;
    if (a != 0) goto main;
ret0:
    return 0;
main:
    p = gEwram02005260;
    p += 8;
    base = *(u8 **)p;
    return base[c];
}
