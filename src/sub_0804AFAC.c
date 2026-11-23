typedef signed int s32;

extern u8 gUnknown_0200BD20[];
extern u8 gUnknown_02002EE0[];
extern int sub_0804AD7C(void);

s8 sub_0804ACAC(void)
{
    u8 *p = gUnknown_0200BD20;
    u32 v = 0x12C;
    s8 r;
    *(u16 *)(p + 0xA2) = v;
    r = sub_0804AD7C();
    if (r == 0) {
        return (s8)p[0xA1];
    }
    return r;
}

s32 sub_0804AD4C(void)
{
    s32 ret;
    u8 *bd = gUnknown_0200BD20;
    u8 *flg = gUnknown_02002EE0;

    if ((*flg & 0x30) == 0x30) {
        *(u32 *)(bd + 0x78) = 0;
        ret = 0;
    } else {
        *(u32 *)(bd + 0x78) = *(u32 *)(bd + 0x78) + 1;
        if (*(u32 *)(bd + 0x78) > 0x3B)
            ret = -1;
        else
            ret = 0;
    }
    return ret;
}

extern s8 sub_08028778(u8 *p, u32 x);

s32 sub_0804AFAC(u8 *p)
{
    s32 r = (s8)sub_08028778(p + 1, 1);
    if (r == 0) {
        p[0] = p[0] + 1;
        p[1] = r;
    }
    return 0;
}
