typedef void (*StateHandler)(u8 *);
typedef u8 (*UpdateHandler)(u8 *);

extern StateHandler D_0822DC84[];
extern UpdateHandler D_0822DDA0[];
extern u8 D_0200B7E0[];
extern void sub_08004F18(void);
extern void sub_08004F80(void);
extern void sub_08027E8C(u8 *);

void sub_08027718(u8 *state)
{
    StateHandler *handlers = D_0822DC84;
    u32 index = state[1];
    handlers[index](state);
}

void sub_08027CFC(void)
{
    u8 *state = D_0200B7E0;
    int mask = -7;
    state[3] &= mask;
    sub_08004F18();
}

void sub_08027D18(void)
{
    u8 *state = D_0200B7E0;
    UpdateHandler *handlers = D_0822DDA0;
    state[2] = handlers[state[2]](state);
    sub_08027E8C(state);
    sub_08004F80();
}

int sub_08027D4C(int value)
{
    u8 *state = D_0200B7E0;
    u8 *entries;
    int count;
    s8 i;

    if (state[4] >= 12)
        return 0;

    i = 0;
    count = state[4];
    entries = state + 0x1C;
    for (; i < count; i++) {
        if (entries[i] == value)
            return 0;
    }
    entries[count] = value;
    state[4]++;
    return 1;
}
