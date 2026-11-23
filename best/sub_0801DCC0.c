extern void sub_0800D6E0(u8 *, u16, u8);
extern void sub_0800D9EC(u8 *, u8);
extern const u16 D_081705B0[];
extern u8 D_020031E4[][2];

void sub_0801DCC0(u8 *state)
{
    u8 *flags;
    int mode;
    u32 address;
    int value;

    *(u32 *)(state + 0x6C) = 0;
    {
        int mask = 2;
        mask |= state[0x0A];
        mask |= 1;
        state[0x0A] = mask;
    }
    sub_0800D6E0(state, 0x501, 0);
    sub_0800D9EC(state, 0xB);
    flags = state + 0x41;
    {
        int mask = -13;
        mask &= *flags;
        mask |= 4;
        *flags = mask;
    }

    address = D_081705B0[1];
    address >>= 4;
    address <<= 1;
    address += (u32)D_020031E4;
    mode = 3;
    mode &= *(u8 *)address;
    value = mode;
    if (value > 3)
        mode = 3;

    flags = state + 0x45;
    mode <<= 2;
    {
        int mask = -13;
        mask &= *flags;
        mask |= mode;
        *flags = mask;
    }
    value = state[0x12];
    state[0x22] = value;
    (*(u8 **)(state + 0x28))[0x21] = 8;
}
