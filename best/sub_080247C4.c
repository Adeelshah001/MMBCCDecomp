/* F_080247C4 @ 0x080247C4 (34 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave15_B.c (registry: src/wave15_B.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 sub_08025324(u8 *p, u8 idx);

u8 sub_080247C4(u8 idx)
{
    u8 v = idx;
    u8 **pp = (u8 **)0x02007090;
    
    if (v > 248)
        return 0;
    return sub_08025324(*pp, v);
}
