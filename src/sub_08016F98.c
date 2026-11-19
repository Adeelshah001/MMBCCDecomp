/* GetRomTableEntry_082240B8 @ 0x08016F98 (20 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x08016f98: GetRomTableEntry_082240B8 (20B, coordinator-verified). */
extern unsigned char gUnknown_082240B8[];

unsigned short sub_08016F98(unsigned char idx)
{
    unsigned char *base = gUnknown_082240B8;
    unsigned int off = idx * 8;
    base += 4;
    return *(unsigned short *)(base + off);
}
