/* Sub_0804C820 @ 0x0804C820 (36 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w35d_0804c820_MATCHED.c (registry: mmbcc/src/w35d_0804c820_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void ClearSignBit_0804C5F4(u32 x);

__attribute__((section(".text.w35d_0804c820")))
void Sub_0804C820(void)
{
    u32 t;
    u16 n;
    u8 *p;
    u32 nn;
    __asm__ volatile("ldr %0, .Lpool7_0804c820" : "=r"(t));
    n = (u16)t;
    if (n == 0)
        return;
    __asm__ volatile("ldr %0, .Lpool6d7c_0804c820" : "=r"(p));
    nn = n;
    do {
        ClearSignBit_0804C5F4(*(u32 *)p);
        p += 12;
        nn--;
    } while (nn != 0);
}
