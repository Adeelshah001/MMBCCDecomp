struct UnkA {
    u32 unk0[4][32];
    u32 unk200;
    u32 unk204;
};

void sub_0800410C(struct UnkA *arg0) {
    u16 i, j;
    i = 0;
    do {
        j = 0;
        do {
            arg0->unk0[i][j] = 0;
            j = (u16)(j + 1);
        } while (j <= 31);
        i = (u16)(i + 1);
    } while (i <= 3);
    arg0->unk200 = 0;
    arg0->unk204 = 0;
}

struct UnkB {
    u32 unk0[4][32];
};

void sub_08004208(struct UnkB *arg0) {
    u16 i, j;
    i = 0;
    do {
        j = 0;
        do {
            arg0->unk0[i][j] = 0;
            j = (u16)(j + 1);
        } while (j <= 31);
        i = (u16)(i + 1);
    } while (i <= 3);
}

struct InnerC {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    s8 unk3;
};

struct OuterC {
    struct InnerC **unk0;
    u8 unk4;
    u8 unk5;
    u8 unk6;
    u8 unk7;
};

void sub_08004258(struct OuterC *arg0, u8 arg1) {
    s8 v;

    arg0->unk4 = arg1;
    arg0->unk5 = 0;
    v = arg0->unk0[arg0->unk4]->unk1 + 1;
    arg0->unk6 = v;
    if (arg0->unk0[arg0->unk4]->unk3 < 0) {
        if (v == 2) {
            arg0->unk7 = v;
        } else if (v == 1) {
            if (arg0->unk0[arg0->unk4]->unk3 == -1)
                arg0->unk7 = 3;
            else
                arg0->unk7 = 4;
        } else {
            arg0->unk7 = 1;
        }
    } else {
        arg0->unk7 = 0;
    }
}
