/* identical to sub_0804AC64 (matched), with its names changed by decompdecomp */
typedef signed int s32;

extern u8 gUnknown_0200BD20[];
extern u8 gUnknown_02002EE0[];
extern int sub_0804AD7C(void);

s8 sub_0804AD00(void)
{
    u8 *p = gUnknown_0200BD20;
    s8 r = sub_0804AD7C();
    if (r == 0) {
        return (s8)p[0xA1];
    }
    return r;
}

s8 sub_0804ACAC(void)
{
    u8 *p = gUnknown_0200BD20;
    s8 r;
    *(u16 *)(p + 0xA2) = 0x12C;
    r = sub_0804AD7C();
    if (r == 0) {
        return (s8)p[0xA1];
    }
    return r;
}

s32 sub_0804AD4C(void)
{
    u8 *bd = gUnknown_0200BD20;
    u8 *flg = gUnknown_02002EE0;
    u32 *ctr = (u32 *)(bd + 0x78);

    if ((*flg & 0x30) == 0x30) {
        *ctr = 0;
        return 0;
    }
    *ctr = *ctr + 1;
    if (*ctr > 0x3B) {
        return -1;
    }
    return 0;
}

extern int sub_08028778(u8 *p, u32 x);

s32 sub_0804AFAC(u8 *p)
{
    s8 r = sub_08028778(p + 1, 1);
    if (r == 0) {
        p[0] = p[0] + 1;
        p[1] = r;
    }
    return 0;
}
