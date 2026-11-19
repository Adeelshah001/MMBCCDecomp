/* Sub_0801BB94 @ 0x0801BB94 (32 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w46d_0801bb94_MATCHED.c (registry: src/w46d_0801bb94_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


void sub_0801BB94(u8 *s)
{
    u8 *entry;
    register u8 *tbase;
    s[10] &= 254;
    tbase = (u8 *)0x082243d8;
    
    entry = (u8 *)(s[9] * 4 + (int)tbase);
    *(u32 *)(s + 12) = 4;
    *(u32 *)(s + 20) = *(u32 *)(*(u32 *)entry + 16);
}
