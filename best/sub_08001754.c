extern u16 D_0816E240[];

u16 sub_08001754(u32 arg0, u32 arg1) {
    u32 tmp;
    u32 shifted;
    u16 r5;
    u16 mask;
    u16 a;
    u16 b;
    u16 c;
    u16 sum;

    tmp = arg0;
    tmp <<= 20;
    tmp >>= 20;
    tmp |= (arg1 & 3) << 12;
    shifted = tmp << 16;
    r5 = (u16)(shifted >> 16);
    mask = 0x1F;
    a = D_0816E240[r5 & mask];
    b = D_0816E240[(shifted >> 0x15) & mask];
    c = D_0816E240[shifted >> 0x1A];
    sum = (u16)(a + b + c);
    return (u16)((u32)(sum & 3) << 14 | r5);
}
