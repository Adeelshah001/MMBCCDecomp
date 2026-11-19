/* IdxLookup_080246FC @ 0x080246FC (38 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w15c_080246fc.c (registry: src/w15c_080246fc.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 sub_08025564(u8 *pp, u8 x);

u8 sub_080246FC(u16 x)
{
    register u8 *pp = (u8 *)0x02007090;
    if (x > 248)
        return 0;
    return (u8)sub_08025564(pp, (u8)x);
}
