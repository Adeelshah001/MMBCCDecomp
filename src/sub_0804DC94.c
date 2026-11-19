/* Sram_RetryWrapper @ 0x0804DC94 (56 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/sram.c (registry: src/sram.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


u8 *sub_0804DC30(u8 *dst, u8 *src, u32 len);

void sub_0804DBC0(u8 *src, u8 *dst, u32 len);

u8 *sub_0804DC94(u8 *dst, u8 *src, u32 len)
{
    u8 tries;
    u8 *res;

    for (tries = 0; tries <= 2; tries++) {
        sub_0804DBC0(dst, src, len);
        res = sub_0804DC30(dst, src, len);
        if (res == 0)
            break;
    }
    return res;
}
