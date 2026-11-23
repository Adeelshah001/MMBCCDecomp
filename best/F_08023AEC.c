void F_08023AEC(u8 *state, u8 *work, u8 *param) {
    u8 *g;
    u8 check;
    u32 r;
    u8 r8;
    u8 *p;
    u8 x;
    u8 y;
    u8 sum;
    g = (u8 *)0x02000840;
    sub_08023B88(param);
    sub_08023DD8(g, (u16 *)param);
    sub_08023CE4(state, g);
    check = g[0x0E];
    r = HasInvalidCodeChecksum(g, check);
    r8 = (u8)r;
    if (r8 != 1) {
        p = g + 0x10;
        x = state[2];
        y = state[6];
        sum = x + y;
    }
}
