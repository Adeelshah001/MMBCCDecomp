extern u8 D_020031E4[];
extern u16 D_081705B0[];

void sub_0800D6E0(void *state, u32 a, u8 b);
void sub_0800D9EC(void *state, u32 a);
void sub_0800DD4C(void *state, u32 a, u32 b);
void sub_0804A378(u32 a);

void sub_08019090(void *state) {
    u8 *s = state;
    u8 *base;
    u8 *entry;
    int mode;
    u8 *p;
    int clear;
    int idx;
    int mode_copy;
    u32 arg_a;
    int zero;

    arg_a = 0x22F;
    sub_0800D6E0(state, arg_a, s[0x11]);
    sub_0800D9EC(state, 0);

    idx = (D_081705B0[0] >> 4) * 2;
    base = D_020031E4;
    entry = base + idx;
    mode = 3;
    mode &= *entry;
    mode_copy = mode;
    if (mode_copy > 3) mode = 3;

    p = s + 0x45;
    mode <<= 2;
    clear = -13;
    *p = (clear & *p) | mode;
    p -= 0x23;
    zero = 0;
    *p = 0xD;
    *(u32 *)(s + 0x58) = zero;
    *(u32 *)(s + 0x60) = zero;
    *(u32 *)(s + 0x5C) = zero;
    *(u32 *)(s + 0x64) = zero;

    sub_0800DD4C(state, 0xFFFFE600, 0xFFFFE700);
    sub_0804A378(0x9F);
}
