extern void sub_0800D6E0(u8 *state, u16 id, u8 variant);
extern void sub_0800D9EC(u8 *state, u8 variant);
extern const u16 D_081705B0[];
extern u16 D_020031E4[];

static inline int ClampPriority(int priority)
{
    if (priority > 3)
        priority = 3;
    return priority;
}

void sub_08020D54(u8 *state)
{
    u8 *owner = *(u8 **)(state + 0x28);
    int mode, clear;
    u8 *attributes;
    volatile u8 *entry;

    *(u32 *)(state + 0x6C) = 0;
    {
        int flags = 2;
        flags |= state[0x0A];
        flags |= 1;
        state[0x0A] = flags;
    }
    sub_0800D6E0(state, 0x421C, 0);
    sub_0800D9EC(state, 0);
    entry = (u8 *)&D_020031E4[D_081705B0[0] >> 4];
    mode = 3;
    mode &= *entry;
    mode = ClampPriority(mode);
    attributes = state + 0x45;
    mode <<= 2;
    clear = ~0x0C;
    *attributes = (clear & *attributes) | mode;

    *(u32 *)(state + 0x50) = 0x7800;
    *(u32 *)(state + 0x54) = 0x6400;
    {
        int flags = 2;
        flags |= owner[0x0A];
        owner[0x0A] = flags;
    }
    state[0x12] = 0x1E;
}
