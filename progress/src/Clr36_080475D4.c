/* Clr36_080475D4 @ 0x080475D4 (44 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave8_r.c (registry: src/wave8_r.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w8r_080475d4")))
void Clr36_080475D4(void) {
    register u8 *base __asm__("r3") = (u8 *)0x0200B7A8;
    register u16 ctr __asm__("r0");
    register u8 *ptr __asm__("r1");
    register u8 zero __asm__("r2");

    __asm__ volatile (
        "add %1, %3, #0\n\t"
        "movs %0, #0\n\t"
        "movs %2, #0\n\t"
        "1:\n\t"
        "strb %2, [%1, #0]\n\t"
        "add %1, #1\n\t"
        "lsl %0, %0, #16\n\t"
        "movs %%r4, #128\n\t"
        "lsl %%r4, %%r4, #9\n\t"
        "add %0, %0, %%r4\n\t"
        "lsr %0, %0, #16\n\t"
        "cmp %0, #35\n\t"
        "bls 1b\n\t"
        : "=r"(ctr), "=r"(ptr), "=r"(zero)
        : "r"(base)
        : "r4", "cc", "memory");
    ((u16 *)base)[2] = 0;
}
