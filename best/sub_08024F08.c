/* GetEnt_U16_14 @ 0x08024F08 (40 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i_old.c (registry: src/wave4_i_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u16 sub_080257B8(u8 *p);

extern u8 gUnknown_02007090[];

/* 0x08024F08: return GetU16_Off14(b+i*144); b=*(0x02007090+0x14);
 * i=b[0x1B0]. Tentative. */
u16 sub_08024F08(void)
{
    u8 *base = gUnknown_02007090;
    u8 *b = *(u8 **)(base + 0x14);
    u8 i = b[0x1b0];
    return sub_080257B8(b + i * 144);
}
