/* Fwd_08004ee0 @ 0x08004EE0 (18 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave14_C.c (registry: src/wave14_C.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* Fwd_08004ee0 @ 0x08004ee0 */
void sub_0800555C(void);

 void Fwd4_08005704(void);

 void sub_0800A094(void);

__attribute__((section(".text.w14c_08004ee0")))
void Fwd_08004ee0(void) { sub_0800555C(); Fwd4_08005704(); sub_0800A094(); }
