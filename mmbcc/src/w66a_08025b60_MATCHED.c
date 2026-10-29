/* Wave 66-A RECOMMENDED: 0x08025B60 (320 B, no trailing pool). old_agbcc -O2 -mthumb-interwork, 0 diffs. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;

u8 TblGet_08025654(u8 *s, u8 idx);
int GetRomTableU16_080266F0(u8 idx);
s16 Sub_0802583C(u8 *s, s16 a, s16 b);
unsigned int GetU16_10_080257F8(u8 *s);
void SetU8_Off1_080256DC(u8 *p, u8 v);
void StoreIdx2_08025638(u8 *s, u8 a, u8 b);

__attribute__((section(".text.w66a_08025b60")))
u8 sub_08025B60(u8 *s, u16 a, u16 b)
{
    u8 i;
    u8 j;
    u8 x = 0;
    u8 y = 0;
    i = TblGet_08025654(s, (u8)a);
    j = TblGet_08025654(s, (u8)b);
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
            if (Sub_0802583C(s, GetRomTableU16_080266F0(x), GetRomTableU16_080266F0(y)) != 0)
                return 2;
            {
                unsigned int w = GetU16_10_080257F8(s);
                if ((u16)w < (u16)GetRomTableU16_080266F0(x))
                    return 3;
            }
        }
    } else {
        if (b <= 9) {
            if (Sub_0802583C(s, GetRomTableU16_080266F0(y), GetRomTableU16_080266F0(x)) != 0)
                return 2;
            {
                unsigned int w = GetU16_10_080257F8(s);
                if ((u16)w < (u16)GetRomTableU16_080266F0(y))
                    return 3;
            }
        }
    }
    if (i != 255)
        SetU8_Off1_080256DC(4 * i + 20 + s, (u8)b);
    if (j != 255)
        SetU8_Off1_080256DC(4 * j + 20 + s, (u8)a);
    StoreIdx2_08025638(s, (u8)a, j);
    StoreIdx2_08025638(s, (u8)b, i);
    return 0;
}

__asm__(
".globl TblGet_08025654\n"
".set TblGet_08025654, 0x08025654\n"
".globl GetRomTableU16_080266F0\n"
".set GetRomTableU16_080266F0, 0x080266F0\n"
".globl Sub_0802583C\n"
".set Sub_0802583C, 0x0802583C\n"
".globl GetU16_10_080257F8\n"
".set GetU16_10_080257F8, 0x080257F8\n"
".globl SetU8_Off1_080256DC\n"
".set SetU8_Off1_080256DC, 0x080256DC\n"
".globl StoreIdx2_08025638\n"
".set StoreIdx2_08025638, 0x08025638\n"
);
