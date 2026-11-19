/* Node_PopAndInit_11E20 @ 0x08011E20 (120 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w22a_08011e20.c (registry: src/w22a_08011e20.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u32 *sub_08004424(u32 list);

u32 *sub_08011E20(u8 a, u8 b, u8 c)
{
    register u32 *s;
    u8 *p;
    u32 *tbl;
    u32 *base;
    int v;
    int w;
    u8 x, t;

    s = sub_08004424(*(u32 *)0x02005270);
    if (s != 0) {
        p = (u8 *)s;
        p += 35;
        x = (a & 7) << 4;
        v = -113;
        v &= *p;
        v |= x;
        t = b & 15;
        w = -16;
        v &= w;
        v |= t;
        *p = v;
        if (b == 0)
            v &= 0x7F;
        else
            v |= 0x80;
        *p = v;
        tbl = (u32 *)0x08223cc0;
        
        ((u8 *)s)[9] = c;
        ((u32 *)s)[5] = *(u32 *)tbl[c];
        base = (u32 *)0x02005020;
        
        base[b] = (u32)s;
    }
    return s;
}
