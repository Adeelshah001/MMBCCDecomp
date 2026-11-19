/* CondRectFill_080070F0 @ 0x080070F0 (68 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w31d_080070f0.c (registry: src/w31d_080070f0.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

extern void RectFill_7134(void *ctx, u16 a, s16 b, s16 c, u8 d);

__attribute__((section(".text.w31d_080070f0")))
void CondRectFill_080070F0(u16 x, u16 y, u16 z, u8 w)
{
    u8 *base = (u8 *)0x02004830;
    if (base[0x265])
        return;
    RectFill_7134(base, x, (s16)y, (s16)z, w);
}
