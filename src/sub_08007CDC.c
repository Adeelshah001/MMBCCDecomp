extern unsigned char gUnknown_02004E18[];

void sub_08007CDC(unsigned short v)
{
    unsigned char *p = gUnknown_02004E18 + v * 8;
    unsigned char val = 4;
    val |= p[7];
    p[7] = val;
}
