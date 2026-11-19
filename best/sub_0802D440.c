/* Check_2D440 @ 0x0802D440 (32 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave9_d_old.c (registry: src/wave9_d_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


u8 sub_0802D440(u8 a, u8 b, u8 c)
{
    u8 r = 0;
    if (a != 2 && b == c && b != 0)
        r = 6;
    return r;
}
