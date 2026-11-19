/* F_08024648 @ 0x08024648 (18 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave15_B.c (registry: src/wave15_B.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern unsigned int Gt199_08026700(u8 v);

__attribute__((section(".text.w15b_08024648")))
u16 F_08024648(u8 x)
{
    return Gt199_08026700(x);
}
