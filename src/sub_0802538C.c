struct UnkState_0802538C {
    u8 unk00[4];
    u8 *unk4;
    u32 unk8;
    u8 unk0C;
};

extern void sub_0802520C(void *a0, u32 a1, u32 a2);

void sub_0802538C(struct UnkState_0802538C *state) {
    signed short i = 0;
    do {
        state->unk4[i] = 0;
        i++;
    } while (i <= 0xF8);
    sub_0802520C(&state->unk0C, state->unk8, 0xF9);
}

extern void sub_080252E8(u8 *q);

void sub_0802533C(u8 *p, u8 idx) {
    u8 *q;
    if (idx > 0xF8) return;
    if (idx > 0xC7) {
        q = p + idx;
        if ((*q & 0x7F) > 0x62) return;
        sub_080252E8(q);
        return;
    }
    q = p + idx;
    if ((*q & 0x7F) > 0x62) return;
    sub_080252E8(q);
}

extern void sub_080267B4(u8 *a, u8 kind);
extern u8 gUnknown_02002F50[];
extern u8 gUnknown_020070F0[];

void sub_080281F0(u8 *s) {
    u8 t = s[1];
    u8 *base = gUnknown_02002F50;
    switch (t) {
    case 0:
        s[6] = 0;
        s[1]++;
        /* fallthrough */
    case 1:
        s[6]++;
        if (s[6] > 0xB4 || (*(u16 *)(base + 4) & 1)) {
            sub_080267B4(gUnknown_020070F0, 8);
            s[0x4698] = 0;
        }
        return;
    default:
        return;
    }
}

void sub_08028244(u8 *s) {
    u8 t = s[1];
    u8 *base = gUnknown_02002F50;
    switch (t) {
    case 0:
        s[6] = 0;
        s[1]++;
        /* fallthrough */
    case 1:
        s[6]++;
        if (s[6] > 0xB4 || (*(u16 *)(base + 4) & 1)) {
            sub_080267B4(gUnknown_020070F0, 9);
        }
        return;
    default:
        return;
    }
}
