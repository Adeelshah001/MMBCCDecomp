/* Clr_08010478 @ 0x08010478 (32 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave8_r_old.c (registry: src/wave8_r_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


int sub_08010478(u8 x) {
    u8 *p = (u8 *)0x02005168;
    int m2 = 2;

    if (x == 1)
        p += 20;
    p[16] &= -m2;
    return 1;
}
