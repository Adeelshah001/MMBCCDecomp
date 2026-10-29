/* Wave 18-B: 0x08024EB8 (34 B, 1 caller, 1 bl -> SumStrides_25754). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

extern u16 SumStrides_25754(u8 *tbl);

__attribute__((section(".text.w18b_08024eb8")))
u16 sub_08024EB8(void)
{
    u32 *pp = (u32 *)0x02007090;
    u8 *base = (u8 *)pp[5];
    u32 off = 216;
    u8 idx;
    u32 sc;

    off <<= 1;
    idx = base[off];
    sc = idx;
    sc = (sc << 3) + sc;
    sc <<= 4;
    return (u16)SumStrides_25754(base + sc);
}
