typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

extern u32 ChkFlag_080247E8(u8 a);
extern u8 TblGet_f0A(u8 idx);
extern u32 F_080247C4(u8 idx);

__attribute__((section(".text.w23d_080378b8")))
u8 F_080378B8(u8 *p, u8 v)
{
    u8 r = 0;
    if ((u16)ChkFlag_080247E8(v) == 0)
        r = 3;
    else if ((u8)TblGet_f0A(v) > 3)
        r = 2;
    else if ((u16)F_080247C4(v) == 1)
        r = 1;
    else if (v == *(p + 0x469E))
        r = 4;
    *(p + 0x469E) = v;
    return r;
}
