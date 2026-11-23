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
extern const u8 D_000011AE[];
extern const u8 D_0000FFF8[];
extern const u8 D_0000FFFF[];

void sub_0800C5B8(const struct PositionState *state, u16 *out, int rawCount)
{
    register u16 *dest = out;
    int count = (u16)rawCount;
    u16 x = state->x >> 1;
    u16 y = state->y >> 1;
    s16 i = 0;

    if (i < count) {
        do {
            *dest = x;
            dest++;
            *dest = y;
            dest++;
            i++;
        } while (i < count);
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
    u8 *base = D_02003670;
    u32 offset = (u32)D_000011AE;
    u8 *flags = base + offset;

    int bit = 4;
    if ((bit & *flags) == 0) {
        state->x = (u32)D_0000FFF8;
        state->y = (u32)D_0000FFF8;
    } else {
        state->x = 0;
        state->y = 0;
    }
    {
        int mask = (u32)D_0000FFFF;
        u16 current = state->flags14;
        state->flags14 = current | mask;
        current = state->flags06;
        state->flags06 = mask | current;
    }
    state->state = 0;
}
