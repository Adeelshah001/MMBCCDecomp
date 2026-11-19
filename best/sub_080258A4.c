/* AddTbl_S14_Idx @ 0x080258A4 (26 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i_old.c (registry: src/wave4_i_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u16 sub_080266F0(u8 idx);

/* 0x080258A4: return GetRomTableU16(idx) + *(u16*)(s+14). Tentative. */
u16 sub_080258A4(u8 *s, u8 idx)
{
    return sub_080266F0(idx) + *(u16 *)(s + 14);
}
