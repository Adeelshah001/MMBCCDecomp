/* GetEnt_U8_19 @ 0x0802500C (24 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i.c (registry: src/wave4_i.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 sub_08026550(u8 *s);

extern u8 gUnknown_02007090[];

/* 0x0802500C: return GetU8_19(base+0x18). Tentative. */
u8 sub_0802500C(void)
{
    u8 *base = gUnknown_02007090;
    return sub_08026550(base + 0x18);
}
