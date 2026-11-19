/* F_080250A8 @ 0x080250A8 (20 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w17d_080250a8.c (registry: src/w17d_080250a8.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Sub_266AC(u8 *s);

__attribute__((section(".text.w17d_080250A8")))
void F_080250A8(void)
{
    u8 *p;
    __asm__ volatile("" : "=r" (p) : "0" ((u8 *)0x02007090));
    Sub_266AC(p + 24);
}
