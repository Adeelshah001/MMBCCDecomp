/* NibbleGate_0800B6A4 @ 0x0800B6A4 (66 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w17d_0800b6a4.c (registry: src/w17d_0800b6a4.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_0800B6F4(u8 *p, u8 x);

extern void sub_0800B6E8(u8 *s);

void sub_0800B6A4(u8 *p, u8 b)
{
    if ((p[30] & 0xa0) != 0) {
        sub_0800B6F4(p, 0);
    } else if ((p[31] & 16) != 0) {
        sub_0800B6E8(p);
    } else if ((((u32)p[18] << 28) >> 28) != b) {
        sub_0800B6F4(p, b);
    }
}
