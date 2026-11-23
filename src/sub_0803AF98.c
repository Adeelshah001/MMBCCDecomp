extern void sub_080267B4(u8 *, u8);
extern void sub_08004F18(void);
extern void sub_08004F80(void);
extern u8 gUnknown_020070F0[];
extern u8 gUnknown_00004698[];

void sub_0803AF98(u8 *state)
{
    u32 offset;
    u8 value = state[0x469C];

    if (value == 8) {
        sub_080267B4(gUnknown_020070F0, 8);
        offset = (u32)gUnknown_00004698;
        *(state + offset) = 0;
    } else if (value == 9) {
        sub_080267B4(gUnknown_020070F0, 8);
        offset = (u32)gUnknown_00004698;
        *(state + offset) = 6;
    } else {
        u8 zero = 0;
        state[1] = 1;
        state[2] = zero;
        state[3] = zero;
    }
    sub_08004F18();
    sub_08004F80();
}
