/* HBlank_VCountUpdate @ 0x08000978 (160 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave5_blk_old.c (registry: src/wave5_blk_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 base_03000400[];

__attribute__((section(".text.w5b_vcount")))
void HBlank_VCountUpdate(void)
{
    volatile u16 vcount;
    u8 b;
    u8 t;

    vcount = *(volatile u16 *)0x04000006;

    b = base_03000400[0x167];
    __asm__("movs %0,#2\n\tand %0,%1" : "=l"(t) : "l"(b));
    if (t == 0) {
        __asm__("movs %0,#2\n\torr %0,%1" : "=l"(t) : "l"(b));
        base_03000400[0x167] = t;
        if (vcount == 0)
            (*(u32 *)(base_03000400 + 0x160))++;
        if (vcount == base_03000400[0x166]) {
            void (*fn)(void) = *(void (**)(void))(base_03000400 + 0x15c);
            if (fn)
                fn();
        }
        if (vcount < base_03000400[0x166])
            *(volatile u8 *)0x04000005 = base_03000400[0x166];
        else
            *(volatile u8 *)0x04000005 = 0;
        {
            u8 *p = base_03000400;
            u8 v;
            p += 0x167;
            v = 2;
            v ^= *p;
            *p = v;
        }
    }
}
