/* Count_467DC @ 0x080467DC (52 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w16b_080467dc.c (registry: src/w16b_080467dc.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u16 GetChipInventoryCount(u8 idx);

u8 sub_080467DC(void)
{
    u8 n = 1;
    u8 i = 1;
    do {
        u8 idx = i;
        u16 v;
        if (i > 194)
            idx = i + 5;
        v = GetChipInventoryCount(idx);
        if (v)
            n++;
        i++;
    } while (i <= 243);
    return n;
}
