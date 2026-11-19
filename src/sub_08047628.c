/* Sub_08047628 @ 0x08047628 (36 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34c_08047628_MATCHED.c (registry: staging/wave34_C/w34c_08047628_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_08004E44(u8 *s);

extern void sub_0800BEE0(int x, int y);

extern void sub_0804764C(u8 *s);

int sub_08047628(u8 *s)
{
    sub_08004E44(s);
    sub_0800BEE0(0x40, 0x80);
    s[0]++;
    sub_0804764C(s);
    return 0;
}
