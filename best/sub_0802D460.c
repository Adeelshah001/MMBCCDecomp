/* PairBonus_2D460 @ 0x0802D460 (40 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave10_L_old.c (registry: src/wave10_L_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x0802D460 (40B): pair-bonus check; 6 if (y,x) in {(4,4),(3,1),(2,4)}. */
u8 sub_0802D460(u8 x, u8 y)
{
    u8 r = 0;
    if (y == 4 && x == 4)
        r = 6;
    else if (y == 3 && x == 1)
        r = 6;
    else if (y == 2 && x == 4)
        r = 6;
    return r;
}
