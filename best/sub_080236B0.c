/* NewNode_080236B0 @ 0x080236B0 (64 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w19b_080236b0.c (registry: src/w19b_080236b0.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u32 *sub_08020ED4(u8 a, u8 b, u8 c, u8 d);

u8 *sub_080236B0(u32 a, u8 *b, u8 *c, u8 *d)
{
    register u8 *cc = c;
    register u8 *dd = d;
    u8 aa = (u8)a;
    u8 nib;
    u32 w35;
    u8 *p;
    w35 = cc[35];
    nib = (w35 << 28) >> 28;
    p = (u8 *)sub_08020ED4(0, 1, nib, 7);
    if (p != 0) {
        u8 z = 0;
        u32 dw0;
        u32 dw1;
        p[16] = z;
        p[17] = aa;
        dw0 = *(u32 *)dd;
        dw1 = *(u32 *)(dd + 4);
        *(u32 *)(p + 96) = dw0;
        *(u32 *)(p + 100) = dw1;
        *(u8 **)(p + 40) = b;
        *(u8 **)(p + 44) = cc;
    }
    return p;
}
