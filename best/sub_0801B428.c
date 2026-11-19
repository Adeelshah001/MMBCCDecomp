/* Step_0801b428 @ 0x0801B428 (82 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36a_0801b428_MATCHED.c (registry: mmbcc/src/w36a_0801b428_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed int s32;

extern void sub_0800DD4C(void *o, s32 x, s32 y);

extern void *sub_0800DD08(void *d, void *s);

u32 sub_0801B428(u8 *s)
{
    u32 buf[2];
    u8 v;
    sub_0800DD4C(s, *(u32 *)(s + 88), *(u32 *)(s + 92));
    *(u32 *)(s + 88) += *(u32 *)(s + 96);
    *(u32 *)(s + 92) += *(u32 *)(s + 100);
    sub_0800DD08(buf, s);
    if (s[13] != 0)
        return 0;
    if ((s8)--s[18] != 0)
        return 0;
    v = s[10];
    v &= 253;
    v &= 254;
    s[10] = v;
    return 1;
}
