/* Sub_08004EF4 @ 0x08004EF4 (36 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34c_08004ef4_MATCHED.c (registry: staging/wave34_C/w34c_08004ef4_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_0800D420(int);

extern void sub_0800D55C(void);

extern void sub_08020EA4(u8 *p1, u8 *p2, int n);

void sub_08004EF4(void)
{
    sub_0800D420(1);
    sub_0800D55C();
    sub_08020EA4((u8 *)0x02004ff0, (u8 *)0x02006700, 18);
}
