/* NewNode_0801D278 @ 0x0801D278 (80 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w19b_0801d278.c (registry: src/w19b_0801d278.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u32 *sub_08017000(u8 a, u8 b, u8 c, u8 d);

u8 *sub_0801D278(u8 *a, u8 *b, u8 *c)
{
    register u8 *aa = a;
    register u8 *bb = b;
    register u8 *cc = c;
    u32 w35 = a[35];
    u8 nib = (w35 << 28) >> 28;
    register u8 *p = (u8 *)sub_08017000(0, 0, nib, 12);
    if (p != 0) {
        register u8 z = 0;
        u32 dw0;
        u32 dw1;
        int t;
        u16 v;
        p[16] = 4;
        p[17] = z;
        dw0 = *(u32 *)cc;
        dw1 = *(u32 *)(cc + 4);
        *(u32 *)(p + 96) = dw0;
        *(u32 *)(p + 100) = dw1;
        t = (aa[34] - 1) << 16;
        v = (u32)t >> 16;
        if (t < 0)
            v = 0;
        p[18] = v;
        *(u8 **)(p + 40) = aa;
        *(u8 **)(p + 44) = bb;
    }
    return p;
}
