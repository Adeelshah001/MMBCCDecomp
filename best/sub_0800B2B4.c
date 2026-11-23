extern unsigned short gUnknown_02004E40[];
extern unsigned char gUnknown_02004E40_b[];

void sub_0800B29C(unsigned short v)
{
    if (gUnknown_02004E40[7] != 0)
        gUnknown_02004E40[7] = v | gUnknown_02004E40[7];
}

int sub_0800B2B4(void)
{
    unsigned char v = gUnknown_02004E40_b[4];
    if ((v & 0x0F) != 0)
        return 0;
    if ((v & 0x80) != 0)
        gUnknown_02004E40_b[5] = 2;
    return 1;
}

int sub_0800B2D8(void)
{
    unsigned char v = gUnknown_02004E40_b[4];
    if ((v & 0x8F) == 0x80)
        return 1;
    return 0;
}

int sub_0800B2F0(void)
{
    unsigned char v = gUnknown_02004E40_b[4];
    if ((v & 0x8F) == 0)
        return 1;
    return 0;
}
