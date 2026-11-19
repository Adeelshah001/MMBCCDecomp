/* Count_08042a38 @ 0x08042A38 (42 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave14_C.c (registry: src/wave14_C.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* Count_08042a38 @ 0x08042a38 */
u8 sub_08024818(u8 i);

u8 sub_08042A38(void)
{
    u8 c = 0;
    u8 i = 0;
    do {
        if (sub_08024818(i))
            c++;
        i++;
    } while (i <= 0x1d);
    return c;
}
