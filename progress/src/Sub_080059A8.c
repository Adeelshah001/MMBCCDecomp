/* Sub_080059A8 @ 0x080059A8 (244 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w54c_080059a8_MATCHED.c (registry: src/w54c_080059a8_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef short s16;

extern void sub_08002300(int a, int b);

extern void sub_080086AC(int a);

__attribute__((section(".text.w54c_080059a8")))
void Sub_080059A8(void)
{
    u8 *tbl = (u8 *)0x02004830;
    s16 i;
    if ((tbl[154 * 4] & 16) != 0) {
        register u16 hw __asm__("r2") = *(u16 *)0x02003670;
        register int sel __asm__("r2");
        if ((hw & 224) == 0)
            sel = (hw & 28) >> 2;
        else
            sel = 0;
        {
            register u8 *callptr __asm__("r1") = (u8 *)0x08172094;
            __asm__ volatile("" : "+r" (callptr));
            __asm__ volatile("add %0, %1, %0" : "+r" (callptr) : "r" (sel) : "cc");
            sub_08002300(*callptr * 20 + 0x0830B340, 0x5940);
        }
    }
    if (tbl[153 * 4] != 0) {
        u8 *hwbase = (u8 *)0x02003670;
        int r2 = ((u32)tbl[154 * 4] << 28) >> 29;
        u8 B;
        u8 d;
        int e;
        __asm__ volatile("" : "+r" (hwbase));
        B = (u8)(((hwbase[0x11AE] & 4) != 0 ? 20 : 18) - r2);
        d = (u8)(B - tbl[153 * 4]);
        e = B - d;
        {
            u32 e2 = (u32)e << 22;
            u32 v1 = (d << 6) + 0x06002000;
            volatile u32 *dma = (volatile u32 *)0x040000D4;
            dma[0] = (u32)(tbl + 156 * 4);
            dma[1] = v1;
            dma[2] = (e2 >> 17) | 0x80000000;
            (void)dma[2];
        }
    }
    for (i = 0; i <= 2; i++)
        sub_080086AC(i * 12 + 0x02004830);
}
