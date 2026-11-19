/* sub_08005268 @ 0x08005268 (12 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w33d_08005268.c (registry: src/w33d_08005268.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void sub_08002300(void);

__attribute__((section(".text.w33d_08005268")))
void sub_08005268(void)
{
    sub_08002300();
}
