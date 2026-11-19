/* F_080251d8 @ 0x080251D8 (50 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave14_C_old.c (registry: src/wave14_C_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* F_08025790 @ 0x08025790 */
u8 sub_08025730(u8 *p, u8 v);

 u8 sub_080251B8(u8 *p);

u8 sub_080251D8(u8 *p)
{
    u8 v = p[0xD8 << 1];
    u8 w = sub_08025730(p + v * 144, 0);
    if (w == 0)
        w = sub_080251B8(p);
    return w;
}
