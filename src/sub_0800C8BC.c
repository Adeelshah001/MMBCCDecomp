struct PositionState {
    u8 reserved00[6];
    u16 flags06;
    u8 reserved08[12];
    u16 flags14;
    u16 x;
    u16 y;
    u8 state;
};

void sub_0800C5B8(struct PositionState *state, u16 *out, u16 count)
{
    u16 x = state->x >> 1;
    u16 y = state->y >> 1;
    signed short i;

    for (i = 0; i < count; i++) {
        out[0] = x;
        out += 1;
        out[0] = y;
        out += 1;
    }
}

extern void QueueResourceTransfer(u8 *p, u32 v);

void sub_0800C878(u8 *s)
{
    u16 *fp = (u16 *)0x020031E8;
    u8 *q = s + 0x34;
    u8 v = *q + 1;
    u32 w;
    u8 *entry;

    if (v > 24)
        v = 0;
    *q = v;

    w = (u32)(12 & *fp) << 12;
    entry = (u8 *)(0x0830B660 + (u32)(v >> 2) * 20);
    QueueResourceTransfer(entry, w + 0x2320);
}

void sub_0800C8BC(u32 dummy, u16 *out, u16 count)
{
    u16 a = 0xFFF8;
    u16 b = 0xFFF8;
    signed short i;

    for (i = 0; i < count; i++) {
        out[0] = a;
        out += 1;
        out[0] = b;
        out += 1;
    }
}
