/* sub_08024CD8 @ 0x08024CD8 (340 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w70a_08024cd8_MATCHED.c (registry: src/w70a_08024cd8_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

u8 TblLookup_25730(u8 *e, u8 a);

u8 CheckPair_258D8(u8 *e, u8 b);

u8 GetIndexedU8(u8 *e, u8 b);

u32 F_08025A10(u8 *e, u8 a);

u32 sub_08025CA0(u8 *e, u8 a, u8 b);

u32 sub_08025B60(u8 *e, u8 a, u8 v);

__attribute__((section(".text.w70a_08024cd8")))
u16 sub_08024CD8(u8 *s, u8 a, u8 b)
{
    if (TblLookup_25730((*(u8 **)(s + 20) + (*(u8 **)(s + 20))[432] * 144), a) == 0) {
        if (CheckPair_258D8((*(u8 **)(s + 20) + (*(u8 **)(s + 20))[432] * 144), b) == 0)
            return 0;
        if (CheckPair_258D8((*(u8 **)(s + 20) + (*(u8 **)(s + 20))[432] * 144), b) == 2)
            return sub_08025B60((*(u8 **)(s + 20) + (*(u8 **)(s + 20))[432] * 144), a, GetIndexedU8((*(u8 **)(s + 20) + (*(u8 **)(s + 20))[432] * 144), b));
        return sub_08025CA0((*(u8 **)(s + 20) + (*(u8 **)(s + 20))[432] * 144), a, b);
    } else {
        if (CheckPair_258D8((*(u8 **)(s + 20) + (*(u8 **)(s + 20))[432] * 144), b) == 0)
            return F_08025A10((*(u8 **)(s + 20) + (*(u8 **)(s + 20))[432] * 144), a);
        if (CheckPair_258D8((*(u8 **)(s + 20) + (*(u8 **)(s + 20))[432] * 144), b) == 2) {
            u8 v = GetIndexedU8((*(u8 **)(s + 20) + (*(u8 **)(s + 20))[432] * 144), b);
            if (v == a)
                return 0;
            return sub_08025B60((*(u8 **)(s + 20) + (*(u8 **)(s + 20))[432] * 144), a, v);
        }
        return sub_08025CA0((*(u8 **)(s + 20) + (*(u8 **)(s + 20))[432] * 144), a, b);
    }
}
