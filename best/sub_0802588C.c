/* AddTbl_S14 @ 0x0802588C (24 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i_old.c (registry: src/wave4_i_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u16 sub_080266F0(u8 idx);

/* 0x0802588C: return GetRomTableU16(s[1]) + *(u16*)(s+14). Tentative.
 * The call must be the first operand for the `adds r0,r4,r0` order. */
u16 sub_0802588C(u8 *s)
{
    return sub_080266F0(s[1]) + *(u16 *)(s + 14);
}
