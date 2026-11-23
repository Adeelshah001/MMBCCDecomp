typedef signed short s16;
typedef signed int s32;

extern u8 gUnknown_030005C0[];
extern u32 D_02000800;
extern u8 gUnknown_03000400[];
extern u16 D_03007FF8;
extern void sub_08000300(void *, void *, u32);
extern void sub_08000328(u32);
extern void sub_08000A1C(void);
extern void sub_08000AD4(void);
extern void sub_0804DCCC(u32, u32, u8);

struct Struct_C68 {
    u32 unk0;
    u16 *unk4;
    u16 unk8;
    u8 unkA;
    u8 unkB;
    u16 *unkC;
};

void sub_08000C68(struct Struct_C68 *arg0) {
    u16 *r2 = arg0->unkC;
    u16 *r3 = arg0->unk4;
    u16 r1 = arg0->unk8;
    if (r1 != 0) {
        s32 r6 = ((s32)arg0->unkA << 0x18) >> 0x17;
        s32 r5 = ((s32)arg0->unkB << 0x18) >> 0x17;
        do {
            *r3 = *r2;
            r3 += r6;
            r2 += r5;
            r1--;
        } while (r1 != 0);
    }
    arg0->unkC = r2;
}

void sub_08000DC0(s16 arg0) {
    u8 *base = gUnknown_030005C0;
    u32 idx = *(u32 *)(base + 0x1E50);
    u8 *elemBase = base + 0x1E08;
    u8 *elem = elemBase + idx * 24;
    if (arg0 != 0) {
        *(u16 *)(elem + 2) = arg0;
        elem[0] = 4;
        sub_08000300(elem + 4, elem + 8, D_02000800);
    }
}

void sub_08000E80(u32 arg0) {
    u8 *base = gUnknown_030005C0;
    u32 idx = *(u32 *)(base + 0x1E50);
    u8 *elemBase = base + 0x1E08;
    u8 *elem = elemBase + idx * 24;
    elem[1] = 1;
    *(u32 *)(elem + 4) = arg0;
    sub_08000328(D_02000800);
}

void sub_08000918(void) {
    u8 *base = gUnknown_03000400;
    u8 *ptr = base + 0x167;
    u8 val = *ptr;
    u8 *ptr2;
    u8 val2;
    u32 *ptr3;
    u32 val3;
    if ((val & 1) == 0) {
        *ptr = val | 1;
        D_03007FF8 = 1;
        ptr2 = base + 0x2B4;
        val2 = *ptr2;
        *ptr2 = val2 + 1;
        ptr3 = (u32 *)(base + 0x158);
        val3 = *ptr3;
        if (val3 != 0) {
            sub_0804DCCC(val3, 0x158, val2);
        }
        sub_08000A1C();
        sub_08000AD4();
        *ptr ^= 1;
    }
}
