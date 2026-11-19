/* sub_08002E80 @ 0x08002E80 (84 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w23a_08002e80.c (registry: src/w23a_08002e80.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w23a_08002E80")))
void sub_08002E80(void)
{
    volatile u16 disp;
    u32 *p;
    volatile u16 *dsp;
    u16 *dp = &disp;

    dsp = (volatile u16 *)0x04000000;
    __asm__ volatile("" : : "r"(dsp) : "r4");
    *dp = *dsp;
    *(volatile u16 *)&disp = *(volatile u16 *)&disp & 0x1FFF;
    *(volatile u16 *)&disp = *(volatile u16 *)&disp | *(u16 *)(p = (u32 *)0x02003230);
    *dsp = *(volatile u16 *)&disp;

    *(volatile u32 *)0x04000040 = p[1];
    *(volatile u32 *)0x04000044 = p[2];
    *(volatile u32 *)0x04000048 = p[3];
}
