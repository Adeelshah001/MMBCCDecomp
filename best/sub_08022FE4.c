extern void sub_0800D728(u32 a, u16 b, u8 c);
extern void sub_0800D9EC(u8 *s, u8 idx);
void sub_080226B0(u8 *p)
{
    u32 zero = 0;
    u8 b;
    *(u32 *)(p + 0x6c) = zero;
    b = 2;
    b |= p[10];
    b |= 1;
    p[10] = b;
    sub_0800D728((u32)p, 0x2e12, 0);
    sub_0800D9EC(p, p[17]);
    *(u32 *)(p + 0x50) = 0xf0 << 7;
    *(u32 *)(p + 0x54) = 0xa0 << 7;
    {
        struct FlagByte { u8 value; };
        struct FlagByte *q = (struct FlagByte *)p;
        int mask = ~0xC;
        q[0x45].value &= mask;
    }
    p[0x22] = zero;
}

extern int sub_08026D94(void);
extern void sub_0800D9FC(u8 *s);
extern const u32 *const D_08226EF0[];
void sub_08022F48(u8 *s)
{
    if ((--s[18] << 24) == 0)
        goto update;
    if ((s8)sub_08026D94() <= 2)
        goto finish;
update:
    {
        const u32 *const *tbl = D_08226EF0;
        register u8 idx = s[9];
        register u32 off;
        const u32 *const *ent = &tbl[idx];
        *(u32 *)(s + 12) = 2;
        *(u32 *)(s + 20) = (*ent)[2];
    }
finish:
    sub_0800D9FC(s);
}

u32 sub_08021D84(u8 *s)
{
    u32 mask = 0x3f;
    mask &= s[19];
    if (mask == 0x3f)
        return 1;
    return 0;
}

extern u32 *sub_08020ED4(u8 a, u8 b, u8 c, u8 d);
u8 *sub_08022FE4(u8 *p)
{
    u8 *q;
    int bit = 1;
    bit &= p[7];
    if (bit)
        return 0;
    q = (u8 *)sub_08020ED4(0, 0, 0, 6);
    if (q != 0) {
        q[0x10] = 2;
        q[0x11] = p[0];
        *(u8 **)(q + 0x28) = p;
    }
    {
        u32 flags = 1;
        flags |= p[7];
        p[7] = flags;
    }
    return q;
}
