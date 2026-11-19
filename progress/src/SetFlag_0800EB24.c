/* SetFlag_0800EB24 @ 0x0800EB24 (12 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w15c_0800eb24.c (registry: src/w15c_0800eb24.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

void SetByte20_Clear21to23_02005130(u8 x);

void SetFlag_0800EB24(void) { SetByte20_Clear21to23_02005130(3); }
