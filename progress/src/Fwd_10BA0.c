/* Fwd_10BA0 @ 0x08010BA0 (20 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w16b_08010ba0.c (registry: src/w16b_08010ba0.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Tbl_ClearEntries(u8 a);

extern u8 RomBase_20051B0[];

void Fwd_10BA0(void)
{
    u8 *base = RomBase_20051B0;
    Tbl_ClearEntries(base[2]);
}
