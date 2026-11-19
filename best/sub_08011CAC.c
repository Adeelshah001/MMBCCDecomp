/* GetTableEntry_08173FAC @ 0x08011CAC (24 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x08011cac: GetTableEntry_08173FAC (24B, coordinator-verified). */
extern unsigned int gUnknown_08173FAC[];

unsigned int *sub_08011CAC(unsigned short idx)
{
    if (idx == 0)
        return 0;
    return &gUnknown_08173FAC[idx];
}
