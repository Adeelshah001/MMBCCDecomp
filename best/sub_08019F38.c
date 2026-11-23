extern const u16 D_081705B0[];
extern u16 D_020031E4[];
extern void sub_0800D770(u8 *state, int sprite, int frame);
extern void sub_0800D9EC(u8 *state, int index);
extern void sub_0800DD08(void *dst, u8 *state);
extern void sub_0800DD2C(u8 *state, int a, int b);
extern void sub_0804A378(int id);

struct Vec2 {
    int x;
    int y;
};

static inline int Clamp3(int x)
{
    int copy = x;
    if (copy > 3)
        x = 3;
    return x;
}

void sub_08019F38(u8 *state)
{
    struct Vec2 vec;
    u32 offset;
    u32 priority;
    int flags;
    int zero;
    u8 *attributes;

    sub_0800D770(state, 0x840, 0);
    sub_0800D9EC(state, 0);

    offset = (u32)D_081705B0;
    offset = *(const u16 *)offset;
    offset >>= 4;
    offset <<= 1;
    offset += (u32)D_020031E4;
    priority = 3;
    offset = *(u8 *)offset;
    priority &= offset;
    priority = Clamp3(priority);

    attributes = state + 0x45;
    priority <<= 2;
    flags = -13;
    flags &= *attributes;
    flags |= priority;
    *attributes = flags;
    attributes -= 0x23;
    zero = 0;
    *attributes = 0xD;
    *(u32 *)(state + 0x58) = zero;
    *(u32 *)(state + 0x60) = zero;
    *(u32 *)(state + 0x5C) = zero;
    *(u32 *)(state + 0x64) = zero;
    sub_0800DD08(&vec, state);
    sub_0800DD2C(state, 0xA00, 0);
    sub_0804A378(0x84);
}
