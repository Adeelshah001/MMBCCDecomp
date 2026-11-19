/* Sub_0800288C @ 0x0800288C (68 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36d_0800288c_MATCHED.c (registry: src/w36d_0800288c_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_0804DB30(u8 *src, u8 *dst);

extern void sub_0804DB24(u8 *src, u8 *dst, u32 n);

void sub_0800288C(u8 *s, u8 *dst)
{
    register u8 *ss = s;
    register u8 *dd = dst;
    register u8 b;
    register int sh;
    if (*(u16 *)(ss + 4) == 0)
        return;
    b = ss[7];
    sh = b << 5;
    dd += sh;
    if (ss[6] == 0)
        goto second;
    {
        register u8 *src;
        register u32 d2;
        src = ss + *(u32 *)ss;
        d2 = 0x03002420;
        
        d2 = (u32)dd + d2;
        sub_0804DB30(src, (u8 *)d2);
    }
    return;
second:
    {
        register u8 *src;
        register u32 d2;
        src = ss + *(u32 *)ss;
        d2 = 0x03002420;
        
        d2 = (u32)dd + d2;
        sub_0804DB24(src, (u8 *)d2, *(u16 *)(ss + 4) >> 2);
    }
}
