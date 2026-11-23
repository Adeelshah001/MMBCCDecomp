extern volatile struct SerialLinkStatus D_02002EE0;
extern volatile u16 D_04000128;
extern void sub_08001800(void);
extern void sub_08001AE4(void);

void UpdateSerialLinkStatus(void)
{
    volatile u16 *control = &D_04000128;
    u16 current = *control;
    if (!(0x40 & current)) {
        volatile struct SerialLinkStatus *state = &D_02002EE0;
        if (state->id == 0) {
            u16 bits = *control;
            u32 id = 0x30;
            id &= bits;
            id >>= 4;
            state->id = id;
        }
        state->ready = 1;
        if (state->enabled != 0) {
            sub_08001800();
            sub_08001AE4();
        }
    }
}
