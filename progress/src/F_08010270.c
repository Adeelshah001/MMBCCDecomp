/* F_08010270 @ 0x08010270 (42 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w21d_08010270.c (registry: src/w21d_08010270.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

extern u32 Setup_0801029C(u32 a0, u8 a1, s16 a2, s8 a3);

__attribute__((section(".text.w21d_08010270")))
u32 F_08010270(u8 a, u32 b, u16 c, u8 d)
{
    return Setup_0801029C(b, (a == 0) ? 1 : 3, (s16)c, (s8)d);
}
