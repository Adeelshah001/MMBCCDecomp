/* F_080251d8 @ 0x080251D8 (50 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave14_C_old.c (registry: src/wave14_C_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* F_08025790 @ 0x08025790 */
u8 TblLookup_25730(u8 *p, u8 v);

 u8 GetEnt_IdxByte1(u8 *p);

__attribute__((section(".text.w14c_080251d8")))
u8 F_080251d8(u8 *p)
{
    u8 v = p[0xD8 << 1];
    u8 w = TblLookup_25730(p + v * 144, 0);
    if (w == 0)
        w = GetEnt_IdxByte1(p);
    return w;
}
