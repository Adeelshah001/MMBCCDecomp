typedef signed short s16;

s8 sub_0800ED44(u8 a, u8 b)
{
    u8 *p = (u8 *)0x02005130;
    u32 w;
    s16 x;
    s8 res;

    if (a == 0) {
        w = *(u32 *)0x02005020;
        p[0x2B] = 0;
    } else {
        w = *(u32 *)(0x02005020 + 4);
        p[0x2B] = 1;
    }

    x = *(s16 *)(0x08223F9C + p[6] * 4 + 2);
    res = sub_080103E0(b, w, 0, x);

    if (res == 1) {
        sub_0800E1F0(16);
        return 1;
    }
    return res;
}
