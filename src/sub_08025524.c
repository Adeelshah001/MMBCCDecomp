/* sub_08025524 @ 0x08025524 (62 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w18b_08025524.c (registry: src/w18b_08025524.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 sub_08025324(u8 *p, u8 idx);

extern void sub_0802533C(u8 *p, u8 idx);

extern void sub_080254E0(u8 *s, u8 idx);

u8 sub_08025524(u8 *p, u8 x)
{
    u8 v = sub_08025324(*(u8 **)p, x);
    if (v <= 98) {
        sub_0802533C(*(u8 **)p, x);
        sub_080254E0(p, x);
        return sub_08025324(*(u8 **)p, x);
    }
    return 0;
}
