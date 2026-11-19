/* TblWalkRet_08011BE0 @ 0x08011BE0 (28 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w18b_08011be0.c (registry: src/w18b_08011be0.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 *sub_080113F4(u16 cur);

u16 TblWalkRet_08011BE0(u16 x)
{
    u8 *r = sub_080113F4(x);
    if (r == 0)
        return 0;
    return x;
}
