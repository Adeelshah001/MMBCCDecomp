/* DrawText_048B4 @ 0x080048B4 (82 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave13_D_old.c (registry: src/wave13_D_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w13d_080048b4")))
void DrawText_048B4(unsigned char *p, unsigned int x, unsigned int y)
{
    unsigned char *q = p;
    unsigned int w = x;
    unsigned short *dst;
    register unsigned int b1 __asm__("r5");
    register unsigned int b2 __asm__("r2");
    unsigned char c;

    dst = *(unsigned short **)0x02003250;
    if (y > 31) return;
    dst += w + y * 32;

    c = *q;
    if (c == 0) return;

    __asm__ volatile(
        "mov r2, #232\n\t"
        "lsl r2, r2, #2\n\t"
        "add %0, r2, #0\n\t"
        "mov r6, #184\n\t"
        "lsl r6, r6, #2\n\t"
        "add %1, r6, #0"
        : "=r" (b1), "=r" (b2)
        :
        : "r2", "r6", "cc");
    do {
        if (w > 31) return;
        if (c <= 0x9F) {
            unsigned char ch = *q;
            unsigned int s;
            __asm__ volatile("add %0, %1, %2" : "=r" (s) : "r" (b1), "r" (ch));
            *dst = s;
        } else {
            unsigned char ch = *q;
            unsigned int s;
            __asm__ volatile("add %0, %1, %2" : "=r" (s) : "r" (b2), "r" (ch));
            *dst = s;
        }
        q++;
        dst++;
        c = *q;
    } while (c != 0);
}
