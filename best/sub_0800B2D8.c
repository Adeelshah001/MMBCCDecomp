/* Tst_0800B2D8 @ 0x0800B2D8 (24 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave8_b_old.c (registry: src/wave8_b_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 gUnknown_02004E40[];

int sub_0800B2D8(void)
{
    u8 v = gUnknown_02004E40[4];
    if ((v & 143) == 128)
        return 1;
    return 0;
}
