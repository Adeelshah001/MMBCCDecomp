/* Guard_0800c4f8 @ 0x0800C4F8 (20 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave14_C.c (registry: src/wave14_C.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* Guard_0800c4f8 @ 0x0800c4f8 */
void Sub_08005274(u32 a, u32 b, u32 c);

__attribute__((section(".text.w14c_0800c4f8")))
void Guard_0800c4f8(u32 x, u32 a) { if (a != 0) Sub_08005274(a, 0, 2); }
