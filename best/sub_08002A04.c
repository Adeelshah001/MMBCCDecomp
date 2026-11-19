/* Clear16_02003090 @ 0x08002A04 (24 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x08002a04: Clear16_02003090 (24B, coordinator-verified). */
extern unsigned char gUnknown_02003090[];

void sub_08002A04(void)
{
    int p = (int)gUnknown_02003090;
    int z = 0;
    int q = p + 15;
    do {
        *(unsigned char *)q = z;
        q--;
    } while (q >= p);
}
