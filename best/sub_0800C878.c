/* Sub_0800C878 @ 0x0800C878 (68 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36d_0800c878_MATCHED.c (registry: src/w36d_0800c878_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_0800244C(u8 *p, int v);

void sub_0800C878(u8 *s)
{
    register u8 *q = s + 52;
    register u16 *fp;
    register u8 a;
    register u32 v;
    u8 *entry;
    int w;
    
    a = *q + 1;
    
    v = a;
    
    if (v > 24)
        v = 0;
    *q = (u8)v;
    entry = (u8 *)0x0830b660 + (v >> 2) * 20;
    fp = (u16 *)0x020031e8;
    
    w = 12;
    w &= *fp;
    sub_0800244C(entry, (w << 12) + 0x2320);
}
