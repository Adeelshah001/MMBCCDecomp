/* Sub_08022E88 @ 0x08022E88 (52 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w35b_08022e88_MATCHED.c (registry: mmbcc/src/w35b_08022e88_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern s8 sub_08026D94(u8 *s);

extern void sub_0800D9FC(u8 *s);

void sub_08022E88(u8 *s)
{
    u8 *ss = s;
    s8 r = sub_08026D94(ss);
    if (r != 3)
    {
        register u8 *tbl = (u8 *)0x08226ef0;
        register u32 idx = ss[9];
        register u32 off = idx << 2;
        u32 v;
        
        off += (u32)tbl;
        *(u32 *)(ss + 12) = 2;
        v = *(u32 *)off;
        v = *(u32 *)(v + 8);
        *(u32 *)(ss + 20) = v;
    }
    else
    {
        sub_0800D9FC(ss);
    }
}
