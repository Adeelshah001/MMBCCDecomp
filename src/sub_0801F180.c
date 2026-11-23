/* NewNode_0801F180 @ 0x0801F180 (40 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w19b_0801f180.c (registry: src/w19b_0801f180.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u32 *CreateBattleObject(u8 a, u8 b, u8 c, u8 d);

u8 *sub_0801F180(u8 *a)
{
    register u8 *p = (u8 *)CreateBattleObject(1, 1, 0, 17);
    register u8 *aa = a;
    if (p != 0) {
        register u8 z = 0;
        p[16] = 5;
        p[17] = z;
        *(u8 **)(p + 40) = aa;
    }
    return p;
}
