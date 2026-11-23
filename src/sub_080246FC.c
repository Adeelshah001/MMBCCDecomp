struct ChipRecord {
    u8 reserved[14];
    u8 field0E;
    u8 field0F;
};

extern const struct ChipRecord D_0822740C[];
extern const u32 D_0822BB8C[];
extern u8 D_02007090[];
extern u8 sub_08025564(u8 *, u8);

u32 sub_080246A8(int rawIndex)
{
    u32 index = (u16)rawIndex;
    u32 result;

    if (index <= 248)
        result = D_0822BB8C[index];
    else
        result = 0;
    return result;
}

u8 sub_0802468C(int rawIndex)
{
    u32 index = (u16)rawIndex;
    u8 result;

    if (index <= 248)
        result = D_0822740C[index].field0F;
    else
        result = 0;
    return result;
}

u8 sub_08024670(int rawIndex)
{
    u32 index = (u16)rawIndex;
    u8 result;

    if (index <= 248)
        result = D_0822740C[index].field0E;
    else
        result = 0;
    return result;
}

u8 sub_080246FC(int rawIndex)
{
    u32 index = (u16)rawIndex;
    u8 *state = D_02007090;
    u8 result;

    if (index <= 248)
        result = sub_08025564(state, (u8)index);
    else
        result = 0;
    return result;
}
