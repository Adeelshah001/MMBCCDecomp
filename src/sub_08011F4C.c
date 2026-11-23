extern u32 D_08223D08[];

void sub_080120F0(u8 *s)
{
    u32 *tbl = D_08223D08;
    u32 idx = s[0x10];
    ((void (*)(u8 *))tbl[idx])(s);
}

void sub_08011F68(u8 *arg0, u8 arg1)
{
    arg0[0xD] = arg1;
    arg0[0xE] = 0;
    arg0[0xF] = 0;
    arg0[0x81] = arg1;
}

u32 sub_08011F50(u8 *s)
{
    u32 v = (u8)(s[0x77] - 3);
    if (v <= 1)
        return 1;
    return 0;
}

void sub_08011F4C(void)
{
}
