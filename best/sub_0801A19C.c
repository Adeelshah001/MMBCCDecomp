extern void sub_0800D770(void *, int, int);
extern void sub_0800D9EC(void *, int);
extern void sub_0800DD08(void *, void *);
extern void sub_0800DD2C(void *, int, int);
extern void sub_0804A378(int);

extern u16 D_081705B0[];
extern u8 D_020031E4[];

struct BattleStruct {
    u8 pad0[0x22];
    u8 unk22;
    u8 pad23[0x22];
    u8 unk45;
    u8 pad46[0x12];
    u32 unk58;
    u32 unk5C;
    u32 unk60;
    u32 unk64;
};

void sub_0801A19C(struct BattleStruct *arg0) {
    int sp_local[2];
    int var_r1;
    int mask;
    int tmp;
    int index;
    int zero;

    sub_0800D770(arg0, 0x848, 0);
    sub_0800D9EC(arg0, 0);

    index = (D_081705B0[0] >> 4) * 2;
    var_r1 = 3 & D_020031E4[index];
    if (var_r1 > 3) {
        var_r1 = 3;
    }
    var_r1 = var_r1;

    mask = var_r1;
    mask = mask << 2;
    tmp = -0xD;
    arg0->unk45 = (u8)((tmp & arg0->unk45) | mask);
    arg0->unk22 = 0xD;

    zero = 0;
    arg0->unk58 = zero;
    arg0->unk60 = zero;
    arg0->unk5C = zero;
    arg0->unk64 = zero;

    sub_0800DD08(sp_local, arg0);
    sub_0800DD2C(arg0, 0xFFFFEC00, 0);
    sub_0804A378(0x9F);
}
