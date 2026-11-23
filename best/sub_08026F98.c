extern u32 gUnknown_0822DC84[];
extern void sub_08027F80(u8 *p);
extern u16 D_020031E0[];
extern u8 D_02003670[];
extern u8 D_020070F0[];

void sub_08027718(u8 *s)
{
    u32 *tbl = gUnknown_0822DC84;
    u32 *e = tbl + s[1];
    ((void (*)(u8 *))(*e))(s);
}

void sub_08027E5C(u8 *p)
{
    p[5] |= 0xFF;
    p[6] = 0;
    p[4] = 0;
    p[3] &= ~6;
    p[3] &= 0x0F;
    p[3] &= ~8;
    p[7] |= 0xFF;
    sub_08027F80(p);
}

void sub_08026F98(u8 x)
{
    u16 *p = D_020031E0;
    u32 v = 0x90 << 5;
    u32 a;
    u32 t;

    v = v | *p;
    *p = v;
    a = (u32)D_02003670;
    t = (x | -x) >> 31;
    t &= 0x20;
    a += 0x11AC;
    *(u8 *)a = (u8)t;
}

int sub_08026D94(void)
{
    u8 *p = D_020070F0;
    int r;
    if (p[1] != 0)
        r = ((s8 *)p)[2];
    else
        r = -1;
    return r;
}
