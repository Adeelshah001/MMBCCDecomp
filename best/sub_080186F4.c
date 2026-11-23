extern u8 D_020031E4[];
extern u16 D_081705B0[];

extern void sub_0800D6E0(void *, int, int);
extern void sub_0800D9EC(void *, int);
extern void sub_0800DD4C(void *, int, int);
extern void sub_0804A378(int);

struct UnkStruct_080186F4 {
    u8 pad0[0x22];
    u8 unk22;
    u8 pad1[0x22];
    u8 unk45;
    u8 pad2[0x12];
    u32 unk58;
    u32 unk5C;
    u32 unk60;
    u32 unk64;
};

void sub_080186F4(struct UnkStruct_080186F4 *arg0) {
    int var;

    sub_0800D6E0(arg0, 0x203, 0);
    sub_0800D9EC(arg0, 0);

    var = 3 & D_020031E4[((u16)(*D_081705B0 >> 4) * 2)];
    if (var > 3) {
        var = 3;
    }

    arg0->unk45 = (u8)((-13 & arg0->unk45) | (var * 4));
    arg0->unk22 = 13;
    arg0->unk58 = 0x200;
    arg0->unk60 = 0;
    arg0->unk5C = -198;
    arg0->unk64 = 8;

    sub_0800DD4C(arg0, -10240, -8960);
    sub_0804A378(138);
}
