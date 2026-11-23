extern u16 sub_08024554(u8 id);
extern s8 sub_08028778(u8 *phase, u8 mode);
extern u8 sub_0802FD68(u8 *state);
extern void sub_08028874(u8 *state, u8 mode);
extern const u8 D_0822DDE0[];

void sub_0802D5A8(u16 packedChange, u16 *value, u8 id)
{
    u16 maximum;
    int change = (int)((u32)packedChange << 16) >> 16;
    u16 old = *value;
    *value = old + change;
    maximum = sub_08024554(id);
    if ((signed short)*value > maximum)
        *value = maximum;
}

void *sub_0802D8F4(u8 *battle)
{
    u32 tableOffset;
    u32 slotOffset;

    u32 flags = 2;
    flags &= battle[0x18];
    if (flags != 0)
        goto firstSide;
    else
    {
        tableOffset = 0x189;
        slotOffset = battle[tableOffset] * 4;
        tableOffset -= 0x1D;
    }
    goto read;
firstSide:
    slotOffset = battle[0x188] * 4;
    tableOffset = 0x150;
read:
    return *(void **)(((u32)battle + tableOffset) + slotOffset);
}

