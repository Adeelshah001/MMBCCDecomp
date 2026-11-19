/* F_0802508C @ 0x0802508C (28 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w17d_0802508c.c (registry: src/w17d_0802508c.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Sub_2666C(u8 *s, u16 idx);

__attribute__((section(".text.w17d_0802508C")))
void F_0802508C(u16 idx)
{
    u16 i = idx;
    u8 *p;
    __asm__ volatile("" : "=r" (p) : "0" ((u8 *)0x02007090));
    if (i != 0) {
        Sub_2666C(p + 24, i);
    }
}
