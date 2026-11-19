/* NewNode_0801CDAC @ 0x0801CDAC (44 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w18d_0801cdac.c (registry: src/w18d_0801cdac.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u32 *sub_08017000(u8 a, u8 b, u8 c, u8 d);

u8 *sub_0801CDAC(u8 a, u8 b)
{
    u8 *p = (u8 *)sub_08017000(0, 0, a, 11);
    if (p != 0) {
        u8 z = 0;
        p[16] = b;
        p[17] = a;
        *(u32 *)(p + 40) = z;
    }
    return p;
}
