/* DecByte_080254b4 @ 0x080254B4 (44 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave14_C_old.c (registry: src/wave14_C_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* DecByte_080254b4 @ 0x080254b4 */
void Buf_RemoveAt_25290(u8 *p, u8 i);

__attribute__((section(".text.w14c_080254b4")))
void DecByte_080254b4(u8 *p, u8 i)
{
    u8 *q = *(u8 **)(p + 8) + i;
    u8 *r = (u8 *)(*q + *(u32 *)(p + 4));
    (*r)--;
    if (*r == 0)
        Buf_RemoveAt_25290(p + 12, i);
}
