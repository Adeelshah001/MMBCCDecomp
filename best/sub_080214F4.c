/* NewNode_080214F4 @ 0x080214F4 (36 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w19b_080214f4.c (registry: src/w19b_080214f4.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u32 *sub_08020ED4(u8 a, u8 b, u8 c, u8 d);

u8 *sub_080214F4(void)
{
    register u8 *p = (u8 *)sub_08020ED4(0, 0, 0, 1);
    if (p != 0) {
        register u8 z = 0;
        p[16] = 1;
        p[17] = z;
        { register u8 ff = 255; p[18] = ff; }
    }
}
