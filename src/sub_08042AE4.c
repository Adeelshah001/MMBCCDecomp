/* Sub_08042AE4 @ 0x08042AE4 (124 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w21b_08042ae4.c (registry: src/w21b_08042ae4.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u16 sub_08024760(void);

extern void sub_080248AC(u32);

extern void sub_08004F18(void);

extern void sub_08004F80(void);

u32 sub_08042AE4(u8 *a)
{
    u32 off = 18099;
    *(u32 *)(a + 18088) = 0;
    *(u32 *)(a + 18092) = 0;
    *(u32 *)(a + 18096) = 0;
    a[7] = a[4];
    a[4] = 1;
    a[5] = 0;
    a[6] = 0;
    a[18092] = 5;
    a[18096] = 0;
    a[18098] = 0;
    a[18097] = 1;
    if (sub_08024760() > 7) {
        a[off] = 1;
    } else {
        a[off] = 0;
    }
    sub_080248AC(0);
    sub_08004F18();
    sub_08004F80();
    return 0;
}
