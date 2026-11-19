/* Wrap_08007324 @ 0x08007324 (84 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36a_08007324_MATCHED.c (registry: mmbcc/src/w36a_08007324_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_080062B4(s8 x, s8 y, u8 w, u8 h, u16 a, u16 b, u32 c);

extern u32 gUnknown_08171474[];

extern u8 gUnknown_02004830[];

void sub_08007324(u16 idx, u16 a, u16 b)
{
    if (gUnknown_02004830[0x265] != 0)
        return;
    sub_080062B4((s8)a, (s8)b, 2, 2, 217, 7, gUnknown_08171474[idx]);
}
