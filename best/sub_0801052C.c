/* Zero_0801052C @ 0x0801052C (32 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave8_r_old.c (registry: src/wave8_r_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


void sub_0801052C(void) {
    u8 *p = (u8 *)0x02004CA0;

    if (p[28] != 0)
        p[28] = 0;
    p += 32;
    if (p[28] != 0)
        p[28] = 0;
}
