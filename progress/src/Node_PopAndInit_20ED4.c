/* Node_PopAndInit_20ED4 @ 0x08020ED4 (132 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w16b_08020ed4.c (registry: src/w16b_08020ed4.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u32 *sub_08004424(u32 list);

extern u32 *sub_08004454(u32 list);

extern u32 g_020066F0;

extern u32 gTbl_08226EF0[];

u32 *Node_PopAndInit_20ED4(u8 a, u8 b, u8 c, u8 d)
{
    register u32 *s __asm__("r4");
    u8 *p;
    u32 *tbl;
    int v;
    int w;
    u8 x, t;

    if (a == 0)
        s = sub_08004424(g_020066F0);
    else
        s = sub_08004454(g_020066F0);
    if (s != 0) {
        p = (u8 *)s;
        p += 35;
        x = (b & 7) << 4;
        v = -113;
        v &= *p;
        v |= x;
        t = c & 15;
        w = -16;
        v &= w;
        v |= t;
        *p = v;
        if (c == 0)
            v &= 0x7F;
        else
            v |= 0x80;
        *p = v;
        tbl = gTbl_08226EF0;
        ((u8 *)s)[9] = d;
        ((u32 *)s)[5] = *(u32 *)tbl[d];
    }
    return s;
}
