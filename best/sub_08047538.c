/* Rank_FromValue @ 0x08047538 (154 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_e_old.c (registry: src/wave7_e_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x08047538: Rank_FromValue (coordinator-verified, 154B + 2B 00 pad).
   old_agbcc omits push {lr} for true-leaf switch functions. */
int sub_08047538(s8 x)
{
    int r = 0;
    switch (x) {
    case 0: r = 0; break;
    case 5: r = 1; break;
    case 10: r = 2; break;
    case 15: r = 3; break;
    case 20: r = 4; break;
    case 25: r = 5; break;
    }
    return r;
}
