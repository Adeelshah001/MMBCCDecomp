/* F_0800ECD8 @ 0x0800ECD8 (30 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w15c_0800ecd8.c (registry: src/w15c_0800ecd8.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


s8 sub_0801025C(u32 a, s8 b);

void sub_0800E1F0(u8 x);

u32 sub_0800ECD8(u32 a, u8 b)
{
    u32 r = (u32)(s8)sub_0801025C(a, (s8)b);
    if (r == 1)
    {
        sub_0800E1F0(13);
        return 1;
    }
    return r;
}
