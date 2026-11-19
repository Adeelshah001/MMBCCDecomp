/* Node_PopAndInit @ 0x08017000 (132 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w16b_08017000.c (registry: src/w16b_08017000.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u32 *sub_08004424(u32 list);

extern u32 *sub_08004454(u32 list);

extern u32 gUnknown_020053C0;

extern u32 gUnknown_082243D8[];

u32 *sub_08017000(u8 a, u8 b, u8 c, u8 d)
{
    register u32 *s;
    u8 *p;
    u32 *tbl;
    int v;
    int w;
    u8 x, t;

    if (a == 0)
        s = sub_08004424(gUnknown_020053C0);
    else
        s = sub_08004454(gUnknown_020053C0);
    if (s != 0) {
        p = (u8 *)s;
        p += 35;
        x = (b & 7) << 4;
        v = -113;
        v &= *p;
        v |= x;
        t = c & 15;
        w = -16;
        v &= w;
        v |= t;
        *p = v;
        if (c == 0)
            v &= 0x7F;
        else
            v |= 0x80;
        *p = v;
        tbl = gUnknown_082243D8;
        ((u8 *)s)[9] = d;
        ((u32 *)s)[5] = *(u32 *)tbl[d];
    }
    return s;
}
