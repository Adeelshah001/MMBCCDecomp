extern void sub_080111B4(u32 state);

u32 TrySetSelectionMode3(u8 option, u8 value)
{
    u8 *state = (u8 *)0x020051B0;

    if (state[4] != 1)
        return 0;

    sub_080111B4(3);
    state[13] = option;
    state[14] = value;
    return 1;
}
