extern void sub_0800D770(u8 *state, u16 id, u8 variant);
extern void sub_0800D9EC(u8 *state, u8 variant);
struct ObjectPosition { int x, y; };
extern struct ObjectPosition *sub_0800DD08(struct ObjectPosition *position, u8 *state);
extern void sub_0800DD2C(u8 *state, int x, int y);
extern void sub_0804A378(int id);
extern const u16 D_081705B0[];
extern u16 D_020031E4[];

static inline int ClampPriority(int limit, int priority)
{
    if (priority > limit)
        priority = limit;
    return priority;
}

void sub_0801A81C(u8 *state)
{
    int mode, clear, zero;
    u8 *flags;
    u8 *entry;
    struct ObjectPosition position;

    sub_0800D770(state, 0x858, 0);
    sub_0800D9EC(state, 0);
    entry = (u8 *)&D_020031E4[D_081705B0[0] >> 4];
    mode = 3;
    mode &= *entry;
    mode = ClampPriority(3, mode);
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
    sub_0800DD08(&position, state);
    sub_0800DD2C(state, 0x1400, 0);
    sub_0804A378(0xA0);
}
