struct UnkArg3 {
    u32 unk00;
    u32 unk04;
    u32 unk08;
};

struct Unk29B0_Arg2 {
    u32 unk00;
    u32 unk04;
    u32 unk08;
    u32 unk0C;
    u32 unk10;
    u32 unk14;
};

struct Unk2960_Arg2 {
    u32 unk00;
    u32 unk04;
};

void sub_0800291C(u32 *arg0, u32 *arg1, u32 arg2, struct UnkArg3 *arg3) {
    int i;
    u32 row;
    i = 0xFF;
    do {
        row = *arg0;
        *arg1++ = arg3->unk00 & (((arg3->unk00 & row) * arg2) >> 5)
                | arg3->unk04 & (((arg3->unk04 & row) * arg2) >> 5)
                | arg3->unk08 & ((((arg3->unk08 & row) >> 5) * arg2));
        arg0++;
    } while (--i >= 0);
}

void sub_080029B0(u32 *arg0, u32 *arg1, struct Unk29B0_Arg2 *arg2, struct UnkArg3 *arg3) {
    int i;
    u32 row;
    i = 0xFF;
    do {
        row = *arg0;
        *arg1++ = arg3->unk00 & ((((arg3->unk00 & row) * arg2->unk00) >> 5) + arg2->unk0C)
                | arg3->unk04 & ((((arg3->unk04 & row) * arg2->unk04) >> 5) + arg2->unk10)
                | arg3->unk08 & (((((arg3->unk08 & row) >> 5) * arg2->unk08) + arg2->unk14));
        arg0++;
    } while (--i >= 0);
}

void sub_08002960(u32 *arg0, u32 *arg1, struct Unk2960_Arg2 *arg2, struct UnkArg3 *arg3) {
    int i;
    u32 row;
    u32 mult;
    u32 addend;
    i = 0xFF;
    mult = arg2->unk00;
    addend = arg2->unk04;
    do {
        row = *arg0;
        *arg1++ = arg3->unk00 & ((((arg3->unk00 & row) * mult) >> 5) + addend)
                | arg3->unk04 & ((((arg3->unk04 & row) * mult) >> 5) + (addend << 5))
                | arg3->unk08 & (((((arg3->unk08 & row) >> 5) * mult) + (addend << 10)));
        arg0++;
    } while (--i >= 0);
}

void sub_0800288C(u8 *s, u8 *dst) {
    u8 *dd;
    u8 b;
    u32 sh;
    u8 *src;
    u32 d2;
    u16 field4;
    field4 = *(u16 *)(s + 4);
    if (field4 == 0)
        return;
    b = s[7];
    sh = b << 5;
    dd = dst + sh;
    if (s[6] != 0) {
        src = s + *(u32 *)s;
        d2 = (u32)dd + 0x03002420;
        sub_0804DB30(src, (u8 *)d2);
    } else {
        src = s + *(u32 *)s;
        d2 = (u32)dd + 0x03002420;
        sub_0804DB24(src, (u8 *)d2, field4 >> 2);
    }
}
