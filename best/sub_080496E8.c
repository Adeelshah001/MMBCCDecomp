/* AddTableEntry_082344CC @ 0x080496E8 (28 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x080496e8: AddTableEntry_082344CC (28B, coordinator-verified). */
extern unsigned char gUnknown_082344CC[];

unsigned char sub_080496E8(unsigned char a, unsigned char b)
{
    return gUnknown_082344CC[a] + b;
}
