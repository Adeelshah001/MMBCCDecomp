/* ChipInit_0801709C @ 0x0801709C (40 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w17c_chipinit.c (registry: src/w17c_chipinit.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u32 *sub_08017000(u8 a, u8 b, u8 c, u8 d);

/* 0x0801709c (40 B): Node_PopAndInit(0,0,0,0) leaf. */
u32 *sub_0801709C(u8 a)
{
    u32 *n = sub_08017000(0, 0, 0, 0);
    if (n != 0) {
        u8 *q = (u8 *)n;
        u32 z = 0;
        q[16] = a;
        q[17] = (u8)z;
        *(u32 *)(q + 40) = z;
    }
    return n;
}
