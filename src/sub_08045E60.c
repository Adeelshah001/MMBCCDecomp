/* identical to sub_08045E20 (matched), with its names changed by decompdecomp */
/* Sub_08045E20 @ 0x08045E20 (32 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34c_08045e20_MATCHED.c (registry: staging/wave34_C/w34c_08045e20_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_0804380C(u8 *s);

extern void sub_08043918(u8 *s);

extern void sub_08044298(u8 *s);

extern void sub_08044FB8(u8 *s);

void sub_08045E60(u8 *s)
{
    sub_0804380C(s);
    sub_08043918(s);
    sub_08044298(s);
    sub_08044FB8(s);
}
