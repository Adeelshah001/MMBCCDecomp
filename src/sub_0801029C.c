extern void sub_08010508(u32 v);

struct Unk02005160 {
    u8 unk0;
    u8 pad1[0x2F];
    u32 unk30;
    u32 unk34;
    u16 unk38;
    u8 pad3A[7];
    u8 unk41;
    u8 unk42;
    u8 unk43;
    u8 unk44;
    u8 unk45;
};

extern struct Unk02005160 D_02005160;

u32 sub_08010088(void)
{
    if ((*(volatile u8 *)0x02005160) == 0)
        return 1;
    return 0;
}

u32 sub_0801029C(u32 arg0, u8 arg1, u16 arg2, u8 arg3)
{
    u8 temp = D_02005160.unk0;
    if (temp != 0)
        return 0;
    sub_08010508(4);
    D_02005160.unk42 = temp;
    D_02005160.unk45 = arg1;
    D_02005160.unk38 = arg2;
    D_02005160.unk30 = arg0;
    D_02005160.unk41 = arg3;
    return 1;
}

u32 sub_08010308(u32 a, u32 b, u16 c, u8 d)
{
    u8 z = D_02005160.unk0;
    if (z != 0)
        return 0;
    sub_08010508(5);
    D_02005160.unk42 = z;
    D_02005160.unk30 = a;
    D_02005160.unk34 = b;
    D_02005160.unk43 = 0xFF;
    D_02005160.unk41 = d;
    D_02005160.unk38 = c;
    return 1;
}

u32 sub_08010374(u8 *arg0)
{
    if (D_02005160.unk0 == 0) {
        *arg0 = D_02005160.unk43;
        return 1;
    }
    *arg0 = -1;
    return 0;
}
