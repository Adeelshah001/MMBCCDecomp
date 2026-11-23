struct Rom0822740C {
    u16 f00;
    u16 f02;
    u16 f04;
    u8 pad06[2];
    u16 f08;
    u8 f0A;
    u8 pad0B[5];
};
extern const struct Rom0822740C D_0822740C[];

u8 sub_080245C4(u8 index)
{
    u32 i = index;
    const struct Rom0822740C *base;
    return i > 248 ? 0 : D_0822740C[i].f0A;
}

struct Rom082298F0 {
    u8 pad[14];
    u8 fieldE;
    u8 fieldF;
    u8 tail[4];
};

extern const struct Rom082298F0 D_082298F0[];

u8 sub_080244B0(u16 id, u8 flags)
{
    const volatile struct Rom082298F0 *base = (const volatile struct Rom082298F0 *)0x082298F0;
    u32 index = id;
    u32 kind = index >> 12;
    if (kind != 3)
        return 0;
    if ((1 & flags) == 0)
        goto even;
    return base[index & 0xfff].fieldF;
even:
    return base[index & 0xfff].fieldE;
}

void sub_08023DD8(u8 *bytes, u16 *digits)
{
    s8 out = 14;
    do {
        u16 carry = 0;
        s8 in = 23;
again:
        {
            u16 scaled = carry * 36;
            u16 *digit = (u16 *)(in * 2 + (u32)digits);
            u16 value = *digit;
            carry = value + scaled;
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

