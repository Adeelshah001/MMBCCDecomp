struct BattleAction2FC {
    u8 unk00[8];
    u16 type;
    u16 amount;
};
extern u8 sub_0803FCC4(u16 type);
extern u16 sub_080400A8(void);
extern int sub_0804DEE8(unsigned value, unsigned divisor);

void sub_0802FC4C(struct BattleAction2FC **action, u8 mode, u16 amount)
{
    if (mode != 2)
    {
        struct BattleAction2FC *active = *action;
        const unsigned type = 0x271;
        if (type == active->type)
        {
            u16 previous = active->amount;
            active->amount = previous + amount;
        }
    }
}

void sub_0802FBA4(u8 *battle, u8 side, u8 slot)
{
    int indexOffset;
    u32 slotOffset;
    void **active;
    u32 slots;

    if (side == 0)
    {
        active = (void **)(battle + 0x168);
        slotOffset = (u32)slot * 4;
        slots = (u32)battle + 0x150;
        *active = *(void **)(slots + slotOffset);
        indexOffset = 0x188;
    }
    else
    {
        u32 offset = 0x184;
        active = (void **)((u32)battle + offset);
        slotOffset = (u32)slot * 4;
        offset -= 0x18;
        slots = (u32)battle + offset;
        *active = *(void **)(slots + slotOffset);
        indexOffset = 0x189;
    }
    battle[indexOffset] = slot;
}
int sub_0802F550(u8 first, u8 second, u8 firstMode, u8 secondMode)
{
    int result = 0;
    u16 chance = first - second + 100;
    signed short threshold;

    if (secondMode == 2 && firstMode != 2)
        chance = ((u32)chance * 0x10000 + 0xFFF10000U) >> 16;
    threshold = (signed short)chance;
    if (threshold <= 99 && threshold < (signed short)(sub_0804DEE8(sub_080400A8(), 99) + 1))
        result = 1;
    return result;
}
