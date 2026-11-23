/* ChipFlagSet_08037914 @ 0x08037914 (68 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w16c_08037914.c (registry: src/w16c_08037914.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


u32 GetChipInventoryCount(u8 idx);

u8 sub_080245C4(u8 idx);

void sub_08037914(u8 *p, u32 b)
{
    u32 v = (u8)b;
    u16 r = (u16)GetChipInventoryCount((u8)v);
    if (r == 1)
        p[0x469c] = (u8)r;
    else if ((u8)sub_080245C4((u8)v) > 3)
        p[0x469c] = 2;
}
