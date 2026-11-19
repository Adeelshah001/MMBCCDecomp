/* F_08024f88 @ 0x08024F88 (52 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave14_C_old.c (registry: src/wave14_C_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* F_08024f88 @ 0x08024f88 */
u32 GetU32_38(u8 *p);

 void Sub_08025E5C(u8 *p, u32 v, u32 w);

__attribute__((section(".text.w14c_08024f88")))
void F_08024f88(u32 a)
{
    u32 base;
    u8 *p;
    u8 v;
    u32 t;
    u32 w;
    __asm__ volatile("" : "=r" (base) : "0" (0x020070A4));
    p = *(u8 **)base;
    v = p[0x1B0];
    t = v * 144;
    p += t;
    w = GetU32_38((u8 *)(base - 0x14));
    Sub_08025E5C(p, w, a);
}
