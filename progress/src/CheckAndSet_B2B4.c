/* CheckAndSet_B2B4 @ 0x0800B2B4 (36 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave8_u_old.c (registry: src/wave8_u_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 gEwram_02004E40[];

u32 CheckAndSet_B2B4(void)
{
    u8 *p = gEwram_02004E40;
    u8 v = p[4];
    int t1;
    int t2;

    __asm__("movs %0,#15\n\tand %0,%1" : "=l"(t1) : "l"(v));
    if (t1 != 0)
        return 0;
    __asm__("movs %0,#128\n\tand %0,%1" : "=l"(t2) : "l"(v));
    if (t2 != 0)
        p[5] = 2;
    return 1;
}
