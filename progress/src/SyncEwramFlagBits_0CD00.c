/* SyncEwramFlagBits_0CD00 @ 0x0800CD00 (56 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave12_C_old.c (registry: src/wave12_C_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x0800CD00: if bit 2 of gEwram_02000EC0[9] clear, clear bits 11-13 of
 * gEwram_020031E0[0] (&= 0xC7FF); else set them (|= 0x3800). */
__attribute__((section(".text.w12c_0800cd00")))
void SyncEwramFlagBits_0CD00(void)
{
    unsigned int base;
    __asm__ volatile("" : "=r" (base) : "0" (0x02000EC0));
    if ((((unsigned char *)base)[9] & 4) == 0) {
        unsigned short *q = (unsigned short *)0x020031E0;
        unsigned short t = 0xC7FF;
        unsigned short u = t & *q;
        *q = u;
    } else {
        register unsigned short *q __asm__("r0") = (unsigned short *)0x020031E0;
        unsigned short t = 0x3800;
        register unsigned short u __asm__("r1") = t;
        u |= *q;
        *q = u;
    }
}
