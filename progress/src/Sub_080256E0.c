/* Sub_080256E0 @ 0x080256E0 (60 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36d_080256e0_MATCHED.c (registry: src/w36d_080256e0_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef short s16;

extern void sub_080255F4(u8 *s);

__attribute__((section(".text.w36d_080256e0")))
void Sub_080256E0(u8 *s)
{
    s16 i;
    register u8 mask __asm__("r3");
    register u8 zero __asm__("r5");
    sub_080255F4(s);
    i = 0;
    zero = 0;
    __asm__ volatile("movs %0, #255" : "=r"(mask));
    for (; i <= 29; i++) {
        register u32 poff __asm__("r1");
        register u8 b __asm__("r2");
        poff = i * 4;
        poff += (u32)s;
        ((u8 *)poff)[20] = zero;
        b = ((u8 *)poff)[21];
        b |= mask;
        ((u8 *)poff)[21] = b;
    }
    s[141] = 0;
    s[140] = 0;
}
