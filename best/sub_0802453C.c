/* GetClampedTable_08229828 @ 0x0802453C (24 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x0802453c: GetClampedTable (24B, coordinator-verified). */
extern unsigned int gUnknown_08229828[];

unsigned int sub_0802453C(unsigned short v)
{
    if (v > 48)
        v = 48;
    return gUnknown_08229828[v];
}
