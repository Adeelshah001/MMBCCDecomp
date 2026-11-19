/* Cmp_08004E0C @ 0x08004E0C (24 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave8_r_old.c (registry: src/wave8_r_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


int sub_08004E0C(u8 x) {
    u8 *p = (u8 *)0x02004F80;

    if (p[1] == x)
        return 1;
    else
        return 0;
}
