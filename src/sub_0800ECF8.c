/* Setup10270_Flag14_0800ECF8 @ 0x0800ECF8 (38 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w22b_0800ecf8.c (registry: src/w22b_0800ecf8.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u32 sub_08010270(u8 a, u32 b, u8 c, s8 d);

extern void sub_0800E1F0(u8 x);

s8 sub_0800ECF8(u8 a, u32 b, u8 c, s8 d)
{
    s8 r = sub_08010270(a, b, c, d);
    if (r == 1) {
        sub_0800E1F0(14);
        return 1;
    }
    return r;
}
