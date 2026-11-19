/* Sub_08034C1C @ 0x08034C1C (132 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w38b_08034c1c_MATCHED.c (registry: mmbcc/src/w38b_08034c1c_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern int sub_08034BD4(u8 a, u16 b);

__attribute__((section(".text.w38b_08034c1c")))
void Sub_08034C1C(u8 *s, u8 mode)
{
    u8 *base;
    register u8 *tblA __asm__("r7");
    u8 *tblB;
    u8 i;
    u8 *p;
    if (mode == 0)
        base = s + 336;
    else
        base = s + 364;
    i = 3;
    tblA = (u8 *)0x0200517e;
    tblB = tblA - 20;
    do {
        u32 *ep = (u32 *)(base + i * 4);
        u8 *ptr = (u8 *)*ep;
        u8 v = (u8)(((u32)sub_08034BD4(ptr[0], *(u16 *)(ptr + 2)) << 24) >> 24);
        u8 *dst;
        if (mode != 0) {
            if (i - 3 == 255)
                goto next;
            dst = (i - 3) + tblA;
            __asm__ volatile("");
        } else {
            if (i - 3 == 255)
                goto next;
            dst = (i - 3) + tblB;
        }
        *dst = v;
next: ;
        i++;
    } while (i <= 5);
    if (mode != 0) {
        __asm__ volatile("" : "+r"(p));
        p = (u8 *)0x0200517c;
    } else
        p = (u8 *)0x02005168;
    p[5] = 4;
    p[6] = 4;
}
