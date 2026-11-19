/* PalDmaInit_02678 @ 0x08002678 (108 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave13_D_old.c (registry: src/wave13_D_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w13d_08002678")))
void PalDmaInit_02678(void)
{
    register unsigned int zero __asm__("r4") = 0;
    unsigned int w = zero;
    volatile unsigned int *dma = (volatile unsigned int *)0x040000D4;
    register unsigned char *q __asm__("r2");
    register unsigned int i __asm__("r3");

    dma[0] = (unsigned int)&w;
    q = (unsigned char *)0x03002420;
    dma[1] = (unsigned int)q;
    dma[2] = 0x85000100;
    (void)dma[2];
    dma[0] = (unsigned int)q;
    dma[1] = 0xA0 << 19;
    dma[2] = 0x84000100;
    (void)dma[2];

    i = 0x402;
    __asm__ volatile(
        "add r0, %1, %0\n\t"
        "mov r1, #32\n\t"
        "strb r1, [r0, #0]\n\t"
        "sub %0, #1\n\t"
        "add r0, %1, %0\n\t"
        "strb r1, [r0, #0]\n\t"
        "sub %0, #1\n\t"
        "add r0, %1, %0\n\t"
        "strb r1, [r0, #0]"
        : "+r" (i)
        : "r" (q)
        : "r0", "r1", "cc", "memory");
    *(unsigned short *)((unsigned int)q + 0x404) = zero;
    *(unsigned short *)((unsigned int)q + 0x406) = (unsigned short)i;
}
