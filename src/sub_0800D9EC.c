/* ChipSlot_IncUse @ 0x0800D9EC (16 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/chipslot.c (registry: src/chipslot.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


void sub_08004258(u8 *p, u8 idx);

void sub_0800D9EC(u8 *s, u8 idx)
{
    sub_08004258(s + 0x70, idx);
}
