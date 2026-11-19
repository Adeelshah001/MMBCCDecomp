/* SubClamp_0802C7B4 @ 0x0802C7B4 (38 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave8_r_old.c (registry: src/wave8_r_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef short s16;

u8 sub_0802C7B4(int a, u16 *p) {
    int a16 = a << 16;
    int t = *p;
    u8 borrow = 0;
    u16 ua = (u16)((unsigned)a16 >> 16);
    int d = t - (a16 >> 16);

    *p = (u16)d;
    if ((s16)d <= 0) {
        *p = 0;
        borrow = (u8)(ua - t);
    }
    return borrow;
}
