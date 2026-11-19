/* Sub_1AB34 @ 0x0801AB34 (64 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w16b_0801ab34.c (registry: src/w16b_0801ab34.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 GetField17_U8(u8 *s);

extern void DecIfNonZero_18(u8 *s);

extern void MaxAssign_17(u8 *s, u8 v);

extern u32 Tbl_082243D8[];

void Sub_1AB34(u8 *s)
{
    u32 *tbase;
    u32 *p;
    if (GetField17_U8(*(u8 **)(s + 44)) > 5) {
        MaxAssign_17(*(u8 **)(s + 44), 7);
        DecIfNonZero_18(*(u8 **)(s + 44));
        *(u8 **)(s + 44) = 0;
        tbase = Tbl_082243D8;
        p = tbase + *(u8 *)(s + 9);
        *(u32 *)(s + 12) = 2;
        *(u32 *)(s + 20) = *(u32 *)(*p + 8);
    }
}
