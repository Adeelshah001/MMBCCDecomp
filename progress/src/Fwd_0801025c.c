/* Fwd_0801025c @ 0x0801025C (18 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave14_C.c (registry: src/wave14_C.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* Fwd_0801025c @ 0x0801025c */
u32 Setup_0801029C(u32 a, u32 b, u32 c, s8 d);

__attribute__((section(".text.w14c_0801025c")))
u32 Fwd_0801025c(u32 a, s8 b) { return Setup_0801029C(a, 0, 0, b); }
