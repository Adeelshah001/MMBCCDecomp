/* F_08001BF8 @ 0x08001BF8 (16 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w47a_08001bf8_MATCHED.c (registry: src/w47a_08001bf8_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


void sub_08001BF8(void)
{
    *(volatile u16 *)0x04000128 |= 0x80;
}
