typedef signed short s16;

struct PositionState {
    u8 reserved00[6];
    u16 flags06;
    u8 reserved08[12];
    u16 flags14;
    u16 x;
    u16 y;
    u8 state;
};

extern u8 D_02003670[];

void sub_0800C5B8(const struct PositionState *state, u16 *out, u16 count)
{
    u16 x = state->x >> 1;
    u16 y = state->y >> 1;
    s16 i;

    for (i = 0; i < count; i++) {
        *out++ = x;
        *out++ = y;
    }
}

void sub_0800C5FC(void)
{
}

void sub_0800C6AC(void)
{
}

void sub_0800C4B4(struct PositionState *state)
{
    u8 *flags = D_02003670 + 0x11AE;
    u16 start;
    int mask = 0xFFFF;

    if ((*flags & 4) == 0)
        start = 0xFFF8;
    else
        start = 0;

    state->x = start;
    state->y = start;
    state->flags14 |= mask;
    state->flags06 |= mask;
    state->state = 0;
}
