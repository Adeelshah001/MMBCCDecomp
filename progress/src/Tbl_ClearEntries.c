/* Tbl_ClearEntries @ 0x08011170 (68 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave15_D.c (registry: src/wave15_D.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

 typedef signed short s16;

extern u32 GetRomTableEntry_082240B8(u8 a);

extern u8 TableByte_16FAC(u8 a, u8 b);

extern void TblFindClear_02C74(u8 v);

__attribute__((section(".text.w15d_08011170")))
void Tbl_ClearEntries(u8 a)
{
    s16 n = (s16)GetRomTableEntry_082240B8(a);
    u16 i;
    if (n <= 0)
        return;
    for (i = 0; (s16)i < n; ) {
        u32 t;
        TblFindClear_02C74(TableByte_16FAC(a, (u8)i));
        t = (u32)i << 16;
        t += 0x80 << 9;
        i = (u16)(t >> 16);
    }
}
