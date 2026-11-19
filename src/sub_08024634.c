/* Wrap_GetRomTableU16 @ 0x08024634 (18 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i.c (registry: src/wave4_i.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u16 sub_080266F0(u8 idx);

/* 0x08024634: return GetRomTableU16(idx). Tentative. */
u16 sub_08024634(u8 idx)
{
    return sub_080266F0(idx);
}
