extern u8 D_020031E4[];
extern u16 D_081705B0[];

void sub_0800D6E0(void *, u32, u32);
void sub_0800D9EC(void *, u32);
void sub_080174A4(u32, u32);
void sub_0804A378(u32);

void sub_08019A3C(void *arg0) {
    u8 *state = arg0;
    int var;
    int mask;
    u16 offset_val;
    u32 index;

    sub_0800D6E0(arg0, 0x23D, 0);
    sub_0800D9EC(arg0, 0);

    offset_val = D_081705B0[0];
    index = ((u16)(offset_val >> 4)) * 2;
    var = 3 & D_020031E4[index];
    if (var > 3) {
        var = 3;
    }

    mask = -13;
    state[0x45] = (u8)((state[0x45] & mask) | (var << 2));
    state[0x22] = 13;
    *(u32 *)(state + 0x58) = 0;
    *(u32 *)(state + 0x60) = 0;
    *(u32 *)(state + 0x5C) = 0;
    *(u32 *)(state + 0x64) = 0;
    sub_0804A378(0x88);
    sub_080174A4(*(u32 *)(state + 0x2C), 3);
}
