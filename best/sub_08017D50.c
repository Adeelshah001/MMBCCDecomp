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

extern void sub_0800DD4C(u8 *, int, int);

void sub_08017D50(u8 *state)
{
    int mode, clear, zero;
    u8 *flags;
    u8 *entry;

    sub_0800D6E0(state, 0x21B, 0);
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
    *(u32 *)(state + 0x58) = 0x400;
    *(u32 *)(state + 0x60) = zero;
    *(u32 *)(state + 0x5C) = 0x400;
    *(u32 *)(state + 0x64) = 0x80;
    sub_0800DD4C(state, zero, -0x2C00);
}
