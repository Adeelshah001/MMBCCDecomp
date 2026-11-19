/* F_080228BC @ 0x080228BC (34 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w17d_080228bc.c (registry: src/w17d_080228bc.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u32 *sub_08020ED4(u8 a, u8 b, u8 c, u8 d);

u8 *sub_080228BC(void)
{
    register u8 *r = (u8 *)sub_08020ED4(1, 1, 0, 5);
    if (r != 0) {
        u8 b = 0;
        u8 a = 1;
        r[16] = a;
        r[17] = b;
    }
    return r;
}
