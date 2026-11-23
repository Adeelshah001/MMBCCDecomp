extern u8 gUnknown_02007090[];
s8 sub_08026720(u8);

struct UnkArg0 {
    u16 unk00;
    u16 unk02;
    u16 unk04;
    u16 unk06;
};

struct UnkArg1 {
    u8 unk00;
    u8 unk01[10];
    u8 unk0B;
    u8 unk0C;
};

int sub_08025108(struct UnkArg0 *arg0, struct UnkArg1 *arg1) {
    u8 *base, *p, *src;
    s8 i;
    u8 v, b0B, b0C;
    u16 w0, w2, w4, w6;

    base = gUnknown_02007090;
    v = arg1->unk00;
    base[0x3C] = v;
    v = arg1->unk00;
    base[0x3D] = sub_08026720(v);
    i = 0;
    p = base + 0x3E;
    src = arg1->unk01;
    for (; i <= 9; i++) {
        p[i] = src[i];
    }
    b0B = arg1->unk0B;
    b0C = arg1->unk0C;
    w0 = arg0->unk00;
    w2 = arg0->unk02;
    w4 = arg0->unk04;
    w6 = arg0->unk06;
    base[0x48] = b0B;
    base[0x49] = b0C;
    *(u16 *)(base + 0x4A) = w0;
    *(u16 *)(base + 0x4C) = w2;
    *(u16 *)(base + 0x4E) = w4;
    *(u16 *)(base + 0x50) = w6;
    *(u16 *)(base + 0x52) = 0x8000;
    return 0x4000;
}
