extern void sub_0800D9FC(u32);
extern void sub_0801D308(u32, u32 *, u32);

void sub_08011F24(u32 arg0)
{
    u32 buf[2] = {0, 0};
    sub_0801D308(arg0, buf, 0);
    sub_0800D9FC(arg0);
}

u32 sub_08011F50(u8 *s)
{
    u8 v = s[0x77] - 3;
    return v <= 1;
}

void sub_08011F68(u8 *arg0, u8 arg1)
{
    u8 *p = arg0 + 0x7C;
    arg0[0xD] = arg1;
    arg0[0xE] = 0;
    arg0[0xF] = 0;
    p[5] = arg1;
}
