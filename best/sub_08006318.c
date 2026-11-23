typedef signed short s16;

struct Slot {
    u8 reserved00[4];
    u16 entries[12];
    u8 reserved1C[2];
    u8 index;
    u8 flags;
};

struct WindowState {
    u16 flags;
    u8 reserved02[10];
    u8 mask;
    u8 reserved0D;
    u8 mode;
};

extern u8 D_02004830[];
extern u8 D_0200483C[];
extern struct Slot D_02004CA0[];
extern u8 D_02003670[];
extern struct WindowState D_02003230;
extern const u8 D_00000265[];
extern const u8 D_000011B0[];
extern const u8 D_000011B1[];
extern const u8 D_000011B2[];
extern const u8 D_000011B3[];

extern void sub_08006168(void *, s8, s8, u8, u8, u16, u16);
extern void sub_08006374(void *, s8, s8, u8, u8, u16, u16, u32);
extern void sub_08005338(u8, u8, u8, u8);

void sub_08006124(int x, int y, u8 width, u8 height, u16 a, u16 b)
{
    sub_08006168(D_0200483C, (s8)x, (s8)y, width, height, a, b);
}

void sub_08005FC0(int rawSlot)
{
    struct Slot *slot = &D_02004CA0[(u8)rawSlot];
    int flags;
    int mask = -7;
    s16 i;

    slot->index = 0;
    flags = slot->flags | 1;
    flags &= mask;
    flags |= 4;
    flags |= 1;
    slot->flags = flags;

    i = 0;
    do {
        slot->entries[i] = 0;
        slot->flags |= 1;
        i++;
    } while (i <= 11);
}

void sub_08006318(u8 x, u8 y, u8 width, u8 height, u16 a, u16 b, u32 c)
{
    u8 *base = D_02004830;
    u32 offset = (u32)D_00000265;
    if (base[offset] == 0)
        sub_08006374(base + 12, (s8)x, (s8)y, width, height, a, b, c);
}

void sub_080052DC(int a, int b, int c, int d)
{
    u8 *base = D_02003670;
    struct WindowState *window = &D_02003230;
    u32 mask = 0x2000;

    window->flags = mask | window->flags;
    window->mask = 0xFF;
    window->mode = 10;
    base[(u32)D_000011B0] = a;
    base[(u32)D_000011B1] = b;
    base[(u32)D_000011B2] = c;
    base[(u32)D_000011B3] = d;
    sub_08005338(0xFF, 0xFF, 0xFF, 0xFF);
}
