extern u16 D_081705B0;
extern u8 D_020031E4[];

void sub_0800D6E0(void *, u32, u32);
void sub_0800D9EC(void *, u32);

void sub_08021E64(u8 *state) {
    u32 var;

    *(u32 *)(state + 0x6C) = 0;
    state[0x0A] = (u8)(2 | state[0x0A] | 1);
    sub_0800D6E0(state, 0x2D01, 0);
    sub_0800D9EC(state, 0);
    var = 3 & D_020031E4[((u16)D_081705B0 >> 4) * 2];
    if (var > 3) {
        var = 3;
    }
    state[0x45] = (u8)((state[0x45] & -13) | (var << 2));
    state[0x22] = 0;
    state[0x12] = 0xFF;
}
