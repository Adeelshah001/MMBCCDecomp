/* F_0804A450 @ 0x0804A450 (68 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w20c_0804a450.c (registry: src/w20c_0804a450.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

__attribute__((section(".text.w20c_0804a450")))
void F_0804A450(void)
{
    register u16 *tbl __asm__("r1") = (u16 *)0x0200BD20;
    u8 *flag = (u8 *)0x02002EE0;
    __asm__ volatile("" : "+r" (tbl), "+r" (flag));
    {
        register u32 one __asm__("r0") = 1;
        __asm__ volatile("" : "+r" (one));
        one &= *flag;
        if (one == 0)
            return;
    }
    {
        u16 *q = (u16 *)((u8 *)tbl + 124);
        u16 v = *q;
        int i = 0;
        if (((s16 *)q)[i] == 0)
            return;
        *q = v - 1;
        if ((s16)(v - 1) != 8)
            return;
        {
            volatile u16 *pv = (volatile u16 *)(flag + 2);
            u16 v = *pv;
            u16 m = 0xFFFD;
            u16 dummy;
            m &= v;
            dummy = *pv;
            *pv = m;
        }
    }
}
