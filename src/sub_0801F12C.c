/* F_0801F12C @ 0x0801F12C (40 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w17d_0801f12c.c (registry: src/w17d_0801f12c.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u32 *CreateBattleObject(u8 a, u8 b, u8 c, u8 d);

u8 *sub_0801F12C(u8 *p)
{
    register u8 *pp = p;
    register u8 *n = (u8 *)CreateBattleObject(0, 1, 0, 17);
    if (n != 0) {
        u8 b = 0;
        u8 a = 2;
        n[16] = a;
        n[17] = b;
        *(u8 **)(n + 40) = pp;
    }
    return n;
}
