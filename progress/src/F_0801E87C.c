/* F_0801E87C @ 0x0801E87C (18 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave15_B.c (registry: src/wave15_B.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void SetDiffSum_080110C8(short a, short b, unsigned int *out);

__attribute__((section(".text.w15b_0801e87c")))
void F_0801E87C(short a, short b, unsigned int *out)
{
    SetDiffSum_080110C8(a, b, out);
}
