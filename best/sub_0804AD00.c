/* Sub_0804AD00 @ 0x0804AD00 (36 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34c_0804ad00_MATCHED.c (registry: staging/wave34_C/w34c_0804ad00_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern int sub_0804AD7C(void);

s8 sub_0804AD00(void)
{
    u8 *p = (u8 *)0x0200bd20;
    s8 r;
    
    r = sub_0804AD7C();
    if (r == 0)
    {
        u8 *q = p;
        q += 161;
        return *(s8 *)q;
    }
    return r;
}
