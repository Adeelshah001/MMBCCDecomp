/* Wave 16 worker B: 0x08025754 (60 B).
 * Sums GetRomTableU16(v) for non-zero TblLookup_25730(tbl,i), i=1..9.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;


extern u16 GetRomTableU16(u8 idx);
extern u8 TblLookup_25730(u8 *tbl, u8 idx);
u8 TblLookup_25730(u8 *tbl, u8 idx);
u16 GetRomTableU16(u8 idx);

u16 SumStrides_25754(u8 *tbl) __attribute__((section(".text.w16b_08025754")));
u16 SumStrides_25754(u8 *tbl)
{
    u8 *tt = tbl;
    u16 sum = 0;
    u16 i = 1;
    u32 t;
    do {
        u8 v = TblLookup_25730(tt, (u8)i);
        if (v != 0)
            sum += GetRomTableU16(v);
        t = ((u32)i << 16) + 0x10000; i = t >> 16;
    } while ((s16)i <= 9);
    return sum;
}

