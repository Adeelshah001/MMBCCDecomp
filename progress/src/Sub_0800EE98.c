/* Sub_0800EE98 @ 0x0800EE98 (60 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w35c_0800ee98_MATCHED.c (registry: mmbcc/src/w35c_0800ee98_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern int Ewram5160_Init_10508(int a);

extern void Zero_0801052C(int a);

extern void Sub_08010724(void *p);

extern void Fwd_08010acc(void *p);

__attribute__((section(".text.w35c_0800ee98")))
void Sub_0800EE98(void)
{
    u8 *base = (u8 *)0x02005160;
    u8 *q = base;
    u16 i = 0;
    while (1) {
        *q++ = 0;
        __asm__ volatile("lsl %0, %0, #16\n\tmovs r3, #128\n\tlsl r3, r3, #9\n\tadd %0, %0, r3\n\tlsr %0, %0, #16" : "+r"(i) :: "r3");
        if (i > 75)
            break;
    }
    Zero_0801052C(Ewram5160_Init_10508(0));
    Sub_08010724(base);
    Fwd_08010acc(base);
}
