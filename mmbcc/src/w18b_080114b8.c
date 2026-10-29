/* Wave 18-B: 0x080114B8 (48 B, 5 callers, 1 bl -> TableWalk_080113F4).
   Initializes the table at 0x02005230 then walks; returns 1 if not found, 0 if found. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

extern u8 *TableWalk_080113F4(u16 cur);

__attribute__((section(".text.w18b_080114b8")))
u32 TblWalkInit_080114B8(u16 x)
{
    u8 *t = (u8 *)0x02005230;
    u8 *r;
    u32 z = 0;

    t[4] = z;
    t[5] = z;
    t[6] = z;
    t[7] = z;
    *(u32 *)(t + 8) = z;
    r = TableWalk_080113F4(x);
    *(u8 **)t = r;
    if (r == 0)
        return 1;
    return 0;
}
