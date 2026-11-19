/* OrBit_0800B29C @ 0x0800B29C (24 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x0800b29c: OrBit (24B, coordinator-verified). */
extern unsigned short gUnknown_02004E40[];

void sub_0800B29C(unsigned short v)
{
    if (gUnknown_02004E40[7] != 0)
        gUnknown_02004E40[7] = v | gUnknown_02004E40[7];
}
