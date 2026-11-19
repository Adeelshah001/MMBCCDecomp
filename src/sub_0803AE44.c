/* TaskInit_0803AE44 @ 0x0803AE44 (76 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w18b_0803ae44.c (registry: src/w18b_0803ae44.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_0804A2DC(u16 a);

extern void sub_08004F18(void);

extern void sub_08004F80(void);

void sub_0803AE44(u8 *p)
{
    u32 z = 0;
    u8 *q;

    *(u32 *)(p + 0x4698) = 0;
    q = p + 0x469c;
    *(u32 *)q = 0;
    p[1] = 1;
    p[2] = 0;
    p[3] = 0;
    *q = 0;
    *(u8 *)(p + 0x469d) = 0;
    sub_0804A2DC(9);
    *(u8 *)(p + 0x46b0) = 0;
    sub_08004F18();
    sub_08004F80();
}
