/* F_08010EA0 @ 0x08010EA0 (36 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w21d_08010ea0.c (registry: src/w21d_08010ea0.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u32 F_08010EC4(u8 a, s8 b, s8 c, s8 d, u8 e);

__attribute__((section(".text.w21d_08010EA0")))
u32 F_08010EA0(u8 a, s8 b, s8 c, s8 d)
{
    return F_08010EC4(a, b, c, d, 1);
}
