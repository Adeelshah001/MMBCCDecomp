/* NodeInit_08021DA8 @ 0x08021DA8 (40 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w18b_08021da8.c (registry: src/w18b_08021da8.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u32 *sub_08020ED4(u8 a, u8 b, u8 c, u8 d);

u8 *sub_08021DA8(u8 *p)
{
    u8 *r = (u8 *)sub_08020ED4(1, 0, 0, 3);
    if (r != 0) {
        r[16] = 3;
        r[17] = p[17];
        *(u32 *)(r + 40) = (u32)p;
    }
    return r;
}
