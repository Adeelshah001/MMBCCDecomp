/* Sub_080402E0 @ 0x080402E0 (132 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w37b_080402e0_MATCHED.c (registry: mmbcc/src/w37b_080402e0_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void sub_08040834(u8 *o);

extern void sub_08040CC4(u8 *o);

extern void Sub_08042998(u8 *o);

extern void F5_080429bc(u8 *o);

__attribute__((section(".text.w37b_080402e0")))
void Sub_080402E0(u8 *o)
{
    u8 x = o[0x46af];
    u8 *b0 = (u8 *)0x02003670;
    register s8 *base __asm__("r2");
    int sv;
    __asm__ volatile("" : "+r"(b0));
    base = (s8 *)(b0 + 0x11ac);
    __asm__ volatile("movs %0, #0\n\tldrsb %0, [%1, %0]" : "=r"(sv) : "r"(base));
    if (x == sv) {
        if (o[0x46ac] == 10) {
            sub_08040834(o);
            sub_08040CC4(o);
        }
        return;
    }
    {
        int d = x - sv;
        int delta;
        if (d < 0) {
            delta = 0xffff;
            if (base[0] == 14)
                Sub_08042998(o);
        } else {
            delta = 1;
            if (base[0] == 14)
                F5_080429bc(o);
        }
        {
            u8 *f0 = (u8 *)0x02003670;
            u8 *fb;
            __asm__ volatile("" : "+r"(f0));
            fb = f0 + 0x11ac;
            *fb += delta;
        }
    }
}
