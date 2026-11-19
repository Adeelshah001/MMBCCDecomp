/* sub_08004E50 @ 0x08004E50 (16 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w33d_08004e50.c (registry: src/w33d_08004e50.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Sub_08004E60(u8 a);

__attribute__((section(".text.w33d_08004e50")))
void sub_08004E50(u8 a)
{
    Sub_08004E60(a);
}
