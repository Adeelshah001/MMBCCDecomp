/* Wave 18-B: 0x080257BC (60 B, 1 caller, 3 bl). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

extern u8 TblLookup_25730(u8 *tbl, u8 idx);
extern u16 SumStrides_25754(u8 *tbl);
extern u16 GetRomTableU16(u8 idx);

__attribute__((section(".text.w18b_080257bc")))
void sub_080257BC(u8 *p, u16 x)
{
    u8 v = TblLookup_25730(p, 0);
    u16 sum;
    u16 t;

    if (v == 0)
        v = p[1];
    sum = SumStrides_25754(p);
    if ((int)sum <= (int)GetRomTableU16(v) + (int)x)
        *(u16 *)(p + 14) = x;
}
