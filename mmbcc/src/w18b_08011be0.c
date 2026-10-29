/* Wave 18-B: 0x08011BE0 (28 B, 0 callers, 1 bl -> TableWalk_080113F4).
   Returns the input if TableWalk finds it, 0 if not. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

extern u8 *TableWalk_080113F4(u16 cur);

__attribute__((section(".text.w18b_08011be0")))
u16 TblWalkRet_08011BE0(u16 x)
{
    u8 *r = TableWalk_080113F4(x);
    if (r == 0)
        return 0;
    return x;
}
