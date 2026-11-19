/* Sub_08015A60 @ 0x08015A60 (100 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36a_08015a60_MATCHED.c (registry: mmbcc/src/w36a_08015a60_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_0800DD2C(u8 *a, u32 b, u32 c);

extern void sub_0800D9EC(u8 *a, u32 b);

extern void sub_0800D9FC(u8 *a);

extern void sub_08017464(u32 a);

extern void sub_08011F68(u8 *a, u32 b);

void sub_08015A60(u8 *arg0)
{
    u8 *r6 = arg0 + 124;
    u8 v;
    if (arg0[14] == 0) {
        arg0[14] = 1;
        sub_0800DD2C(arg0, 0xffffc400, 0);
        sub_0800D9EC(arg0, 0);
        arg0[18] = 20;
    }
    sub_0800D9FC(arg0);
    {
        int t = arg0[18] - 1;
        arg0[18] = t;
        v = (u8)t;
    }
    if (v == 0) {
        sub_08017464(*(u32 *)(arg0 + 44));
        *(u32 *)(arg0 + 44) = 0;
        sub_0800DD2C(arg0, 0xffffc400, 0);
        r6[4] = 0;
        sub_08011F68(arg0, 0);
    }
}
