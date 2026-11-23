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

extern const u8 D_08226720[];

void sub_0801ABE4(u8 *state)
{
    int mode, clear, zero;
    u8 *flags;
    u8 *entry;
    u32 address;
    int frame;

    sub_0800D6E0(state, 0x224, 0);
    address = (u32)D_08226720;
    frame = state[0x11];
    address = frame + address;
    frame = *(const u8 *)address;
    sub_0800D9EC(state, frame);
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
    *(u32 *)(state + 0x58) = 0xA00;
    *(u32 *)(state + 0x60) = -8;
    *(u32 *)(state + 0x5C) = zero;
    *(u32 *)(state + 0x64) = 4;
}
