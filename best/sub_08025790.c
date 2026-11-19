/* F_08025790 @ 0x08025790 (38 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave14_C_old.c (registry: src/wave14_C_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* F_08025790 @ 0x08025790 */
u8 sub_08025730(u8 *p, u8 v);

 u32 sub_080266F0(u32 v);

u16 sub_08025790(u8 *p)
{
    u8 v = sub_08025730(p, 0);
    u32 w = v;
    if (v == 0)
        w = p[1];
    w = sub_080266F0(w);
    return (u16)(*(u16 *)(p + 14) + w);
}
