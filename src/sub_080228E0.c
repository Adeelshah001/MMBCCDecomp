/* NewNode_080228E0 @ 0x080228E0 (46 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w19b_080228e0.c (registry: src/w19b_080228e0.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u32 *sub_08020ED4(u8 a, u8 b, u8 c, u8 d);

u8 *sub_080228E0(u8 *a)
{
    register u8 *p = (u8 *)sub_08020ED4(1, 1, 0, 5);
    register u8 *aa = a;
    if (p != 0) {
        u32 dw0;
        u32 dw1;
        p[16] = 2;
        p[17] = aa[17];
        dw0 = *(u32 *)(aa + 80);
        dw1 = *(u32 *)(aa + 84);
        *(u32 *)(p + 80) = dw0;
        *(u32 *)(p + 84) = dw1;
    }
    return p;
}
