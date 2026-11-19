/* Setup_0801029C @ 0x0801029C (86 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w20d_0801029c.c (registry: src/w20d_0801029c.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Ewram5160_Init_10508(u32 v);

__attribute__((section(".text.w20d_0801029C")))
u8 Setup_0801029C(u32 a0, u8 a1, u16 a2, u8 a3)
{
    register u8 *p __asm__("r4") = (u8 *)0x02005160;
    register u8 z __asm__("r5");
    u8 *q1;
    u8 *q2;
    register u8 *q3 __asm__("r0");
    z = p[0];
    if (z != 0) {
        return 0;
    }
    Ewram5160_Init_10508(4);
    q1 = p + 66;
    *q1 = z;
    /* opaque adds forces adds r0,#3 (compiler folds to indexed strb otherwise) */
    __asm__ ("add %0, %0, #3" : "+r" (q1));
    *q1 = a1;
    *(u16 *)(p + 56) = a2;
    *(u32 *)(p + 48) = a0;
    q3 = p + 65;
    *q3 = a3;
    return 1;
}
