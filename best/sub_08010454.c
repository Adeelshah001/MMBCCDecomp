int sub_08010478(u8 x)
{
    u8 *p = (u8 *)0x02005168;
    u32 mask;
    if (x == 1)
        p += 20;
    mask = 2;
    mask = -mask;
    mask &= p[16];
    p[16] = mask;
    return 1;
}

u32 sub_08010498(u8 a)
{
    u8 *p = (u8 *)0x02005168;
    u8 v;
    if (a == 1)
        p += 20;
    v = p[16];
    if ((v & 2) != 0) {
        if ((v & 1) != 0) {
            u32 t = 2;
            t = -t;
            t &= v;
            p[16] = (u8)t;
        }
        return 0;
    } else {
        return 1;
    }
}

int sub_08010454(u8 x)
{
    u8 *p = (u8 *)0x02005168;
    if (x == 1)
        p += 20;
    {
        u32 mask = 2;
        mask &= p[16];
        if (mask == 0)
            return 0;
        return 1;
    }
}

void sub_0801052C(void)
{
    u8 *p = (u8 *)0x02004CA0;
    if (p[28] == 0)
        goto second;
    p[28] = 0;
second:
    p += 32;
    if (p[28] == 0)
        return;
    p[28] = 0;
}
