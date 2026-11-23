extern const u16 D_081705B0[];
extern u16 D_020031E4[];
extern void sub_0800D6E0(u8 *state, int sprite, int enabled);
extern void sub_0800D9EC(u8 *state, int enabled);

void sub_0801DAD4(u8 *state)
{
    u8 priority;
    int flags;
    u8 *attributes;
    const u8 *priorityByte;
    int checked;
    u8 startFlags, timer;

    *(u32 *)(state + 0x6C) = 0;
    startFlags = 2;
    startFlags |= state[0xA];
    startFlags |= 1;
    state[0xA] = startFlags;
    sub_0800D6E0(state, 0x1400, 0);
    sub_0800D9EC(state, 0);
    priorityByte = (const u8 *)&D_020031E4[D_081705B0[0] >> 4];
    priority = 3;
    priority &= *priorityByte;
    checked = priority;
    if (checked > 3)
        priority = 3;

    attributes = state + 0x45;
    checked = priority << 2;
    flags = -13;
    flags &= *attributes;
    flags |= checked;
    *attributes = flags;
    timer = state[0x12];
    state[0x22] = timer;
}
