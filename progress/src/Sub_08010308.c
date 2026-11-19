/* Sub_08010308 @ 0x08010308 (90 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w21b_08010308.c (registry: src/w21b_08010308.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Ewram5160_Init_10508(u32 v);

__attribute__((section(".text.w21b_08010308")))
u32 Sub_08010308(u32 a, u32 b, u16 c, u8 d)
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
    Ewram5160_Init_10508(5);
    q1 = p + 66;
    *q1 = z;
    *(u32 *)(p + 48) = a;
    *(u32 *)(p + 52) = b;
    q2 = p + 67;
    *q2 = 0xff;
    q3 = p + 65;
    *q3 = d;
    *(u16 *)(p + 56) = c;
    return 1;
}
