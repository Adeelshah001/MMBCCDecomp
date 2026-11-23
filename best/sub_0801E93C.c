extern u32 gUnknown_082243D8[];
extern u32 gUnknown_08226A04[];

void sub_0804DCD0(u8 *s, u32 fn);
void sub_0801D3A8(u8 *s);
void sub_0800D9FC(u8 *s);
u32 sub_08010F88(u8 x);

void sub_0801D36C(u8 *s)
{
    u32 *t1;
    u32 *p;
    u32 e;

    t1 = gUnknown_082243D8;
    p = t1 + s[9];
    *(u32 *)(s + 12) = 1;
    e = *p;
    *(u32 *)(s + 20) = *(u32 *)(e + 4);
    sub_0804DCD0(s, gUnknown_08226A04[s[16]]);
    sub_0801D3A8(s);
}

void sub_0801D89C(u8 *s)
{
    u32 *t1;
    u32 *p;
    u8 *q;
    u8 *p2;
    u8 v;

    v = (u8)(s[0x77] - 3);
    if (v <= 1)
    {
        q = *(u8 **)(s + 0x28);
        if (q[12] <= 1)
        {
            p2 = *(u8 **)(s + 0x2C);
            p2[0]++;
        }
        t1 = gUnknown_082243D8;
        p = t1 + s[9];
        *(u32 *)(s + 12) = 2;
        *(u32 *)(s + 20) = *(u32 *)((u8 *)*p + 8);
    }
    sub_0800D9FC(s);
}

void sub_0801E14C(u8 *s)
{
    u32 *t1;
    u32 *p;

    sub_08010F88(s[16]);
    t1 = gUnknown_082243D8;
    p = t1 + s[9];
    *(u32 *)(s + 12) = 4;
    *(u32 *)(s + 20) = *(u32 *)((u8 *)*p + 0x10);
}

void sub_0801E93C(u8 *s)
{
    u8 v;
    u32 *t1;
    u32 *entry;

    sub_0800D9FC(s);
    v = (u8)(s[0x77] - 3);
    if (v <= 1)
    {
        t1 = gUnknown_082243D8;
        entry = t1 + s[9];
        *(u32 *)(s + 12) = 2;
        *(u32 *)(s + 20) = *(u32 *)((u8 *)*entry + 8);
    }
}
