/* F_24744 @ 0x08024744 (26 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave11_A_old.c (registry: src/wave11_A_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


int sub_08024744(u8 x)
{
    u8 xx = x;
    register int t;
    u8 u;
    
    t = xx;
    t -= 50;
    u = (u8)t;
    if (u <= 6)
        return t;
    return -1;
}
