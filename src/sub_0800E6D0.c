struct State02005130 {
    u8 pad00[0x15];
    u8 unk15;
    u8 pad16[2];
    u16 unk18;
    u8 pad1A[0x0F];
    u8 unk29;
};

extern struct State02005130 D_02005130;
extern u8 *D_02005020[];
extern u8 *D_02005270;
extern u8 *D_020053C0;

void sub_08016F74(u8 *);
u16 sub_08016F88(u8 *);
void sub_0800E1F0(u8);
void sub_0800D568(u8 *);

void sub_0800E6D0(void) {
    struct State02005130 *s = &D_02005130;
    u8 *target;

    s->unk18 = 1;
    if (s->unk29 == 0) {
        target = D_02005020[0];
    } else {
        target = D_02005020[1];
    }

    switch (s->unk15) {
    case 0:
        sub_08016F74(target);
        s->unk15++;
        break;
    case 1:
        if (sub_08016F88(target)) {
            D_02005130.unk18 = 0;
            sub_0800E1F0(0);
        }
        break;
    }

    sub_0800D568(D_02005270);
    sub_0800D568(D_020053C0);
}
