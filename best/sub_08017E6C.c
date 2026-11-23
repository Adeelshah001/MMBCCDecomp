extern const u16 D_081705B0[];
extern u16 D_020031E4[];
extern void sub_0800D6E0(u8 *state, int sprite, int enabled);
extern void sub_0800D9EC(u8 *state, int enabled);
extern void sub_0804A378(int id);

void sub_08017E6C(u8 *state)
{
    u8 priority;
    int flags;
    u8 *attributes;
    const u8 *priorityByte;
    int checked;
    u32 zero;

    sub_0800D6E0(state, 0x20C, 1);
    sub_0800D9EC(state, 1);
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
    attributes -= 0x23;
    zero = 0;
    *attributes = 13;
    *(u32 *)(state + 0x58) = 0x800;
    *(u32 *)(state + 0x60) = zero;
    *(u32 *)(state + 0x5C) = zero;
    *(u32 *)(state + 0x64) = zero;
    sub_0804A378(0xA3);
}
