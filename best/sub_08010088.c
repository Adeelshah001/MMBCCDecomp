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

#define gUnk02005160 ((struct Unk02005160 *)0x02005160)

u32 sub_08010088(void)
{
    if (gUnk02005160->unk0 == 0)
        return 1;
    return 0;
}

u32 sub_0801029C(u32 arg0, u8 arg1, u16 arg2, u8 arg3)
{
    u8 temp = gUnk02005160->unk0;
    if (temp == 0) {
        sub_08010508(4);
        gUnk02005160->unk42 = temp;
        gUnk02005160->unk45 = arg1;
        gUnk02005160->unk38 = arg2;
        gUnk02005160->unk30 = arg0;
        gUnk02005160->unk41 = arg3;
        return 1;
    }
    return 0;
}

u32 sub_08010308(u32 a, u32 b, u16 c, u8 d)
{
    register u8 *p = (u8 *)0x02005160;
    register u8 z;
    u8 *q1;
    u8 *q2;
    register u8 *q3;
    z = p[0];
    if (z != 0) {
        return 0;
    }
    sub_08010508(5);
    q1 = p + 66;
    *q1 = z;
    *(u32 *)(p + 48) = a;
    *(u32 *)(p + 52) = b;
    q2 = p + 67;
    *q2 = 0xff;
    q3 = p + 65;
    *q3 = d;
    *(u16 *)(p + 56) = c;
    return 1;
}

u32 sub_08010374(u8 *arg0)
{
    if (gUnk02005160->unk0 != 0) {
        *arg0 = -1;
        return 0;
    }
    *arg0 = gUnk02005160->unk43;
    return 1;
}
