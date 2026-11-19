/* Sub_0800BF44 @ 0x0800BF44 (40 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34c_0800bf44_MATCHED.c (registry: staging/wave34_C/w34c_0800bf44_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed short s16;

extern void sub_0800C4B4(u8 *p);

extern void sub_0800C41C(s16 x);

void sub_0800BF44(u32 a)
{
    u16 aa = a;
    u8 *p = (u8 *)0x02004f40;
    sub_0800C4B4(p);
    *(u16 *)(p + 20) = aa;
    sub_0800C41C((s16)aa);
}
