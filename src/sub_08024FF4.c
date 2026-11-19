/* GetEnt_U8_24 @ 0x08024FF4 (24 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i.c (registry: src/wave4_i.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 sub_0802654C(u8 *s);

extern u8 gUnknown_02007090[];

/* 0x08024FF4: return GetField24_U8(*(0x02007090)+0x18). Tentative.
 * The base local defeats absolute folding (else pool becomes 0x020070A8). */
u8 sub_08024FF4(void)
{
    u8 *base = gUnknown_02007090;
    return sub_0802654C(base + 0x18);
}
