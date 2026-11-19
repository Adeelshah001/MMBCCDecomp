/* Sub_08038520 @ 0x08038520 (136 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36c_08038520_MATCHED.c (registry: mmbcc/src/w36c_08038520_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

extern int TblGetByte_24384(int a);

extern int Search_080112FC(int a, int b);

extern int TblWalkInit_080114B8(void);

extern int Sub_080114E8(void);

__attribute__((section(".text.w36c_08038520")))
int Sub_08038520(u8 *s)
{
    int r = 0;
    u8 *p = s + 18077;
    s8 v = p[0];
    switch (v) {
    case 0: {
        int t = TblGetByte_24384(4096) - 50;
        u16 u = Search_080112FC((u8)t, 8);
        __asm__ volatile("" : "+r"(u));
        if (u == 0) {
            *(s + 18076) = 7;
            p[0] = 0;
            break;
        }
        if ((s8)TblWalkInit_080114B8() != 0)
            break;
        p[0]++;
    }
    case 1:
        if ((s16)Sub_080114E8() == 1) {
            u8 *q = s + 18076;
            int z = 0;
            *q = 7;
            *(s + 18077) = z;
            r = 2;
        }
        break;
    default:
        break;
    }
    return r;
}
