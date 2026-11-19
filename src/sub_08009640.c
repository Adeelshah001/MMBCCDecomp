/* SetByte620_FF @ 0x08009640 (20 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x08009640: SetByte620_FF (20B, coordinator-verified). */
extern unsigned char gUnknown_02004830[];

void sub_08009640(void)
{
    gUnknown_02004830[620] = 0xff;
}
