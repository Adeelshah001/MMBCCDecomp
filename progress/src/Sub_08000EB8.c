/* Sub_08000EB8 @ 0x08000EB8 (28 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w37b_08000eb8_MATCHED.c (registry: mmbcc/src/w37b_08000eb8_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w37b_08000eb8")))
void Sub_08000EB8(int idx)
{
    u8 *q = (u8 *)0x030023c8 + idx * 24;
    if (*q != 1)
        *q |= 8;
}
