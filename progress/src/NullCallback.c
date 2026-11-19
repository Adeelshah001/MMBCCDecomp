/* NullCallback @ 0x08005208 (2 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_d.c (registry: src/wave3_d.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x08005208: no-op callback stub (1 bl caller: sub_080050F0). */
__attribute__((section(".text.w3d_noop")))
void NullCallback(void)
{
}
