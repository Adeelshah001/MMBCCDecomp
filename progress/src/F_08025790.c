/* F_08025790 @ 0x08025790 (38 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave14_C_old.c (registry: src/wave14_C_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* F_08025790 @ 0x08025790 */
u8 TblLookup_25730(u8 *p, u8 v);

 u32 GetRomTableU16(u32 v);

__attribute__((section(".text.w14c_08025790")))
u16 F_08025790(u8 *p)
{
    u8 v = TblLookup_25730(p, 0);
    u32 w = v;
    if (v == 0)
        w = p[1];
    w = GetRomTableU16(w);
    return (u16)(*(u16 *)(p + 14) + w);
}
