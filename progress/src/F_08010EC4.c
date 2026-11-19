/* F_08010EC4 @ 0x08010EC4 (110 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w20d_08010ec4.c (registry: src/w20d_08010ec4.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 sub_08010FB4(u8 a);

__attribute__((section(".text.w20d_08010EC4")))
u8 F_08010EC4(u8 a, u8 b, u8 c, u8 d, u8 e)
{
    register u8 *base __asm__("r2") = (u8 *)0x020051b0;
    int v = base[3];
    u8 *p;
    int a12;
    v >>= a;
    if ((v & 1) == 0) {
        return 0;
    }
    a12 = a * 12;
    {
        register u8 *q __asm__("r1") = base + 24;
        /* divided-syntax forces adds r4,r0,r1 order (compiler swaps otherwise) */
        __asm__ ("add %0, %1, %2" : "=r" (p) : "r" (a12), "r" (q));
    }
    if ((s8)sub_08010FB4(a) != 1) {
        return 0;
    }
    p[0] = 1;
    p[6] = e;
    p[3] = b;
    p[4] = c;
    p[2] = d;
    return 1;
}
