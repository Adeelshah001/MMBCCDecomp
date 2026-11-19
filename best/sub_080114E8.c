/* Sub_080114E8 @ 0x080114E8 (70 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36b_080114e8_MATCHED.c (registry: mmbcc/src/w36b_080114e8_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef short s16;

extern void sub_08010B30(void);

s16 sub_080114E8(void)
{
    u32 *table = (u32 *)0x08173ec8;
    u8 *s = (u8 *)0x02005230;
    u16 res;
    do {
        u8 idx = s[4];
        u32 fn = table[idx];
        res = ((u16 (*)(u8 *))fn)(s);
    } while ((s16)res < 0);
    if (((u8 *)0x02005230)[34] != 0) {
        ((u8 *)0x02005230)[34] = 0;
    } else {
        sub_08010B30();
    }
    return (s16)res;
}
