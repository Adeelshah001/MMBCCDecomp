struct BattleAction2FC {
    u8 unk00[8];
    u16 type;
    u16 amount;
};
extern u8 sub_0803FCC4(u16 type);
extern u16 sub_080400A8(void);
extern int sub_0804DEE8(unsigned value, unsigned divisor);

void ClearPendingBattleAction(struct BattleAction2FC **action, u8 *mode)
{
    if (sub_0803FCC4((*action)->type) == 0)
        *mode = 2;
    *action = 0;
}

void sub_0802FC4C(struct BattleAction2FC **action, u8 mode, u16 amount)
{
    if (mode != 2)
    {
        struct BattleAction2FC *active = *action;
        if (active->type == 0x271)
            active->amount += amount;
    }
}

void sub_0802FBA4(u8 *battle, u8 side, u8 slot)
{
    int indexOffset;
    if (side == 0)
    {
        *(void **)(battle + 0x168) = ((void **)(battle + 0x150))[slot];
        indexOffset = 0x188;
    }
    else
    {
        *(void **)(battle + 0x184) = ((void **)(battle + 0x16C))[slot];
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
        chance -= 15;
    threshold = (signed short)chance;
    if (threshold <= 99 && threshold < (signed short)(sub_0804DEE8(sub_080400A8(), 99) + 1))
        result = 1;
    return result;
}
