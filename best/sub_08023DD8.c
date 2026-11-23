struct Rom082298F0 {
    u8 pad[14];
    u8 fieldE;
    u8 fieldF;
    u8 tail[4];
};

extern const struct Rom082298F0 D_082298F0[];

u8 sub_080244B0(u16 id, u8 flags)
{
    const volatile struct Rom082298F0 *base;
    u32 index = id;
    u32 kind = index >> 12;
    if (kind != 3)
        return 0;
    base = (const volatile struct Rom082298F0 *)0x082298F0;
    if (1 & flags)
        goto odd;
    return base[index & 0xfff].fieldE;
odd:
    return base[index & 0xfff].fieldF;
}

void sub_08023DD8(u8 *bytes, u16 *digits)
{
    s8 out = 14;
    do {
        u16 carry = 0;
        s8 in = 23;
again:
        {
            u16 *digit;
            u16 value;
            carry *= 36;
            digit = (u16 *)(in * 2 + (u32)digits);
            value = *(volatile u16 *)digit;
            carry = value + carry;
            if (carry > 255) {
                *digit = carry >> 8;
                carry &= 255;
            } else {
                *digit = 0;
            }
            --in;
        }
        if (in >= 0)
            goto again;
        bytes[out] = carry;
        --out;
    } while (out >= 0);
}

