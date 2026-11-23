void sub_080112BC(u8 *state)
{
    unsigned zero = 0;
    unsigned next = state[4] + 1;
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
    int difference = first - second;
    int midpoint = (second >> 1) + (first >> 1);
    dest->first = difference;
    dest->second = midpoint;
}

extern u8 D_020051B0[];

int sub_0801109C(void)
{
    u8 *state = D_020051B0;
    if (state[4] == 1)
        return 1;
    return 0;
}

struct State5230 {
    u8 unk00[4];
    u8 mode;
    u8 unk05[29];
    u8 skipReset;
};

extern struct State5230 D_02005230;
extern u16 (*const D_08173EC8[])(struct State5230 *);
extern void sub_08010B30(void);

short sub_080114E8(void)
{
    u16 (*const *handlers)(struct State5230 *) = D_08173EC8;
    struct State5230 *state = &D_02005230;
    u16 result;
    do {
        u8 mode = state->mode;
        u16 (*handler)(struct State5230 *) = handlers[mode];
        result = handler(state);
    } while ((short)result < 0);

    if (D_02005230.skipReset)
        D_02005230.skipReset = 0;
    else
        sub_08010B30();
    return (short)result;
}
