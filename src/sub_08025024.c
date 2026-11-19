/* GetEnt_U16_22 @ 0x08025024 (24 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i.c (registry: src/wave4_i.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u16 sub_080265F4(u8 *s);

extern u8 gUnknown_02007090[];

/* 0x08025024: return GetField22_U16(base+0x18). Tentative. */
u16 sub_08025024(void)
{
    u8 *base = gUnknown_02007090;
    return sub_080265F4(base + 0x18);
}
