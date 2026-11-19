/* SetField120_U16Pair @ 0x080174C4 (8 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_a.c (registry: src/wave3_a.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x080174C4: *(u16*)(s+120)=b; *(u16*)(s+122)=c. Tentative.
 * The `s += 120` is required: agbcc otherwise keeps the base in r3. */
void sub_080174C4(u8 *s, u16 b, u16 c)
{
    s += 120;
    *(u16 *)s = b;
    *(u16 *)(s + 2) = c;
}
