typedef signed int s32;

extern u8 gUnknown_0200BD20[];
extern u8 gUnknown_02002EE0[];
extern int sub_0804AD7C(void);

s8 sub_0804ACAC(void)
{
    u8 *p = gUnknown_0200BD20;
    u16 *q = (u16 *)(p + 0xA2);
    u32 v = 0x12C;
    s8 r;
    *q = v;
    r = sub_0804AD7C();
    if (r == 0) {
        return (s8)p[0xA1];
    }
    return r;
}

s32 sub_0804AD4C(void)
{
    u8 *bd = gUnknown_0200BD20;

    if ((gUnknown_02002EE0[0] & 0x30) == 0x30) {
        *(s32 *)(bd + 0x78) = 0;
        return 0;
    }
    *(s32 *)(bd + 0x78) = *(s32 *)(bd + 0x78) + 1;
    if (*(s32 *)(bd + 0x78) <= 0x3B)
        return 0;
    return -1;
}
