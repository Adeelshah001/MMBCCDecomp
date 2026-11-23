struct Coord16 {
    short x;
    short y;
};

struct Sub16E84 {
    u8 unk00;
    u8 pad01[3];
    u8 unk04;
    u8 pad05[5];
    u8 unk0A;
};

struct Obj16E84 {
    u8 pad00[0x10];
    u8 unk10;
    u8 unk11;
    u8 pad12[0x1A];
    u32 unk2C;
    u8 pad30[0x4C];
    struct Sub16E84 unk7C;
};

extern const struct Coord16 D_08223ED8[];

void sub_08017458(u32);
void sub_080174C4(u32, int, int);
void sub_08011F68(struct Obj16E84 *, u32);

void sub_08016E84(struct Obj16E84 *obj, u8 arg1, u8 arg2, u32 arg3, u8 arg4) {
    struct Sub16E84 *sub = &obj->unk7C;

    obj->unk2C = arg3;
    sub_08017458(arg3);
    sub_080174C4(arg3, D_08223ED8[sub->unk00].x, D_08223ED8[sub->unk00].y);
    obj->unk10 = arg1;
    obj->unk11 = arg2;
    sub_08011F68(obj, 3);
    sub->unk04 = 1;
    sub->unk0A = arg4;
}
