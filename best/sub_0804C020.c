u32 sub_0804C278(u32 a, u32 b, u32 c, u32 d);

void sub_0804C020(u32 *state) {
    u32 magic = 0x68736D53;
    u32 r0, r3;
    if (state[0x34/4] != magic) return;
    state[0x34/4] = magic + 1;
    if (state[0x38/4] == 0) return;
    r0 = state[0x3C/4];
    r3 = state[0x38/4];
    sub_0804C278(r0, 0, magic, r3);
}
