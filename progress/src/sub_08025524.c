/* sub_08025524 @ 0x08025524 (62 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w18b_08025524.c (registry: src/w18b_08025524.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 GetMaskedByte_08025324(u8 *p, u8 idx);

extern void F_0802533c(u8 *p, u8 idx);

extern void Sub_254E0(u8 *s, u8 idx);

__attribute__((section(".text.w18b_08025524")))
u8 sub_08025524(u8 *p, u8 x)
{
    u8 v = GetMaskedByte_08025324(*(u8 **)p, x);
    if (v <= 98) {
        F_0802533c(*(u8 **)p, x);
        Sub_254E0(p, x);
        return GetMaskedByte_08025324(*(u8 **)p, x);
    }
    return 0;
}
