extern u32 *sub_0801709C(u8 kind);
extern u8 sub_080170C4(u32 *object);
extern void sub_0800E1F0(u8 mode);
extern void sub_0800D568(u32 *object);
extern u8 D_02005130[];
extern u32 *D_02005270;
extern u32 *D_020053C0;

void sub_0800E440(void)
{
    u8 *state = D_02005130;
    u32 *volatile *object = (u32 *volatile *)(state + 0x1C);

    *(u16 *)(state + 0x18) = 1;
    switch (state[0x15]) {
    case 0: {
        u8 kind;
        if (state[0x25] != 0)
            kind = 5;
        else
            kind = 3;
        *object = sub_0801709C(kind);
        if (*object == 0) {
            u8 *base = (u8 *)0x02005130;
            *(u16 *)(base + 0x18) = 0;
            sub_0800E1F0(0);
        } else {
            state[0x15]++;
        }
        break;
    }
    case 1:
        if (sub_080170C4(*object)) {
            u8 mode = 0;
            *(u16 *)(state + 0x18) = mode;
            sub_0800E1F0(mode);
        }
        break;
    }
    sub_0800D568(D_02005270);
    sub_0800D568(D_020053C0);
}
