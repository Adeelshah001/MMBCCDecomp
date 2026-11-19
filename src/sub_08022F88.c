/* NodeInit_08022F88 @ 0x08022F88 (38 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w18b_08022f88.c (registry: src/w18b_08022f88.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u32 *sub_08020ED4(u8 a, u8 b, u8 c, u8 d);

u8 *sub_08022F88(u32 x)
{
    u8 *r = (u8 *)sub_08020ED4(0, 0, 0, 6);
    if (r != 0) {
        r[16] = 0;
        r[17] = 0;
        *(u32 *)(r + 40) = x;
    }
    return r;
}
