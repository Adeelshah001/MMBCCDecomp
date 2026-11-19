/* Call3_08025464 @ 0x08025464 (20 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave14_C.c (registry: src/wave14_C.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* Call3_08025464 @ 0x08025464 */
void sub_08025230(u8 *p, u32 v, u32 w);

__attribute__((section(".text.w14c_08025464")))
void Call3_08025464(u8 *p) { sub_08025230(p + 12, *(u32 *)(p + 8), 0xF9); }
