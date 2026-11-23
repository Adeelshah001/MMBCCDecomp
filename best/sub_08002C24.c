typedef signed short s16;
typedef signed int s32;

extern u16 D_02004828;
extern u32 sub_0804DD08(void);

void sub_080052A0(void) {
    s32 val = (s32)*(s16 *)&D_02004828 * 11 + sub_0804DD08();
    s32 t = (s16)val;
    if (t < 0) {
        t = -t;
    }
    D_02004828 = (u16)(t + 0xFF89);
}

extern u8 D_02003090[];
extern u8 D_020030A0[];
extern void sub_080042B8(void *);

u8 sub_08002C24(u32 arg0) {
    u8 target = (u8)arg0 + 1;
    u32 index = 0;
    if (D_02003090[0] != target) {
        do {
            index++;
        } while (index <= 0x0F && D_02003090[index] != target);
    }
    if (index == 0x10) {
        return 3;
    }
    sub_080042B8(&D_020030A0[index * 20 + 8]);
    return D_020030A0[index * 20 + 15];
}

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

void sub_080029B0(u32 *arg0, u32 *arg1, struct Unk29B0_Arg2 *arg2, struct UnkArg3 *arg3) {
    s32 counter = 0xFF;
    do {
        u32 row = *arg0;
        u32 r6;
        u32 t;

        t = ((u32)(arg3->unk00 & row) >> 5) * arg2->unk00 + arg2->unk0C;
        r6 = arg3->unk00 & t;
        t = ((u32)(arg3->unk04 & row) >> 5) * arg2->unk04 + arg2->unk10;
        r6 |= arg3->unk04 & t;
        t = ((u32)(arg3->unk08 & row) >> 5) * arg2->unk08 + arg2->unk14;
        r6 |= arg3->unk08 & t;
        *arg1 = r6;
        arg0++;
        arg1++;
    } while (--counter >= 0);
}

struct Unk2960_Arg2 {
    u32 unk00;
    u32 unk04;
};

void sub_08002960(u32 *arg0, u32 *arg1, struct Unk2960_Arg2 *arg2, struct UnkArg3 *arg3) {
    s32 counter = 0xFF;
    do {
        u32 row = *arg0;
        u32 r6;
        u32 t;

        t = ((u32)(arg3->unk00 & row) >> 5) * arg2->unk00 + arg2->unk04;
        r6 = arg3->unk00 & t;
        t = ((u32)(arg3->unk04 & row) >> 5) * arg2->unk00 + (arg2->unk04 << 5);
        r6 |= arg3->unk04 & t;
        t = ((u32)(arg3->unk08 & row) >> 5) * arg2->unk00 + (arg2->unk04 << 10);
        r6 |= arg3->unk08 & t;
        *arg1 = r6;
        arg0++;
        arg1++;
    } while (--counter >= 0);
}
