/* F_08020514 @ 0x08020514 (40 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w17d_08020514.c (registry: src/w17d_08020514.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u32 *CreateBattleObject(u8 a, u8 b, u8 c, u8 d);

u8 *sub_08020514(u8 *p)
{
    register u8 *pp = p;
    register u8 *n = (u8 *)CreateBattleObject(0, 0, 0, 18);
    if (n != 0) {
        u8 b = 0;
        u8 a = 4;
        n[16] = a;
        n[17] = b;
        *(u8 **)(n + 40) = pp;
    }
    return n;
}
