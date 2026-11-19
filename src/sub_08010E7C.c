/* F_08010E7C @ 0x08010E7C (36 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w21d_08010e7c.c (registry: src/w21d_08010e7c.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u32 sub_08010EC4(u8 a, s8 b, s8 c, s8 d, u8 e);

u32 sub_08010E7C(u8 a, s8 b, s8 c, s8 d)
{
    return sub_08010EC4(a, b, c, d, 0);
}
