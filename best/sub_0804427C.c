struct UnkArg3 {
    u32 unk00;
    u32 unk04;
    u32 unk08;
};

struct Unk2960_Arg2 {
    u32 unk00;
    u32 unk04;
};

struct Unk29B0_Arg2 {
    u32 unk00;
    u32 unk04;
    u32 unk08;
    u32 unk0C;
    u32 unk10;
    u32 unk14;
};

void sub_0800063C(void) {
    u32 stack_var;
    volatile u32 *reg;
    volatile u16 *vram;

    reg = (volatile u32 *)0x040000D4;
    vram = (volatile u16 *)0x02000ED0;
    *(volatile u16 *)0x04000204 = 0x45B7;
    stack_var = 0;
    reg[0] = (u32)&stack_var;
    reg[1] = 0x03000000;
    reg[2] = 0x85001F80;
    reg[2];
    reg[0] = (u32)&stack_var;
    reg[1] = 0x02000000;
    reg[2] = 0x85010000;
    reg[2];
    vram[0x1001] = 0;
    vram[0x1000] = 0;
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

void sub_0804427C(void) {
}
