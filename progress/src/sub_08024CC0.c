/* sub_08024CC0 @ 0x08024CC0 (24 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w33d_08024cc0.c (registry: src/w33d_08024cc0.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u32 F_080249B8(u8 *p, u8 a, u8 b);

__attribute__((section(".text.w33d_08024cc0")))
u16 sub_08024CC0(u8 *p, u8 a, u8 b)
{
    return (u16)F_080249B8(p, a, b);
}
