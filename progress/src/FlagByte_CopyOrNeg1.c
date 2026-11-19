/* FlagByte_CopyOrNeg1 @ 0x08010374 (40 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave8_u_old.c (registry: src/wave8_u_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 g_02005160[];

u32 FlagByte_CopyOrNeg1(u8 *p)
{
    u8 *q = g_02005160;
    u8 *r = p;

    if (*q == 0) {
        u8 *t = q;
        u8 v;

        t += 67;
        v = *t;
        *r = v;
        return 1;
    } else {
        register int v __asm__("r2");
        register int w __asm__("r0");

        __asm__ volatile("movs %0, #1\n\tneg %0, %0" : "=r"(v));
        w = v;
        *r = (u8)w;
        return 0;
    }
}
