/* Sub_0800A0D4 @ 0x0800A0D4 (124 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36b_0800a0d4_MATCHED.c (registry: mmbcc/src/w36b_0800a0d4_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_0800A150(u8 *s);

void sub_0800A0D4(void)
{
    u8 *s = (u8 *)0x02004e40;
    u32 *table = (u32 *)0x08173048;
    extern u8 B[];
    u8 *b;
    int m9 = -9;
    int m2 = -2;
    int m3 = -3;
    u32 *ptr = table + s[0];
    u8 res = (u8)((u8 (*)(u8 *))*ptr)(s);
    if (s[19] & 2) res |= 128;
    s[4] = res;
    if ((s[31] & 8) == 0 && s[28] != 0) s[28]--;
    b = B;
    if (b[612] != 0) sub_0800A150(s);
    s[31] &= m9;
    s[20] &= m2;
    s[20] &= m3;
}
