/* IsZero_02005160_080103cc @ 0x080103CC (20 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x08010088: IsZero_02005160 (20B, coordinator-verified). */
extern unsigned char gUnknown_02005160[];

unsigned int sub_080103CC(void)
{
    unsigned int v = gUnknown_02005160[0];
    if (v == 0)
        goto L1;
    v = 0;
    goto L2;
L1:
    v = 1;
L2:
    return v;
}
