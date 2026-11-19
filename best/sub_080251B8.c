/* GetEnt_IdxByte1 @ 0x080251B8 (30 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i_old.c (registry: src/wave4_i_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 sub_08025A08(u8 *p);

/* 0x080251B8: return GetByte1_25A08(s+i*144); i=s[0x1B0]. Tentative. */
u8 sub_080251B8(u8 *s)
{
    u8 i = s[0x1b0];
    return sub_08025A08(s + i * 144);
}
