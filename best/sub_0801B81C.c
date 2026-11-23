extern void sub_0800D6E0(u8 *, int, int);
extern void sub_0800D9EC(u8 *, int);
extern const u16 D_081705B0[];
extern u16 D_020031E4[];

static inline int LimitMode(int mode)
{
    if (mode > 3)
        mode = 3;
    return mode;
}

void sub_0801B81C(u8 *state)
{
    int mode, clear, zero;
    u8 *flags;
    u8 *entry;

    sub_0800D6E0(state, 0x313, 0);
    sub_0800D9EC(state, 0);
    entry = (u8 *)&D_020031E4[D_081705B0[0] >> 4];
    mode = 3;
    mode &= *entry;
    mode = LimitMode(mode);
    flags = state + 0x45;
    mode <<= 2;
    clear = 13;
    clear = -clear;
    *flags = (clear & *flags) | mode;
    flags -= 0x23;
    zero = 0;
    *flags = 0xD;
    *(u32 *)(state + 0x58) = zero;
    *(u32 *)(state + 0x60) = zero;
    *(u32 *)(state + 0x5C) = zero;
    *(u32 *)(state + 0x64) = zero;
}
