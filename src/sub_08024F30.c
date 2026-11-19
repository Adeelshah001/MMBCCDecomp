/* F_08024F30 @ 0x08024F30 (24 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w21d_08024f30.c (registry: src/w21d_08024f30.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_0802611C(u8 *p, u16 a);

void sub_08024F30(u16 a)
{
    u8 **base = (u8 **)0x02007090;
    u8 *p;
    
    p = base[5];
    sub_0802611C(p, a);
}
