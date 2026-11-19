/* Sub_0800C3E4 @ 0x0800C3E4 (56 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34c_0800c3e4_MATCHED.c (registry: staging/wave34_C/w34c_0800c3e4_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_080006DC(u32 a, u32 b, int c);

void sub_0800C3E4(void)
{
    u32 *p1 = (u32 *)0x000014a5;
    u32 *p2 = (u32 *)0x03002440;
    u32 *p3;
    sub_080006DC((u32)p1, (u32)p2, 32);
    p3 = (u32 *)0x020038ac;
    sub_080006DC(0, *(p3 + 1), 32);
    sub_080006DC(4096, *p3, 2048);
}
