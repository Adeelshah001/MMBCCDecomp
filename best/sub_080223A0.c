extern u32 gUnknown_08226EF0[];
extern void sub_0800D728(u32 a, u16 b, u8 c);
extern void sub_0800D9EC(u8 *s, u8 idx);
extern void sub_0800D9FC(u8 *s);
extern int sub_08026D94(u8 *s);

void sub_080226B0(u8 *p)
{
    register u32 z = 0;
    u8 b;
    *(u32 *)(p + 0x6c) = z;
    b = 2;
    b |= p[10];
    b |= 1;
    p[10] = b;
    sub_0800D728((u32)p, 0x2e12, 0);
    sub_0800D9EC(p, p[17]);
    *(u32 *)(p + 0x50) = 0xf0 << 7;
    *(u32 *)(p + 0x54) = 0xa0 << 7;
    p[0x45] &= -13;
    p[0x22] = (u8)z;
}

u32 sub_080225B4(u16 arg0, u8 arg1)
{
    u32 *tbl = (u32 *)0x08173760;
    u32 hi = arg0 >> 8;
    u32 lo = (arg0 & 0xFF) << 2;
    u8 *p = (u8 *)(tbl[hi] + lo);
    u8 *q = p + *(u32 *)p;
    u8 *r = q + 0x0C;
    return (u32)r + *(u32 *)r + (arg1 << 5);
}

void sub_080223A0(u8 *p)
{
    u8 *q = *(u8 **)(p + 0x28);
    u8 r;
    *(u32 *)(p + 0x50) = *(u32 *)(q + 0x50);
    *(u32 *)(p + 0x54) = *(u32 *)(q + 0x54);
    r = q[0x12];
    if (r != 0xFF) {
        if (p[0x12] != r) {
            p[0x12] = r;
            sub_0800D9EC(p, p[0x12]);
            p[0x0A] = 1 | p[0x0A];
        }
    } else {
        p[0x0A] = 0xFE & p[0x0A];
    }
    sub_0800D9FC(p);
}

void sub_08022E88(u8 *s)
{
    s8 r = sub_08026D94(s);
    if (r != 3) {
        u32 *e = &gUnknown_08226EF0[s[9]];
        *(u32 *)(s + 12) = 2;
        {
            u32 v = *e;
            *(u32 *)(s + 20) = *(u32 *)(v + 8);
        }
    } else {
        sub_0800D9FC(s);
    }
}
