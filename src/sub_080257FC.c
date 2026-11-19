/* Sub_257FC @ 0x080257FC (62 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w16b_080257fc.c (registry: src/w16b_080257fc.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u16 sub_080266F0(u8 idx);

extern u8 sub_08025730(u8 *tbl, u8 idx);

void sub_080257FC(u8 *s, u16 v)
{
    if (sub_080266F0(sub_08025730(s, 10)) > v)
        return;
    if (sub_080266F0(sub_08025730(s, 11)) > v)
        return;
    *(u16 *)(s + 16) = v;
}
