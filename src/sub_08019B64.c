extern void sub_0800D6E0(u8 *, int, int);
extern void sub_0800D9EC(u8 *, int);
extern void sub_0800DD4C(u8 *, int, int);
extern void sub_080174A4(u32, int);
extern const u16 D_081705B0[];
extern u16 D_020031E4[];

void sub_08019B64(u8 *state)
{
    int priority;
    int flags;
    u8 *attributes;
    const u8 *priorityByte;
    u32 val;
    u32 t;
    u32 zero;

    sub_0800D6E0(state, 0x200, state[0x11]);
    sub_0800D9EC(state, 0);
    priorityByte = (const u8 *)&D_020031E4[D_081705B0[0] >> 4];
    priority = 3;
    priority &= *priorityByte;
    flags = (u8)priority;
    if (flags > 3) {
        val = (u32)flags >> 16;
        priority = (val >> 16) + 3;
    }

    attributes = state + 0x45;
    priority <<= 2;
    t = (u32)flags >> 16;
    flags = t >> 16;
    flags += 13;
    flags = -flags;
    val = *attributes;
    flags &= val;
    flags |= priority;
    *attributes = flags;
    attributes -= 0x23;
    zero = 0;
    *attributes = 13;
    *(u32 *)(state + 0x58) = zero;
    *(u32 *)(state + 0x60) = zero;
    *(u32 *)(state + 0x5C) = zero;
    *(u32 *)(state + 0x64) = zero;
    sub_0800DD4C(state, -0x3C00, 0);
    sub_080174A4(*(u32 *)(state + 0x2C), 3);
}
