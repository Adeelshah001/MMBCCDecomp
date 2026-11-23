void sub_0800D6E0(void *, int, int);
void sub_0800D9EC(void *, u8);

extern u8 D_020031E4[];
extern u16 D_081705B0[];

void sub_0801D658(void *state) {
    int var;
    u8 b;

    b = *(u8 *)((u8 *)state + 0x0A);
    b = (u8)(1 | b);
    *(u8 *)((u8 *)state + 0x0A) = b;

    *(u32 *)((u8 *)state + 0x6C) = 0;

    b = *(u8 *)((u8 *)state + 0x0A);
    b = (u8)(2 | b);
    *(u8 *)((u8 *)state + 0x0A) = b;

    sub_0800D6E0(state, 0xA02, 0);
    sub_0800D9EC(state, *(u8 *)((u8 *)state + 0x13));

    var = (int)(3 & *(u8 *)((u8 *)0x020031E4 + ((*(u16 *)0x081705B0 >> 4) * 2)));
    if (var > 3) var = 3;

    b = *(u8 *)((u8 *)state + 0x45);
    b = (u8)((u8)(-13 & b) | (u8)(var << 2));
    *(u8 *)((u8 *)state + 0x45) = b;

    *(u8 *)((u8 *)state + 0x22) = 0;
}
