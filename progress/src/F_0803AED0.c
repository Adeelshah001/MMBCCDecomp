/* F_0803AED0 @ 0x0803AED0 (106 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w18c_0803aed0.c (registry: src/w18c_0803aed0.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Call4E60_4E44(void);

extern void PalModeSet_4DFC(u8 x);

extern u8 _call_via_r1(u8 *p, u32 x);

__attribute__((section(".text.w18c_0803aed0")))
void F_0803AED0(u8 *p)
{
    u8 st = p[2];
    if (st == 0) goto L0;
    if (st == 1) goto L1;
    goto Lend;
L0:
    Call4E60_4E44();
    {
        u8 *q = (u8 *)0x02004F80;
        PalModeSet_4DFC(q[2]);
    }
    p[2]++;
L1:
    {
        register u32 *tbl __asm__("r1");
        u8 idx;
        register u32 r __asm__("r1");
        u32 off;
        __asm__ volatile("" : "=r" (tbl) : "0" ((u32 *)0x08232344));
        off = 0x469c;
        idx = *(p + off);
        {
            u8 tmp = _call_via_r1(p, tbl[idx]);
            __asm__ volatile("" : "+r" (tmp));
            r = tmp;
        }
        if (r == 1) {
            u8 z = 0;
            p[1] = 3;
            p[2] = z;
            p[3] = z;
        } else if (r == 2) {
            u8 z = 0;
            p[1] = (u8)r;
            p[2] = z;
            p[3] = z;
        }
    }
Lend:;
}
