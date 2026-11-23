/* F_080378B8 @ 0x080378B8 (92 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w23d_080378b8.c (registry: src/w23d_080378b8.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u32 TryAddChipToInventory(u8 a);

extern u8 sub_080245C4(u8 idx);

extern u32 GetChipInventoryCount(u8 idx);

u8 sub_080378B8(u8 *p, u8 v)
{
    u8 r = 0;
    if ((u16)TryAddChipToInventory(v) == 0)
        r = 3;
    else if ((u8)sub_080245C4(v) > 3)
        r = 2;
    else if ((u16)GetChipInventoryCount(v) == 1)
        r = 1;
    else if (v == *(p + 0x469E))
        r = 4;
    *(p + 0x469E) = v;
    return r;
}
