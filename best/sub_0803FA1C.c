/* CheckId_FA1C @ 0x0803FA1C (44 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave8_s_old.c (registry: src/wave8_s_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


u32 sub_0803FA1C(u16 x)
{
    register int sx = (u16)x;
    register int sx2 = sx;
    u32 r = 0;
    if (sx == 64)
        goto L1;
    if (sx > 64)
        goto L2;
    if (sx == 17)
        goto L1;
    goto Lend;
L2:
    if (sx2 == (130 << 5))
        goto L1;
    if (sx2 != (157 << 5))
        goto Lend;
L1:
    r = 1;
Lend:
    return r;
}
