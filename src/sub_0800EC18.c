/* FlagByteSet_0800EC18 @ 0x0800EC18 (36 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w15c_0800ec18.c (registry: src/w15c_0800ec18.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 gUnknown_02005130[];

void sub_0800E1F0(u8 x);

void sub_0800EC18(u8 a)
{
    u32 addr = (u32)gUnknown_02005130;
    u8 *p = (u8 *)addr;
    u8 b = (u8)a;
    p[37] = 0;
    if (b == 1)
        p[37] = b;
    sub_0800E1F0(10);
}
