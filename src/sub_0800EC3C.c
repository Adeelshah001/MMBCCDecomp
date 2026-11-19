/* F_0800EC3C @ 0x0800EC3C (64 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w20d_0800ec3c.c (registry: src/w20d_0800ec3c.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 sub_0801009C(u8 a, u8 b, u8 c, u8 d, u8 e, u8 f);

extern void sub_0800E1F0(u8 v);

s8 sub_0800EC3C(u8 a, u8 b, u8 c, u8 d, u8 e, u8 f)
{
    s8 r = (s8)sub_0801009C(a, b, c, d, e, f);
    if (r == 1) {
        sub_0800E1F0(11);
        return 1;
    }
    return r;
}
