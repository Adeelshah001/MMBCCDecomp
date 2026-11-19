/* Check_080248c4 @ 0x080248C4 (82 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36a_080248c4_MATCHED.c (registry: mmbcc/src/w36a_080248c4_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 sub_08025478(u8 *s, u8 idx);

extern u16 sub_08025958(u8 *p, u8 v);

extern void sub_080254B4(u8 *s, u8 idx);

u32 sub_080248C4(u8 *s, u8 idx)
{
    u16 lim = *(u16 *)(s + 18);
    u8 v;
    u8 *p;
    u8 b;
    if (idx >= lim)
        return 1;
    v = sub_08025478(s, idx);
    p = *(u8 **)(s + 20);
    b = p[432];
    if ((u16)sub_08025958(p + b * 144, v) != 0)
        return 4;
    sub_080254B4(s, idx);
    return 0;
}
