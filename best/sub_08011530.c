/* Sub_08011530 @ 0x08011530 (48 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w37b_08011530_MATCHED.c (registry: mmbcc/src/w37b_08011530_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


int sub_08011530(u8 *s)
{
    u8 zb = 0;
    u32 zw = 0;
    *(u16 *)(s + 16) = zw;
    *(u16 *)(s + 14) = zw;
    *(u32 *)(s + 8) = zw;
    *(u16 *)(s + 12) = (u16)0xfffe;
    s[36] = zb;
    s[34] = zb;
    s[4]++;
    s[5] = zb;
    s[6] = zb;
    s[7] = zb;
    return -1;
}
