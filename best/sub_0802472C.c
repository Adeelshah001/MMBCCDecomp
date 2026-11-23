
struct ChipRecord24618 {
    u8 unk00[8];
    u16 field08;
    u8 unk0A[2];
    u8 field0C;
    u8 field0D;
    u8 unk0E[2];
};

extern const struct ChipRecord24618 D_0822740C[];

short sub_0802472C(u8 input)
{
    return (short)((u32)input << 24);
}

u8 sub_08024618(u8 rawIndex)
{
    register u32 index = rawIndex;
    if (index > 248)
        return 0;
    return D_0822740C[index].field0D;
}

u8 sub_080245FC(u8 rawIndex)
{
    register u32 index = rawIndex;
    if (index > 248)
        return 0;
    return D_0822740C[index].field0C;
}

u16 sub_080245E0(u8 rawIndex)
{
    register u32 index = rawIndex;
    if (index > 248)
        return 0;
    return D_0822740C[index].field08;
}
