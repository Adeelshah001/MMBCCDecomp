/* sub_08024EB8 @ 0x08024EB8 (40 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w18b_08024eb8.c (registry: src/w18b_08024eb8.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u16 SumStrides_25754(u8 *tbl);

__attribute__((section(".text.w18b_08024eb8")))
u16 sub_08024EB8(void)
{
    u32 *pp = (u32 *)0x02007090;
    u8 *base = (u8 *)pp[5];
    u32 off = 216;
    u8 idx;
    u32 sc;

    off <<= 1;
    idx = base[off];
    sc = idx;
    sc = (sc << 3) + sc;
    sc <<= 4;
    return (u16)SumStrides_25754(base + sc);
}
