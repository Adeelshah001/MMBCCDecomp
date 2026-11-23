extern u8 gUnknown_02005260[];

void sub_08011D68(u16 arg0, u8 arg1)
{
    u32 arg0_shifted;
    u16 xr;
    u8 yr;
    u32 *ptr;
    u32 base;
    u8 *p;
    u8 bit;
    u8 mask;
    u8 val;
    arg0_shifted = (u32)arg0 << 16;
    xr = arg0_shifted >> 16;
    yr = (u32)arg1 << 24 >> 24;
    if (xr == 0)
        return;
    if (xr > 0x7F)
        return;
    ptr = (u32 *)gUnknown_02005260;
    p = (u8 *)(ptr[1] + (arg0_shifted >> 19));
    bit = xr & 7;
    mask = (u8)~(1 << bit);
    val = (u8)((yr & 1) << bit);
    *p = (*p & mask) | val;
}
