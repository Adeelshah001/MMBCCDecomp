extern u32 *gUnknown_082243D8[];
extern u32 gUnknown_08226A04[];

void sub_0804DCD0(u8 *s, u32 fn);
void sub_0801D3A8(u8 *s);
u32 *CreateBattleObject(u8 a, u8 b, u8 c, u8 d);

void sub_0801D36C(u8 *s)
{
    *(u32 *)(s + 12) = 1;
    *(u32 *)(s + 20) = gUnknown_082243D8[s[9]][1];
    sub_0804DCD0(s, gUnknown_08226A04[s[16]]);
    sub_0801D3A8(s);
}

void *sub_0801D308(void *s, void *t, u8 arg2)
{
    void *n;
    u8 *q;
    u32 *sp;
    u32 *tp;

    n = CreateBattleObject(0, 1, 0, 0xC);
    if (n != 0)
    {
        q = (u8 *)n;
        q[0x10] = 7;
        q[0x11] = arg2;
        sp = (u32 *)s;
        tp = (u32 *)t;
        *(u32 *)(q + 0x58) = sp[0x50 / 4];
        *(u32 *)(q + 0x5C) = sp[0x54 / 4];
        *(u32 *)(q + 0x58) += tp[0];
        *(u32 *)(q + 0x5C) += tp[1];
    }
    return n;
}

u32 *sub_0801D2C8(u8 a, u32 b, u32 c, u32 *d)
{
    u32 type;
    u32 *n;
    u8 *q;

    type = 6;
    if (a == 0)
        type = 5;
    n = CreateBattleObject(0, 1, 0, 12);
    if (n != 0)
    {
        q = (u8 *)n;
        q[0x10] = type;
        q[0x11] = 0;
        *(u32 *)(q + 0x60) = d[0];
        *(u32 *)(q + 0x64) = d[1];
        *(u32 *)(q + 0x28) = c;
        *(u32 *)(q + 0x2C) = b;
    }
    return n;
}

u8 *sub_0801D278(u8 *a, u8 *b, u8 *c)
{
    u8 *n;
    int t;
    u16 v;

    n = (u8 *)CreateBattleObject(0, 0, a[35] & 0xF, 0xC);
    if (n != 0)
    {
        n[0x10] = 4;
        n[0x11] = 0;
        *(u32 *)(n + 0x60) = *(u32 *)c;
        *(u32 *)(n + 0x64) = *((u32 *)c + 1);
        t = (a[34] - 1) << 16;
        v = (u32)t >> 16;
        if (t < 0)
            v = 0;
        n[0x12] = v;
        *(u32 *)(n + 0x28) = (u32)a;
        *(u32 *)(n + 0x2C) = (u32)b;
    }
    return n;
}
