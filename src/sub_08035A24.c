/* Sub_08035A24 @ 0x08035A24 (216 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w38a_08035a24_MATCHED.c (registry: mmcc/src/w38a_08035a24_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern int sub_080247C4(int idx);

extern u32 sub_08024434(u16 a);

extern void sub_08006A54(u32 a, int b, int c, int d, int e);

extern int sub_080241D0(int a);

extern u32 sub_080246A8(u16 idx);

extern void sub_08006DD8(int a, int b, int c, int d, int e);

extern void sub_08024F88(u8 *a);

extern void sub_080068F0(u8 *a, int b, int c, int d, int e);

void sub_08035A24(void)
{
    u8 buf[48];
    u16 c7 = 0;
    u8 c6 = 0;
    u8 i;
    for (i = 1; i <= 243; i++) {
        u8 arg = i;
        u8 ret;
        if (i > 194)
            arg = (u8)(i + 5);
        ret = (u8)sub_080247C4(arg);
        if (ret != 0) {
            c7 += ret;
            c6++;
        }
    }
    c7++;
    c6++;
    sub_08006A54(sub_08024434(4096), 2, 4, 4, 0);
    sub_08006A54(sub_080246A8((u8)sub_080241D0(4096)), 8, 4, 8, 0);
    sub_08006DD8(c6, 17, 4, 3, 0);
    sub_08006A54(*(u32 *)0x0822E9AC, 20, 4, 1, 0);
    sub_08006DD8(c7, 21, 4, 4, 0);
    sub_08006A54(*(u32 *)0x0822E9B4, 25, 4, 1, 0);
    sub_08024F88(buf);
    sub_080068F0(buf, 2, 7, 25, 0);
}
