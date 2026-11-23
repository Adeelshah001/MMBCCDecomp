struct BattleAction2FC {
    u8 unk00[8];
    u16 type;
    u16 amount;
};
extern u8 sub_0803FCC4(u16 type);
extern u16 sub_080400A8(void);
extern int sub_0804DEE8(unsigned value, unsigned divisor);

extern const u8 D_00000271[];
void sub_0802FC4C(struct BattleAction2FC **action, u8 mode, u16 amount)
{
    if (mode != 2)
    {
        struct BattleAction2FC *active = *action;
        const unsigned type = (u32)D_00000271;
        if (type == active->type)
        {
            u16 previous = active->amount;
            active->amount = previous + amount;
        }
    }
}

void sub_0802FBA4(u8 *battle, u8 side, u32 rawSlot)
{
    u8 slot = (u8)rawSlot;
    u32 offset;
    void **active;
    u32 slots;

    if (side == 0)
    {
        active = (void **)(battle + 0x168);
        offset = (u32)slot * 4;
        slots = (u32)battle + 0x150;
        *active = *(void **)(slots + offset);
        offset = 0x188;
    }
    else
    {
        u32 activeOffset = 0x184;
        active = (void **)((u32)battle + activeOffset);
        offset = (u32)slot * 4;
        activeOffset -= 0x18;
        slots = (u32)battle + activeOffset;
        *active = *(void **)(slots + offset);
        offset = 0x189;
    }
    battle[offset] = slot;
}
