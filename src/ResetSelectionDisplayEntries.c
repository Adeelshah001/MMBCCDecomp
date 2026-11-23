extern u8 D_02004E40[];
extern void sub_0800B520(u32 *b, u32 c, u32 d);
extern void ResetSelectionDisplayEntries(void);
extern void sub_0800B4C8(void);

u32 sub_0800B308(void)
{
    u8 *base = (u8 *)0x02004e40;
    int mask = 15;
    int result;
    if ((mask &= base[4]) == 0)
        result = 1;
    else
        result = 0;
    return result;
}

int StartSelectionWithEntries(u32 *a, u32 *b, u32 c, u32 d)
{
    u8 *base = (u8 *)0x02004e40;
    u8 flag = base[4];
    unsigned int g;
    if ((flag & 15) != 0)
        return 0;
    g = 128;
    g &= flag;
    if (g == 0) {
        base[5] = 1;
        return 0;
    }
    *(u32 *)(base + 32) = (u32)a;
    sub_0800B520(b, c, d);
    base[5] = 3;
    ResetSelectionDisplayEntries();
    sub_0800B4C8();
    return 1;
}

u8 sub_0800B368(u32 a, u32 *b, u32 c, u32 d)
{
    u8 *base = (u8 *)0x02004e40;
    int mask = 128;
    u8 flag = base[4];
    if ((mask &= flag) == 0) {
        base[5] = 1;
        return 0;
    }
    base[0] = 0;
    base[3] = 0;
    base[2] = 0;
    base[1] = 0;
    base[5] = 3;
    *(u32 *)(base + 32) = a;
    sub_0800B520(b, c, d);
    ResetSelectionDisplayEntries();
    sub_0800B4C8();
    return 1;
}

void ResetSelectionDisplayEntries(void)
{
    u8 *base = (u8 *)0x02004e40;
    u16 i = 0;
    u8 *entries = base + 0x88;
    u16 marker = 0x8000;
    int flags;
    do {
        short index = i;
        u32 offset = index * 0x24;
        *(u16 *)((u32)entries + offset) = marker;
        i = index + 1;
    } while ((short)i <= 2);
    flags = 4;
    flags |= base[0x14];
    base[0x14] = flags;
}
