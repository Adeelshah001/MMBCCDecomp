/* CondCopy_0800EAF4 @ 0x0800EAF4 (48 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w15c_0800eaf4.c (registry: src/w15c_0800eaf4.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 gUnknown_02005130[];

void sub_0800E1F0(u8 x);

void sub_0800EAF4(u8 x, u8 y)
{
    u8 *p = gUnknown_02005130;
    if (p[4] != x || p[5] != y)
    {
        p[6] = x;
        p[7] = y;
        sub_0800E1F0(2);
    }
}
