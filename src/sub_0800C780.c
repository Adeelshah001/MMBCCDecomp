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
    u16 i;

    for (i = 0; i < count; i++) {
        out[0] = x;
        out[1] = y;
        out += 2;
    }
}

void sub_0800C780(void)
{
}

void sub_0800C8BC(u16 *out, u16 count)
{
    u16 i;

    for (i = 0; i < count; i++) {
        out[0] = 0xFFF8;
        out[1] = 0xFFF8;
        out += 2;
    }
}

extern void QueueResourceTransfer(u8 *p, u32 v);

void sub_0800C878(u8 *s)
{
    u8 *q = s + 0x34;
    u8 v = *q + 1;
    u16 *fp = (u16 *)0x020031E8;
    u32 w;

    if (v > 24)
        v = 0;
    *q = v;

    w = 12 & *fp;
    QueueResourceTransfer((u8 *)(0x0830B660 + (u32)(v >> 2) * 20), (w << 12) + 0x2320);
}
