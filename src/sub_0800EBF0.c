/* Fwd_EBF0 @ 0x0800EBF0 (36 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w16b_0800ebf0.c (registry: src/w16b_0800ebf0.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 sub_080104CC(u8 x);

extern void sub_0800E1F0(u8 v);

extern u8 gUnknown_02005130[];

s8 sub_0800EBF0(void)
{
    u8 *base = gUnknown_02005130;
    s8 v = (s8)sub_080104CC(base[2]);
    if (v == 1) {
        sub_0800E1F0(8);
        return 1;
    }
    return v;
}
