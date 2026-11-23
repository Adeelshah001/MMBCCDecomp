void sub_080112BC(volatile u8 *state)
{
    u8 next = state[4] + 1;
    u8 zero = 0;
    state[4] = next;
    state[5] = zero;
    state[6] = zero;
    state[7] = zero;
}

struct CoordinatePair {
    int first;
    int second;
};

void ComputePairDiffAndMidpoint(const struct CoordinatePair *source, struct CoordinatePair *dest)
{
    int second = source->second;
    int first = source->first;
    int midpoint = (second >> 1) + (first >> 1);
    int difference = first - second;
    dest->first = difference;
    dest->second = midpoint;
}

extern u8 D_020051B0[];

int sub_0801109C(void)
{
    u8 *state = D_020051B0;
    return state[4] == 1;
}

struct State5230 {
    u8 unk00[4];
    u8 mode;
    u8 unk05[29];
    u8 skipReset;
};

extern struct State5230 D_02005230;
extern const u32 D_08173EC8[];
extern void sub_08010B30(void);

short sub_080114E8(void)
{
    const u32 *handlers = D_08173EC8;
    struct State5230 *state = &D_02005230;
    u16 result;
    do {
        u32 handler = state->mode;
        handler = handlers[handler];
        result = ((u16 (*)(struct State5230 *))handler)(state);
    } while ((short)result < 0);

    if (D_02005230.skipReset)
        D_02005230.skipReset = 0;
    else
        sub_08010B30();
    return (short)result;
}
