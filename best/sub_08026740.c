extern u8 D_020070F0[];
extern void (*const D_0822D8EC[])(u8 *);
void sub_08000EF8(void);
void sub_08000DC0(u32 slot);

void sub_08026740(void)
{
    u8 *state;
    u16 maxTime;

    sub_08000EF8();
    state = D_020070F0;
    maxTime = 0x633B;
    for (;;) {
        if (state[0] != 11) {
            if (++state[16] > 59) {
                int zero = 0;
                state[16] = zero;
                if (state[17] <= 58) {
                    state[17]++;
                } else if (*(u16 *)(state + 18) != maxTime) {
                    state[17] = zero;
                    if (state[18] <= 58) {
                        state[18]++;
                    } else if (state[19] != 99) {
                        state[19]++;
                        state[18] = zero;
                    }
                }
            }
        }
        {
            void (*const *table)(u8 *) = D_0822D8EC;
            u32 mode = state[0];
            table[mode](state);
        }
        sub_08000DC0(1);
    }
}
