struct PositionEntry { u8 pad[4]; u8 x; u8 y; u8 pad6; u8 flags; };

extern struct PositionEntry D_02004E18[];
extern const u16 D_08171EF4[2];
extern void sub_08006578(int x, int y, u8 width, u8 height, u16 a, u16 b);
extern int sub_08022FE4(struct PositionEntry *entry);

void sub_08007CF4(u16 idx, u8 x, u8 y)
{
    struct PositionEntry *entry = D_02004E18 + idx;
    int flags;

    entry->x = x;
    entry->y = y;
    flags = -5;
    flags &= entry->flags;
    entry->flags = flags;
    if (idx == 0) {
        int sx = (s8)x;
        int sy = (s8)y;
        const u16 *settings = D_08171EF4;
        sub_08006578(sx, sy, 8, 7, settings[0], settings[1]);
    } else {
        flags &= 1;
        if (flags == 0 && sub_08022FE4(entry)) {
            flags = 1;
            flags |= entry->flags;
            entry->flags = flags;
        }
    }
}
