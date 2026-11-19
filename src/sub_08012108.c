/* Sub_08012108 @ 0x08012108 (136 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36c_08012108_MATCHED.c (registry: mmbcc/src/w36c_08012108_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_080174A4(u32 a, int b);

extern void sub_0800DD2C(u8 *s, u32 a, int b);

extern void sub_0800D9EC(u8 *s, int a);

extern void sub_08017478(u32 a, int b);

extern void sub_0800D9FC(u8 *s);

extern void sub_08017464(u32 a);

extern void sub_08011F68(u8 *s, int a);

void sub_08012108(u8 *s)
{
    u8 *p = s + 124;
    if (s[14] == 0) {
        s[14] = 1;
        sub_080174A4(*(u32 *)(s + 44), 3);
        sub_0800DD2C(s, (int)0xffffc400, 0);
        sub_0800D9EC(s, 0);
        s[18] = 15;
    }
    if (s[14] == 1 && s[18] == 8)
        sub_08017478(*(u32 *)(s + 44), 1);
    sub_0800D9FC(s);
    s[18]--;
    if (s[18] == 0) {
        sub_08017478(*(u32 *)(s + 44), 7);
        sub_08017464(*(u32 *)(s + 44));
        *(u32 *)(s + 44) = 0;
        sub_0800DD2C(s, (int)0xffffc400, 0);
        p[4] = 0;
        sub_08011F68(s, 0);
    }
}
