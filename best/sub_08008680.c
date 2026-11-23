void sub_08008BB8(u16 *dest, u16 value, u8 mode)
{
    if ((u8)(mode) == 0)
        *dest = (u16)value;
}
extern u8 D_02003670[];
extern const u8 D_000011AE[];
int sub_08008680(u8 *p)
{
    s8 result;
    u8 *base;
    u32 flag;
    volatile u8 *address;
    if (p[11])
        goto fallback;
    base = D_02003670;
    address = base + (u32)D_000011AE;
    flag = 1;
    flag &= *address;
    result = 32;
    if (flag)
        goto done;
    result = 22;
    goto done;
fallback:
    result = 8;
done:
    return result;
}

int sub_08008654(u8 *p)
{
    s8 result;
    u8 *base;
    u32 flag;
    volatile u8 *address;
    if (p[11])
        goto fallback;
    base = D_02003670;
    address = base + (u32)D_000011AE;
    flag = 1;
    flag &= *address;
    result = 5;
    if (flag)
        goto done;
    result = 6;
    goto done;
fallback:
    result = 5;
done:
    return result;
}

int sub_08008628(u8 *p)
{
    s8 result;
    u8 *base;
    u32 flag;
    volatile u8 *address;
    if (p[11])
        goto fallback;
    base = D_02003670;
    address = base + (u32)D_000011AE;
    flag = 1;
    flag &= *address;
    result = 32;
    if (flag)
        goto done;
    result = 64;
    goto done;
fallback:
    result = 32;
done:
    return result;
}
