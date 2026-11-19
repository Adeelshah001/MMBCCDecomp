/* GetU16_Off14 @ 0x080257B8 (4 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_b.c (registry: src/wave3_b.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* Halfword getter at struct offset 14 (TENTATIVE name).
 * ROM 0x080257B8 (4 B). */
u16 sub_080257B8(u8 *p)
{
    return *(u16 *)(p + 14);
}
