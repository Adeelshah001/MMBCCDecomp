/* F_0801D2C8 @ 0x0801D2C8 (62 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w20c_0801d2c8.c (registry: src/w20c_0801d2c8.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u32 *sub_08017000(u8 a, u8 b, u8 c, u8 d);

u32 *sub_0801D2C8(u8 a, u32 b, u32 c, u32 *d)
{
    register u32 type;
    u32 *n;
    type = 6;
    if (a == 0)
        type = 5;
    n = sub_08017000(0, 1, 0, 12);
    if (n != 0) {
        u8 *q = (u8 *)n;
        u32 z = 0;
        u32 v0, v1;
        q[16] = type;
        q[17] = z;
        v0 = d[0];
        v1 = d[1];
        *(u32 *)(q + 96) = v0;
        *(u32 *)(q + 100) = v1;
        *(u32 *)(q + 40) = c;
        *(u32 *)(q + 44) = b;
    }
    return n;
}
