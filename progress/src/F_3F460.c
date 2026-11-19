/* F_3F460 @ 0x0803F460 (32 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave11_A_old.c (registry: src/wave11_A_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w11a_0803f460")))
void F_3F460(u8 *base, u8 i, u8 j)
{
    u8 *t;
    u32 off;
    u8 a, b;
    __asm__ volatile("" : "=r" (off) : "0" (0x464C));
    t = base + off;
    a = t[i];
    b = t[j];
    t[i] = b;
    t[j] = a;
}
