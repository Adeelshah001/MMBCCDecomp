/* Sub_08017A24 @ 0x08017A24 (32 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w37c2_08017a24_MATCHED.c (registry: mmbcc/src/w37c2_08017a24_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


void Sub_08017A24(u8 *s)
{
    u32 **tbl = (u32 **)0x082243d8;
    register u32 **addr;
    s[10] &= 254;
    
    addr = (u32 **)(s[9] * 4 + (int)tbl);
    *(u32 *)(s + 12) = 4;
    *(u32 *)(s + 20) = *(u32 *)((u8 *)*addr + 16);
}
