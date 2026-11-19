/* Sub_0800C5A4 @ 0x0800C5A4 (20 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w35c_0800c5a4_MATCHED.c (registry: mmbcc/src/w35c_0800c5a4_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


void sub_0800C5A4(u8 *p)
{
    u16 a = (p[22] - 1) & 63;
    u16 b = (p[24] - 1) & 63;
    *(u16 *)(p + 22) = a;
    *(u16 *)(p + 24) = b;
}
