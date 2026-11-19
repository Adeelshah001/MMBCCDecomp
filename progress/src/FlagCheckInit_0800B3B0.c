/* FlagCheckInit_0800B3B0 @ 0x0800B3B0 (58 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w17d_0800b3b0.c (registry: src/w17d_0800b3b0.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Ewram4E40_Init_0B4E4(void);

extern void Clr_0800B4C8(void);

__attribute__((section(".text.w17d_0800B3B0")))
u32 FlagCheckInit_0800B3B0(u8 *p)
{
    register u32 p3 __asm__("r3");
    register u8 *q __asm__("r2");
    u8 t;
    __asm__ volatile("add %0, %1, #0" : "=r" (p3) : "r" ((u32)p));
    __asm__ volatile("" : "=r" (q) : "0" ((u8 *)0x02004E40));
    t = q[4];
    if ((t & 15) != 0) return 0;
    {
        u32 r = 128;
        r &= t;
        if (r == 0) {
            q[5] = 1;
            return 0;
        }
    }
    *(u32 *)(q + 32) = p3;
    q[5] = 3;
    Ewram4E40_Init_0B4E4();
    Clr_0800B4C8();
    return 1;
}
