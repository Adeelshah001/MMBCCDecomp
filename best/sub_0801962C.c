extern void sub_0800D6E0(u8 *, int, int);
extern void sub_0800D9EC(u8 *, int);
extern void sub_080174A4(u32, int);
extern const u16 D_081705B0[];
extern u16 D_020031E4[];

static inline int ClampPrio(int prio, int offset)
{
    int p = prio + offset;
    if (p > 3)
        prio = 3;
    else
        prio = p;
    return prio;
}

void sub_0801962C(u8 *state)
{
    int mode, clear, zero;
    u8 *flags;
    u8 *entry;

    sub_0800D6E0(state, 0x233, 0);
    sub_0800D9EC(state, 0);
    entry = (u8 *)&D_020031E4[D_081705B0[0] >> 4];
    mode = 3;
    mode &= *entry;
    mode = ClampPrio(mode, 0);
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
    *(u32 *)(state + 0x5C) = zero;
    *(u32 *)(state + 0x64) = zero;
    sub_080174A4(*(u32 *)(state + 0x2C), 3);
}
