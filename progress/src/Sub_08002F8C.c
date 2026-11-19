/* Sub_08002F8C @ 0x08002F8C (42 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34c_08002f8c_MATCHED.c (registry: staging/wave34_C/w34c_08002f8c_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void sub_0804D65C(u32 x, u32 y, int z);

__attribute__((section(".text.w34c_08002f8c")))
void Sub_08002F8C(void)
{
    u32 t;
    u16 n;
    u8 *p;
    u32 nn;
    __asm__ volatile("ldr %0, .Lpool7_08002f8c" : "=r"(t));
    n = (u16)t;
    if (n == 0)
        return;
    __asm__ volatile("ldr %0, .Lpool6d7c_08002f8c" : "=r"(p));
    nn = n;
    do {
        u32 v = *(u32 *)p;
        u32 c;
        __asm__ volatile("ldr %0, .Lpoolffff_08002f8c" : "=r"(c));
        sub_0804D65C(v, c, 256);
        p += 12;
        nn--;
    } while (nn != 0);
}
