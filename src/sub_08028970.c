extern s8 sub_08028778(u8 *phase, u8 mode);
extern int sub_0802FD68(u8 *state);

u32 sub_08028970(u8 *state)
{
    u32 flags = state[6];
    u32 mask = 8;
    int result;

    mask &= flags;
    if (mask)
        goto advance;
    mask = 32;
    mask &= flags;
    if (mask)
    {
        result = sub_08028778(state + 1, 0);
        if (result != 0)
            goto finish;
        goto update;
    }

    switch (state[1])
    {
    case 0:
        state[1] = 1;
    case 1:
        if ((u8)sub_0802FD68(state) != 0)
            goto advance;
        break;
    }
    return 0;

advance:
    result = 0;
update:
    state[0] = 1;
    state[1] = result;
finish:
    return 0;
}

