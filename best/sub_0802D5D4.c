/* Sub_0802D5D4 @ 0x0802D5D4 (156 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w37c_0802d5d4_MATCHED.c (registry: mmbcc/src/w37c_0802d5d4_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 sub_08024618(u8 v);

extern void sub_0802D670(u8 *p);

void sub_0802D5D4(u8 *s)
{
    u16 z;
    u8 t = sub_08024618(s[32]);
    z = 0;
    s[8] = t;
    s[9] = sub_08024618(s[176]);
    sub_0802D670(s + 336);
    sub_0802D670(s + 364);
    s[392] = 2;
    s[393] = 2;
    if ((s[404] & 15) == 4)
        *(u16 *)(s + 166) = z;
    if ((s[404] & 240) == 64)
        *(u16 *)(s + 154) = z;
    if ((s[408] & 15) == 4)
        *(u16 *)(s + 310) = z;
    if ((s[408] & 240) == 64)
        *(u16 *)(s + 298) = z;
}
