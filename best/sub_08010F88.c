extern void sub_080111B4(u8 state);

int sub_08011054(u8 *out)
{
    u8 *state = (u8 *)0x020051B0;
    int result = 0;
    if (state[4] == 1) {
        *out = state[12];
        result = 1;
    }
    return result;
}

int sub_08010FB4(u8 slot)
{
    u32 offset = slot * 12;
    u8 *entry = (u8 *)(offset + 0x020051C8);
    if (entry[0] != 0)
        goto occupied;
    if (((s8 *)entry)[1] != 0)
        goto occupied;
    return 1;
occupied:
    return 0;
}

u32 sub_08010F88(u8 x)
{
    u8 *p = (u8 *)0x020051B0;
    int off;
    u8 *q;
    u32 mask = 1U << x;
    u32 v = p[3];
    v &= ~mask;
    {
        u8 z;

        p[3] = v;
        z = 0;
        off = x * 12;
        p += 24;
        q = p + off;
        q[0] = z;
        q[6] = z;
        q[1] = z;
    }
    return 1;
}
