struct SceneRestoreState {
    u16 saved;
    u16 pending;
};
extern struct SceneRestoreState D_0200BD10;
extern void sub_08002FD4(u16 value);

struct SceneWaitState {
    u8 pad00[0x7C];
    u16 counter7C;
    u8 pad7E[2];
    volatile short counter80;
};
extern struct SceneWaitState D_0200BD20;

extern volatile u16 D_02002EE0[];
extern void sub_08000F28(u16 value);

u16 GetTrackedAudioId(void)
{
    return D_0200BD10.saved;
}

void sub_0804A38C(void)
{
    D_0200BD20.counter7C = 0;
}

void sub_0804A328(void)
{
    sub_08002FD4(D_0200BD10.saved);
    D_0200BD10.pending = 0;
}

int sub_0804A40C(void)
{
    volatile short *counter = &D_0200BD20.counter80;
    u16 previous = *counter;

    if (*counter > 31) {
        volatile u16 *state = D_02002EE0;
        u16 flags = 0xFFFD & state[1];
        (void)state[1];
        state[1] = flags;
        flags = state[1];
        state[1] = 0;
        sub_08000F28(flags);
        return 0;
    }
    *counter = previous + 1;
    return -1;
}
