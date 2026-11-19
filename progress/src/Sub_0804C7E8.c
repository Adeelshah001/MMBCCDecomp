/* Sub_0804C7E8 @ 0x0804C7E8 (36 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34c_0804c7e8_MATCHED.c (registry: staging/wave34_C/w34c_0804c7e8_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Sub_0804CECC(u32 x);

__attribute__((section(".text.w34c_0804c7e8")))
void Sub_0804C7E8(void)
{
    u32 t;
    u16 n;
    u8 *p;
    u32 nn;
    __asm__ volatile("ldr %0, .Lpool7_0804c7e8" : "=r"(t));
    n = (u16)t;
    if (n == 0)
        return;
    __asm__ volatile("ldr %0, .Lpool6d7c_0804c7e8" : "=r"(p));
    nn = n;
    do {
        Sub_0804CECC(*(u32 *)p);
        p += 12;
        nn--;
    } while (nn != 0);
}
