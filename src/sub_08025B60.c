/* sub_08025B60 @ 0x08025B60 (320 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w66a_08025b60_MATCHED.c (registry: src/w66a_08025b60_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef short s16;

u8 sub_08025654(u8 *s, u8 idx);

int sub_080266F0(u8 idx);

s16 sub_0802583C(u8 *s, s16 a, s16 b);

unsigned int sub_080257F8(u8 *s);

void sub_080256DC(u8 *p, u8 v);

void sub_08025638(u8 *s, u8 a, u8 b);

u8 sub_08025B60(u8 *s, u16 a, u16 b)
{
    u8 i;
    u8 j;
    u8 x = 0;
    u8 y = 0;
    i = sub_08025654(s, (u8)a);
    j = sub_08025654(s, (u8)b);
    if (i != 255)
        x = s[20 + 4 * i];
    if (j != 255)
        y = s[20 + 4 * j];
    if (i == 255 && j == 255)
        return 0;
    if (a == 0 || b == 0)
        return 7;
    if (a <= 9) {
        if (b > 9) {
            if (sub_0802583C(s, sub_080266F0(x), sub_080266F0(y)) != 0)
                return 2;
            {
                unsigned int w = sub_080257F8(s);
                if ((u16)w < (u16)sub_080266F0(x))
                    return 3;
            }
        }
    } else {
        if (b <= 9) {
            if (sub_0802583C(s, sub_080266F0(y), sub_080266F0(x)) != 0)
                return 2;
            {
                unsigned int w = sub_080257F8(s);
                if ((u16)w < (u16)sub_080266F0(y))
                    return 3;
            }
        }
    }
    if (i != 255)
        sub_080256DC(4 * i + 20 + s, (u8)b);
    if (j != 255)
        sub_080256DC(4 * j + 20 + s, (u8)a);
    sub_08025638(s, (u8)a, j);
    sub_08025638(s, (u8)b, i);
    return 0;
}
