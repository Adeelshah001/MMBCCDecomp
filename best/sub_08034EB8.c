/* Sub_08034EB8 @ 0x08034EB8 (114 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36b_08034eb8_MATCHED.c (registry: mmbcc/src/w36b_08034eb8_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 sub_080245C4(u8 b);

extern u32 sub_080400A8(void);

extern u32 sub_0804DDA0(u32 a, u32 b);

u8 sub_08034EB8(u8 *base, u8 arg1)
{
    register u8 *b8;
    u8 buf[12];
    u8 target;
    u8 count;
    u8 res;
    u8 i;
    b8 = base;
    target = arg1;
    count = 0;
    res = count;
    for (i = 1; i <= 11; i++) {
        u8 *elem = i * 12 + b8;
        if ((u8)sub_080245C4(*elem) == target && *elem != 0) {
            buf[count] = *elem;
            count++;
        }
    }
    if (count != 0) {
        u16 rnd = sub_080400A8();
        u32 idx = sub_0804DDA0(rnd, count);
        res = buf[idx];
    }
    return res;
}
