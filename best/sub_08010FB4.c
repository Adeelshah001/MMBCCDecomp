extern void sub_080111B4(u8 state);

int sub_08011054(u8 *out)
{
    u8 *state = (u8 *)0x020051B0;
    if (state[4] != 1)
        return 0;
    *out = state[12];
    return 1;
}

int TrySetSelectionMode3(u8 x, u8 y)
{
    u8 *state = (u8 *)0x020051B0;
    if (state[4] == 1) {
        sub_080111B4(3);
        state[13] = x;
        state[14] = y;
        return 1;
    }
    return 0;
}

int sub_08010FB4(u8 slot)
{
    u32 offset = slot * 12;
    u8 *entry = (u8 *)(offset + 0x020051C8);
    if (entry[0] == 0 && ((s8 *)entry)[1] == 0)
        return 1;
    return 0;
}

u32 sub_08010F88(u8 x)
{
    u8 *p = (u8 *)0x020051B0;
    int off;
    u8 *q;
    u8 v;

    v = p[3];
    v &= ~(1U << x);
    {
        u8 z = 0;

        p[3] = v;
        off = x * 12;
        p += 24;
        q = p + off;
        q[0] = z;
        q[6] = z;
        q[1] = z;
    }
    return 1;
}
