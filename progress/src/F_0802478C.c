/* F_0802478C @ 0x0802478C (28 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave15_B.c (registry: src/wave15_B.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 GetBoundedByte_08025478(void *s, u16 idx);

__attribute__((section(".text.w15b_0802478c")))
u8 F_0802478C(u16 idx)
{
    return GetBoundedByte_08025478((void *)0x02007090, idx);
}
