/* Sub_0800EDB0 @ 0x0800EDB0 (52 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36d_0800edb0_MATCHED.c (registry: src/w36d_0800edb0_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern int sub_08010478(int flag);

extern void sub_0800E1F0(int v);

int sub_0800EDB0(u8 a)
{
    register int flag;
    u8 *dst;
    s8 r;
    if ((a << 24) == 0)
        flag = 0;
    else
        flag = 1;
    dst = (u8 *)0x02005130;
    
    dst += 43;
    *dst = (u8)flag;
    r = sub_08010478(flag);
    if (r == 1) {
        sub_0800E1F0(17);
        return 1;
    }
    return r;
}
