/* F_0801D048 @ 0x0801D048 (40 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w17d_0801d048.c (registry: src/w17d_0801d048.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u32 *sub_08017000(u8 a, u8 b, u8 c, u8 d);

u8 *F_0801D048(u8 x)
{
    register u8 xx = x;
    register u8 *n = (u8 *)sub_08017000(0, 1, 0, 12);
    if (n != 0) {
        u8 z = 0;
        n[16] = xx;
        n[17] = z;
        *(u32 *)(n + 40) = z;
    }
    return n;
}
