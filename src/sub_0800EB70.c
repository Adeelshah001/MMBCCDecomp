/* FlagStore_0800EB70 @ 0x0800EB70 (48 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w15c_0800eb70.c (registry: src/w15c_0800eb70.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 gUnknown_02005130[];

void sub_0800E1F0(u8 x);

void sub_0800EB70(u8 a, u8 b)
{
    u8 *q = gUnknown_02005130;
    u8 *p;
    u8 *r;
    p = q;
    p += 37;
    *p = 0;
    if (b == 1)
        *p = b;
    r = q;
    r += 36;
    *r = a;
    sub_0800E1F0(5);
}
