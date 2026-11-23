typedef signed short s16;
extern u16 sub_080266F0(u8 idx);

u8 sub_080258D8(u8 *p, u16 idx)
{
    u32 off = ((u32)idx << 16) >> 14;
    u8 *q;
    off += 20;
    q = p + off;
    if (q[0] == 0)
        return 0;
    if (q[1] == 255)
        return 1;
    return 2;
}

u8 sub_080258C0(u8 *s, u16 idx)
{
    if (idx > 29)
        return 0;
    return *(s + idx * 4 + 20);
}

u8 sub_08025904(u8 *arg0)
{
    u8 count = 0;
    s16 i = 0;
    do {
        if (arg0[i * 4 + 0x15] != 0xFF)
            count++;
        i++;
    } while ((s16)i <= 29);
    arg0[0x8D] = count;
    return count;
}

u16 sub_080258A4(u8 *s, u8 idx)
{
    return sub_080266F0(idx) + *(u16 *)(s + 14);
}
