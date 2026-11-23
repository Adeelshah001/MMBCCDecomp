extern u16 sub_08025754(u8 *tbl);
extern u16 sub_08025B60(u8 *p, u8 a, u8 b);
extern u8 sub_08025730(u8 *tbl, u8 idx);
extern u32 sub_08025A10(u8 *s, u8 idx);

u16 sub_08024EB8(void)
{
    u8 *base = (u8 *)*(u32 *)(0x02007090 + 0x14);
    return (u16)sub_08025754(base + base[432] * 144);
}

u16 sub_08024C14(u8 *s, u8 a, u8 b)
{
    u8 *base = (u8 *)*(u32 *)(s + 0x14);
    return (u16)sub_08025B60(base + base[432] * 144, a, b);
}

void sub_0802518C(u16 *src, u16 *dst)
{
    dst[0] = src[0x9D2];
    dst[1] = src[0x9D3];
    dst[2] = src[0x9D4];
    dst[3] = src[0x9D5];
}

u16 sub_08024BC8(u8 *p, u8 v)
{
    u8 *base = (u8 *)*(u32 *)(p + 0x14);
    u8 *tbl = base + base[432] * 144;
    if (sub_08025730(tbl, v) == 0)
        return 0;
    return (u16)sub_08025A10(tbl, v);
}
