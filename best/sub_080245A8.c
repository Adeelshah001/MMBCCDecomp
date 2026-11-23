struct ChipTableEntry {
    u16 f00;
    u16 f02;
    u16 f04;
    u8 _06[2];
    u16 f08;
    u8 f0A;
    u8 _0B;
    u8 f0C;
    u8 f0D;
    u8 f0E;
    u8 f0F;
};

extern struct ChipTableEntry gUnknown_0822740C[];

u16 sub_08024554(u8 idx)
{
    if (idx > 0xF8)
        return 0;
    return gUnknown_0822740C[idx].f00;
}

u16 sub_08024570(u8 idx)
{
    if (idx > 0xF8)
        return 0;
    return gUnknown_0822740C[idx].f04;
}

u16 sub_0802458C(u8 idx)
{
    if (idx > 0xF8)
        return 0;
    return gUnknown_0822740C[idx].f02;
}

u32 sub_080245A8(u8 idx)
{
    if (idx > 0xF8)
        return 0;
    return gUnknown_0822740C[idx].f08 >> 0xC;
}
