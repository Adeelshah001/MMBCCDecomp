/* Sub_080098C4 @ 0x080098C4 (108 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36b_080098c4_MATCHED.c (registry: mmbcc/src/w36b_080098c4_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void sub_080024BC(u32 *base, u32 idx, u32 *buf);

__attribute__((section(".text.w36b_080098c4")))
void Sub_080098C4(u8 a, u16 b, u8 c, u8 d)
{
    register u32 *base __asm__("r8") = (u32 *)0x0830b778;
    register u32 maskA __asm__("r5") = 0xffff0000;
    register u32 maskB __asm__("r6") = 0x0000ffff;
    volatile u32 buf[2];
    u32 t;
    buf[0] = (a & 0x1F) | ((a >> 5) << 17);
    t = buf[1];
    t &= maskA;
    t |= 1;
    t &= maskB;
    t |= 0x20000;
    buf[1] = t;
    sub_080024BC(base, ((b + c + (d << 5)) << 5) + 0x10000, (u32 *)buf);
}
