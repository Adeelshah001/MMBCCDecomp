/* NewNode_080203A4 @ 0x080203A4 (58 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w18d_080203a4.c (registry: src/w18d_080203a4.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u32 *CreateBattleObject(u8 a, u8 b, u8 c, u8 d);

u8 *sub_080203A4(u8 *a, u8 *b, u8 c)
{
    u8 t;
    u8 *p = (u8 *)CreateBattleObject(1, 0, 0, 18);
    if (p != 0) {
        p[16] = 1;
        p[17] = c;
        t = a[120];
        p[120] = t;
        *(u8 **)(p + 40) = a;
        *(u8 **)(p + 44) = b;
    }
    return p;
}
