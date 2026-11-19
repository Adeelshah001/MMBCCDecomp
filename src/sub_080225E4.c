/* NodeInit_080225E4 @ 0x080225E4 (38 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w18b_080225e4.c (registry: src/w18b_080225e4.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u32 *sub_08020ED4(u8 a, u8 b, u8 c, u8 d);

u8 *sub_080225E4(u8 x)
{
    u8 *r = (u8 *)sub_08020ED4(0, 2, 0, 4);
    if (r != 0) {
        r[16] = 0;
        r[17] = x;
    }
    return r;
}
