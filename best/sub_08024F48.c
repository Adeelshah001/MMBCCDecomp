/* GetEnt_U16_10 @ 0x08024F48 (40 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i_old.c (registry: src/wave4_i_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u16 sub_080257F8(u8 *s);

extern u8 gUnknown_02007090[];

/* 0x08024F48: return GetU16_10(b+i*144). Tentative. */
u16 sub_08024F48(void)
{
    u8 *base = gUnknown_02007090;
    u8 *b = *(u8 **)(base + 0x14);
    u8 i = b[0x1b0];
    return sub_080257F8(b + i * 144);
}
