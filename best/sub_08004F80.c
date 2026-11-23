extern u8 D_02003670[];
extern u32 D_020066F0;

extern void sub_0800D568(u32 v);
extern void sub_0800D59C(u32 v);
extern void sub_080050E0(u8 *base);
extern void sub_08004FEC(u8 *base);
extern void sub_0800419C(u8 *p);

void sub_08004F80(void)
{
    u8 *base = D_02003670;
    u32 *hp = &D_020066F0;
    u8 *p;
    int val;
    u32 tmp;

    sub_0800D568(*hp);
    sub_0800D59C(*hp);
    p = base + 0x11AE;
    val = 2;
    tmp = *p;
    val |= tmp;
    *p = val;
    if ((val & 0xF8) != 8)
        sub_08004FEC(base);
    else
        sub_080050E0(base);
    sub_0800419C(base + 0x49C);
    sub_0800419C(base + 0x2C);
    tmp = 0x264;
    sub_0800419C(base + tmp);
    *(u32 *)base += 1;
}
