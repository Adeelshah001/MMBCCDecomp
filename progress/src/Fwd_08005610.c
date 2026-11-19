/* Fwd_08005610 @ 0x08005610 (10 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave14_C.c (registry: src/wave14_C.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* Fwd_08005610 @ 0x08005610 */
void Sub_0800CC94(void);

__attribute__((section(".text.w14c_08005610")))
void Fwd_08005610(void)
{
    Sub_0800CC94();
}
