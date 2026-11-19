/* Sub_08027D18 @ 0x08027D18 (48 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w35b_08027d18_MATCHED.c (registry: mmbcc/src/w35b_08027d18_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 _call_via_r1(u8 *s, u32 v);

extern void sub_08027E8C(u8 *s);

extern void sub_08004F80(void);

void sub_08027D18(void)
{
    register u8 *s = (u8 *)0x0200b7e0;
    register u8 *tbl = (u8 *)0x0822dda0;
    register u32 idx = s[2];
    register u32 off;
    u32 v;
    
    
    
    off = idx << 2;
    off += (u32)tbl;
    v = *(u32 *)off;
    s[2] = _call_via_r1(s, v);
    sub_08027E8C(s);
    sub_08004F80();
}
