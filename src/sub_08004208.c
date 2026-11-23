typedef signed short s16;

struct UnkA {
    u32 unk0[4][32];
    u32 unk200;
    u32 unk204;
};

void sub_0800410C(struct UnkA *arg0) {
    s16 i = 0;
    s16 j;
    do {
        j = 0;
        do {
            arg0->unk0[i][j] = 0;
            j++;
        } while (j <= 31);
        i++;
    } while (i <= 3);
    arg0->unk200 = 0;
    arg0->unk204 = 0;
}

struct UnkB {
    u32 unk0[4][32];
};

void sub_08004208(struct UnkB *arg0) {
    s16 i = 0;
    s16 j;
    do {
        j = 0;
        do {
            arg0->unk0[i][j] = 0;
            j++;
        } while (j <= 31);
        i++;
    } while (i <= 3);
}
