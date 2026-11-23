extern u8 gUnknown_02007090[];
extern u8 gUnknown_020070A4[];
extern u16 sub_08025754(u8 *tbl);

u16 sub_08024EB8(void)
{
    u32 *pp = (u32 *)0x02007090;
    u8 *base = (u8 *)pp[5];
    u8 *addr = base + 0x1B0;
    u8 idx = *addr;
    u32 sc = idx * 9;
    return (u16)sub_08025754(base + (sc << 4));
}

extern u32 sub_08023E30(u8 *p);
extern void EncodeMappedSlots(u8 *t, u32 v, u32 arg);

void sub_08024F88(u32 arg0)
{
    u8 *p = gUnknown_020070A4;
    u8 *base = *(u8 **)p;
    u8 *addr = base + 0x1B0;
    u8 idx = *addr;
    u32 sc = idx * 9;
    EncodeMappedSlots(base + (sc << 4), sub_08023E30(p - 0x14), arg0);
}

extern u16 sub_08026238(u8 *s, u32 a, u32 b);

u16 sub_08024FBC(u32 a, u32 b)
{
    u8 *base = gUnknown_02007090;
    return sub_08026238(base + 0x18, a, b);
}

extern void sub_0802666C(u8 *p);

void sub_0802508C(u16 arg0)
{
    u8 *base = gUnknown_02007090;
    if (arg0 != 0) {
        sub_0802666C(base + 0x18);
    }
}
