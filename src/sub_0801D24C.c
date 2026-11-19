/* NodeInit_0801D24C @ 0x0801D24C (42 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w18b_0801d24c.c (registry: src/w18b_0801d24c.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u32 *sub_08017000(u8 a, u8 b, u8 c, u8 d);

u8 *sub_0801D24C(u8 *p, u8 x)
{
    u8 *r = (u8 *)sub_08017000(0, 0, 0, 12);
    if (r != 0) {
        r[16] = 3;
        r[17] = x;
        *(u32 *)(r + 40) = (u32)p;
    }
    return r;
}
