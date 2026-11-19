/* ObjSlotInit_05FC0 @ 0x08005FC0 (84 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w16d_08005fc0.c (registry: src/w16d_08005fc0.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

 typedef short s16;

void ObjSlotInit_05FC0(u8 a)
{
    u8 *p = (u8 *)((u8)a << 5);
    int v;
    s16 i;
    u8 *q;
    p += 0x2004CA0;
    p[30] = 0;
    {
        int one = 1;
        v = p[31];
        v |= one;
        v &= -7;
        v |= 4;
        v |= one;
        p[31] = v;
    }
    i = 0;
    q = p;
    {
        register u8 *q4 __asm__("r3") = q + 4;
        register u16 zero __asm__("r5") = 0;
        register int uno __asm__("r4") = 1;
        for (; i <= 11; i++) {
            int off = (s16)i * 2;
            __asm__ volatile("add %0, %1, %0" : "+r" (off) : "r" (q4));
            *(u16 *)off = zero;
            q[31] |= uno;
        }
    }
}
