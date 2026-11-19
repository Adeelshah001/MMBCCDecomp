/* sub_08025B60 @ 0x08025B60 (320 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w66a_08025b60_MATCHED.c (registry: src/w66a_08025b60_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef short s16;

u8 TblGet_25654(u8 *s, u8 idx);

int GetRomTableU16(u8 idx);

s16 sub_0802583C(u8 *s, s16 a, s16 b);

unsigned int GetU16_10(u8 *s);

void SetU8_Off1(u8 *p, u8 v);

void StoreIdx2_25638(u8 *s, u8 a, u8 b);

__attribute__((section(".text.w66a_08025b60")))
u8 sub_08025B60(u8 *s, u16 a, u16 b)
{
    u8 i;
    u8 j;
    u8 x = 0;
    u8 y = 0;
    i = TblGet_25654(s, (u8)a);
    j = TblGet_25654(s, (u8)b);
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
            if (sub_0802583C(s, GetRomTableU16(x), GetRomTableU16(y)) != 0)
                return 2;
            {
                unsigned int w = GetU16_10(s);
                if ((u16)w < (u16)GetRomTableU16(x))
                    return 3;
            }
        }
    } else {
        if (b <= 9) {
            if (sub_0802583C(s, GetRomTableU16(y), GetRomTableU16(x)) != 0)
                return 2;
            {
                unsigned int w = GetU16_10(s);
                if ((u16)w < (u16)GetRomTableU16(y))
                    return 3;
            }
        }
    }
    if (i != 255)
        SetU8_Off1(4 * i + 20 + s, (u8)b);
    if (j != 255)
        SetU8_Off1(4 * j + 20 + s, (u8)a);
    StoreIdx2_25638(s, (u8)a, j);
    StoreIdx2_25638(s, (u8)b, i);
    return 0;
}
