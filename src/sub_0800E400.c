/* GuardedListInit_0800E400 @ 0x0800E400 (64 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w15c_0800e400.c (registry: src/w15c_0800e400.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 sub_08010088(void);

extern void sub_0800E1F0(u8 x);

extern void sub_0800D568(u8 *p);

void sub_0800E400(void)
{
    u16 *p = (u16 *)0x02005130;
    u8 z = 0;
    p[12] = 1;
    if ((s8)sub_08010088() == 1) {
        p[12] = z;
        sub_0800E1F0(z);
    }
    sub_0800D568(*(u8 **)0x02005270);
    sub_0800D568(*(u8 **)0x020053C0);
}
