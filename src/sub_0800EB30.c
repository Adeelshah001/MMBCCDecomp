/* F_0800EB30 @ 0x0800EB30 (64 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w20d_0800eb30.c (registry: src/w20d_0800eb30.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 sub_0800FFF4(u8 a, u8 b, u8 c, u8 d, u8 e, u8 f);

extern void sub_0800E1F0(u8 v);

s8 sub_0800EB30(u8 a, u8 b, u8 c, u8 d, u8 e, u8 f)
{
    s8 r = (s8)sub_0800FFF4(a, b, c, d, e, f);
    if (r == 1) {
        sub_0800E1F0(4);
        return 1;
    }
    return r;
}
