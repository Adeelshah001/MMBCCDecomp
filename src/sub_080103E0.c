struct Obj103E0 {
    u8 unk00[0x23];
    u8 side:4;
    u8 unk23_4:4;
};

struct Slot103E0 {
    u8 unk00[0x10];
    u8 flags;
    u8 unk11[3];
};

struct State103E0 {
    u8 unk00;
    u8 unk01[7];
    struct Slot103E0 slots[2];
};

struct Vec2 {
    u32 x;
    u32 y;
};

extern struct State103E0 D_02005160;
extern void sub_08010478(u8);
extern int sub_080236B0(u8, struct Slot103E0 *, struct Obj103E0 *, struct Vec2 *);

int sub_080103E0(u8 arg0, struct Obj103E0 *arg1, u32 arg2, u32 arg3)
{
    struct State103E0 *s = &D_02005160;
    struct Slot103E0 *slot;
    struct Vec2 pos;
    u8 flags;
    int mask;

    if (s->unk00 != 0)
        return 0;

    if (arg1->side == 1)
        slot = &s->slots[1];
    else
        slot = &s->slots[0];

    flags = slot->flags;
    mask = 1;
    mask &= flags;
    if (!mask) {
        mask = 2;
        mask &= flags;
        if (!mask) {
            pos.x = arg2;
            pos.y = arg3;
            if (sub_080236B0(arg0, slot, arg1, &pos)) {
                int bit = 1;
                bit |= slot->flags;
                slot->flags = bit;
                return 1;
            }
        }
    } else {
        sub_08010478(arg1->side);
    }
    return 0;
}
