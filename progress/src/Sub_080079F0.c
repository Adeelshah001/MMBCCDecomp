/* Sub_080079F0 @ 0x080079F0 (60 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w35c_080079f0_MATCHED.c (registry: mmbcc/src/w35c_080079f0_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void sub_08007A2C(u8 *base, s8 a, s8 b, s8 c);

__attribute__((section(".text.w35c_080079f0")))
void Sub_080079F0(u8 a, u16 b, u16 c)
{
    register u8 *base __asm__("r6") = (u8 *)0x02004830;
    if (*(base + 0x265) == 0)
        sub_08007A2C(base, (s8)a, (s8)b, (s8)c);
}
