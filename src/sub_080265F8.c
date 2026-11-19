/* Sub80_Field22 @ 0x080265F8 (20 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i.c (registry: src/wave4_i.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u16 sub_080265F4(u8 *s);

/* 0x080265F8: return 0x80 - GetField22_U16(s). Tentative.
 * No u16 local: the call result must feed `subs` directly, else agbcc
 * truncates early. */
u16 sub_080265F8(u8 *s)
{
    return 0x80 - sub_080265F4(s);
}
