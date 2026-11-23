/* NewNode_0801F154 @ 0x0801F154 (44 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w18d_0801f154.c (registry: src/w18d_0801f154.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u32 *CreateBattleObject(u8 a, u8 b, u8 c, u8 d);

u8 *sub_0801F154(u8 *a, u8 *b)
{
    u8 *p = (u8 *)CreateBattleObject(0, 1, 0, 17);
    if (p != 0) {
        u8 z = 0;
        p[16] = 3;
        p[17] = z;
        *(u8 **)(p + 40) = a;
        *(u8 **)(p + 44) = b;
    }
    return p;
}
