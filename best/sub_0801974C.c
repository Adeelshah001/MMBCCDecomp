extern const u16 D_081705B0[];
extern u16 D_020031E4[];
extern void sub_0800D6E0(u8 *state, u16 sprite, u8 frame);
extern void sub_0800D9EC(u8 *state, u8 index);
extern void sub_080174A4(void *actor, int mode);

void sub_0801974C(u8 *state)
{
    int priority;
    int flags;
    int zero;
    u8 *attributes;
    u32 offset;
    u32 controls;

    sub_0800D6E0(state, 0x236, 0);
    sub_0800D9EC(state, 0);

    offset = (u32)D_081705B0;
    offset = *(const u16 *)offset;
    offset >>= 4;
    offset <<= 1;
    controls = (u32)D_020031E4;
    offset += controls;
    priority = 3;
    offset = *(u8 *)offset;
    priority &= offset;
    flags = priority;
    if (flags > 3)
        priority = 3;

    attributes = state + 0x45;
    priority <<= 2;
    flags = -13;
    flags &= *attributes;
    flags |= priority;
    *attributes = flags;
    attributes -= 0x23;
    zero = 0;
    *attributes = 13;
    *(u32 *)(state + 0x58) = 0x400;
    *(u32 *)(state + 0x60) = zero;
    *(u32 *)(state + 0x5C) = zero;
    *(u32 *)(state + 0x64) = zero;
    sub_080174A4(*(void **)(state + 0x2C), 3);
}
