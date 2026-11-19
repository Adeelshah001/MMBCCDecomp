/* Dispatch_0801BF10 @ 0x0801BF10 (164 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w26c_0801bf10.c (registry: src/w26c_0801bf10.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


u32 *sub_080178A8(u8 a, u8 b, u16 c, u16 d, u8 *e);

void sub_080174A4(u8 *s, u8 bit);

u8 sub_08017474(u8 *s);

void sub_0800D9EC(u8 *s, u8 idx);

void sub_08017478(u8 *s, u8 v);

extern u8 gUnknown_08226884[];

u8 sub_0801BF10(u8 *s)
{
    switch (s[13]) {
    case 0:
        if ((u8)(s[119] - 3) > 1)
            break;
        {
            u8 t = gUnknown_08226884[s[17]];
            sub_080178A8(t, (u8)(((u32)s[35] << 28) >> 28), (u16)(0xF0 << 6), 0, *(u8 **)(s + 44));
            sub_080174A4(*(u8 **)(s + 44), 3);
            sub_0800D9EC(s, 1);
            s[13]++;
        }
        break;
    case 1:
        if (sub_08017474(*(u8 **)(s + 44)) > 5) {
            sub_0800D9EC(s, 2);
            s[13]++;
        }
        break;
    case 2:
        if ((u8)(s[119] - 3) > 1)
            break;
        sub_08017478(*(u8 **)(s + 44), 7);
        return 1;
    default:
        break;
    }
    return 0;
}
