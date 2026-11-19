/* Get_0802503C @ 0x0802503C (24 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave6_l4_old.c (registry: src/wave6_l4_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x0802503c: Get_0802503C (coordinator-verified). */
u16 sub_080265F8(u8 *s);

extern u8 gUnknown_02007090[];

u16 Get_0802503C(void)
{
    u8 *p = gUnknown_02007090;
    p += 24;
    return sub_080265F8(p);
}
