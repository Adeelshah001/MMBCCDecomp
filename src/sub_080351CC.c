typedef u32 (*StateHandler)(u8 *);
extern StateHandler D_0822EA6C[];
extern StateHandler D_0822EA80[];
extern u16 sub_08024554(u8);

u8 sub_080350B4(u8 *state)
{
    StateHandler *handlers = D_0822EA6C;
    u32 index = state[4];
    return (u8)handlers[index](state);
}

u32 sub_08035128(u8 *state)
{
    u32 done = 0;
    StateHandler *handlers = D_0822EA80;
    u8 *phase = state + 0x46A8;
    if ((u8)handlers[*phase](state) != 0) {
        state[4] = 3;
        state[5] = done;
    }
    if (*phase == 3) {
        state[0x46B7] = *phase;
        done = 1;
    }
    return done;
}

int sub_080351CC(u8 *state)
{
    int zero = 0;
    state[4] = 1;
    state[5] = zero;
    return 0;
}

int sub_08034BD4(u8 kind, u16 amount)
{
    int band = 3;

    if (amount != 0 && kind != 0) {
        u16 total = sub_08024554(kind);
        if (amount >= total * 7 / 10) {
            band = 0;
        } else {
            int cutoff = total * 3 / 10;
            band = 2;
            if (amount >= cutoff)
                band = 1;
        }
    }
    return band;
}
