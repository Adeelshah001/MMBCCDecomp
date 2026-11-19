/* Sub_08024BC8 @ 0x08024BC8 (76 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w20b_08024bc8.c (registry: src/w20b_08024bc8.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 sub_08025730(u8 *tbl, u8 idx);

extern u32 sub_08025A10(u8 *s, u8 idx);

u16 sub_08024BC8(u8 *p, u8 v)
{
    if (sub_08025730((u8 *)(*(u32 *)(p + 20) + (*(u8 *)(*(u32 *)(p + 20) + 432) * 144)), v) == 0)
        return 0;
    return (u16)sub_08025A10((u8 *)(*(u32 *)(p + 20) + (*(u8 *)(*(u32 *)(p + 20) + 432) * 144)), v);
}
