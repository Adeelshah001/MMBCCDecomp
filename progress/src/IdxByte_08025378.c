/* IdxByte_08025378 @ 0x08025378 (20 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave14_C.c (registry: src/wave14_C.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* IdxByte_08025378 @ 0x08025378 */
u8 GetBit80(u8 *p);

__attribute__((section(".text.w14c_08025378")))
u8 IdxByte_08025378(u8 *p, u8 i) { return GetBit80(p + i); }
