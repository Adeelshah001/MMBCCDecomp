extern u8 gUnknown_02005260[];

u8 sub_08011DB0(u16 idx)
{
    u16 xr = (u32)idx << 16 >> 16;
    u16 a = xr;
    if (xr > 7)
        return 0;
    if (xr != 0) {
        u32 *ptr = (u32 *)gUnknown_02005260;
        u32 base = ptr[2];
        return *(u8 *)(base + a);
    }
    return 0;
}
