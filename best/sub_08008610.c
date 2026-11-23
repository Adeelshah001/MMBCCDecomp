extern u32 gUnknown_02003674;
u32 sub_08008610(u8 *s)
{
    u32 address;
    if (s[11] == 0)
        address = *(u32 *)0x02003674;
    else
        address = 0x02004AA0;
    return address;
}

extern void sub_0800DD74(u8 *p);
extern u8 D_02004E18[];
extern const u16 D_08171EF4[];
extern u8 D_03002420[];

void sub_08007EEC(u16 idx)
{
    u8 *p = (u8 *)0x02004e18 + idx * 8;
    u8 m = 2;
    u16 *g = (u16 *)0x08171ef4;
    p[7] |= m;
    if (idx == 0) {
        u32 offset = g[1] << 5;
        u8 *base = (u8 *)0x03002420;
        sub_0800DD74((u8 *)(offset + (u32)base));
    }
}

typedef short s16;
extern u32 gUnknown_0817212C[];
extern u8 D_02004CE0[];

void sub_08009380(void)
{
    u16 i = 0;
    s16 j = i;
    u32 *tbl = gUnknown_0817212C;
    while (j <= 5) {
        u8 *p = D_02004CE0 + j * 0x34;
        u8 *flags = p + 0x2c;
        if (1 & *(vu8 *)flags) {
            u16 v = *(volatile u16 *)(p + 0x2c);
            u32 idx = ((u32)v << 22) >> 28;
            ((void (*)(u8 *))tbl[idx])(p);
        }
        i = j + 1;
        j = i;
    }
}

void sub_0800960C(void)
{
    u16 i = 0;
    s16 slot;
    u8 *base = D_02004E18;
    do {
        u8 *entry;
        slot = (s16)i;
        entry = (u8 *)((slot * 8) + (u32)base);
        entry[0] = i;
        {
            int flags = ((volatile s8 *)entry)[1];
            ((vu8 *)entry)[1] = flags | 0xff;
        }
        *(u16 *)(entry + 2) = 0;
        i = slot + 1;
    } while ((s16)i <= 3);
}
