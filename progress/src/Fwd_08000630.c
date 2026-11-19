/* Fwd_08000630 @ 0x08000630 (10 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w15c_08000630.c (registry: src/w15c_08000630.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

void Fwd_08002f4c(void);

void Fwd_08000630(void) { Fwd_08002f4c(); }
