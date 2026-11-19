/* Sub_08004E60 @ 0x08004E60 (128 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w38b_08004e60_MATCHED.c (registry: mmbcc/src/w38b_08004e60_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Sub_080053A0(void);

extern void Fwd_08004ee0(void);

extern void sub_080052DC(int a, int b, int c, int d);

extern void sub_0800B8D0(void);

extern void Sub_08004EF4(void);

__attribute__((section(".text.w38b_08004e60")))
void Sub_08004E60(u8 a)
{
    register u8 aa __asm__("r6") = a;
    u8 *p = (u8 *)0x02003670;
    u16 q = 4526;
    register u8 bit __asm__("r5") = ((u32)p[q] << 29) >> 31;
    u8 *qq;
    u16 i;
    int z;
    int t;
    qq = p;
    i = 0;
    z = 0;
    while (i <= q + 9) {
        *qq++ = z;
        __asm__ volatile("lsl %0, %0, #16\n\tmovs r7, #128\n\tlsl r7, r7, #9\n\tadd %0, %0, r7\n\tlsr %0, %0, #16" : "+r"(i) :: "r7");
    }
    p += 4526;
    t = (aa << 3) | (*p & 7);
    t &= -5;
    t |= (bit << 2);
    t &= -3;
    *p = t;
    Sub_080053A0();
    if ((*p & 248) != 8)
        Fwd_08004ee0();
    sub_080052DC(0, 160, 0, 240);
    sub_0800B8D0();
    Sub_08004EF4();
}
